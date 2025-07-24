#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "shader.h"


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type; // eg. diffuse, specular
	std::string path;
};

class Mesh {
public:
	// Mesh data
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture>		textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);

	unsigned int VAO;
private:
	// Render data
	unsigned int VBO;
	unsigned int EBO;

	void setupMesh();


};
	