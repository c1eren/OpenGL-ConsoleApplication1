#include <iostream>

#include "cube.h"
#include "stb_image.h" 


std::array<std::string, 4> texTypes{
	"diffuse",
	"specular",
	"normal",
	"emission"
};

std::vector<Texture> Cube::textures_loaded; // Available to all Cube instances

Cube::Cube(std::span<float> vertices, std::span<unsigned int> indices, std::vector<std::string> texturePaths)
{
	this->vertices = vertices;
	this->indices = indices;
	
	for (unsigned int i = 0; i < texturePaths.size(); i++)
	{
		this->textures.push_back(loadTextures(texturePaths[i]));
	}
	hasEBO = 1;
	hasTex = 1;
	setUpCube();
}

Cube::Cube(std::span<float> vertices, std::vector<std::string> texturePaths)
{
	this->vertices = vertices;

	for (unsigned int i = 0; i < texturePaths.size(); i++)
	{
		this->textures.push_back(loadTextures(texturePaths[i]));
	}
	hasEBO = 0;
	hasTex = 1;
	setUpCubeNoEBO();
}

Cube::Cube(std::span<float> vertices)
{
	this->vertices = vertices;
	hasEBO = 0;
	hasTex = 0;
	setUpCubeScreen();
}


Texture Cube::loadTextures(std::string texturePath)
{

	Texture texture;

	// Check if texture is already loaded
	bool skip = 0;
	for (unsigned int j = 0; j < textures_loaded.size(); j++)
	{
		if (!std::strcmp(textures_loaded[j].path.data(), texturePath.c_str()))
		{
			// Mesh will use this texture
			texture = (textures_loaded[j]);
			skip = 1;
			break;
		}
	}

	if (!skip)
	{
		texture.path = texturePath;

		for (unsigned int i = 0; i < texTypes.size(); i++)
		{
			if (texturePath.find(texTypes[i]) != std::string::npos)
			{
				texture.type = "texture_" + texTypes[i];
				break;
			}
		}

		// Generate texture handle
		glGenTextures(1, &texture.id);

		// Load texture using stbi
		const char* path = texturePath.c_str(); // Can look at stbi_load() just taking a std::string
		//load texture with stb_i
		int width;
		int height;
		int nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 2)
				format = GL_RG;
			else if (nrChannels == 3)
				format = GL_RGB;
			else
				format = GL_RGBA; // Look here if things start breaking

			// Generate texture 
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Free image load data
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture at: " << "\"" << path << "\"" << std::endl;
			stbi_image_free(data);
		}

		textures_loaded.push_back(texture);
	}

	return texture;

}

void Cube::setUpCube()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// Vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	glBindVertexArray(0);
}

void Cube::setUpCubeNoEBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// Vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);

}

void Cube::setUpCubeScreen()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	// Vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindVertexArray(0);
}

void Cube::Draw(Shader &shader)
{
	if (hasTex)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++);
			}
			// Concatenate type and number together and set a location value to correspond with active texture unit
			shader.setInt(("material." + name + number).c_str(), i);
			//std::cout << "(material. + name + number).c_str(): " << ("material." + name + number).c_str() << std::endl;
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
	}

	if (!hasEBO)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	else
	{
		// Draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void Cube::DrawNoTex(Shader &shader)
{
	// Draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}