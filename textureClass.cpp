#include <iostream>
#include "stb_image.h"  

#include "textureClass.h"

GLuint Texture::nextAvailableUnit = 0;

Texture::Texture(const texData& texData)
	: data(texData)
{
	glGenTextures(1, &texId);
	textureUnit = GL_TEXTURE0 + nextAvailableUnitGet();
	nextAvailableUnit++;

	bind();
	load();
}

void Texture::load()
{
	int width;
	int height;
	int nrChannels;
	unsigned char* loadData = stbi_load(data.texPath, &width, &height, &nrChannels, 0);

	if (loadData)
	{
		//generate texture 
		glTexImage2D(data.dimension, 0, data.internalFormat, width, height, 0, data.format, GL_UNSIGNED_BYTE, loadData);
		glGenerateMipmap(data.dimension);
	}
	else
	{
		std::cout << "Failed to load texture at: " << "\"" << data.texPath << "\"" << std::endl;
	}

	//free image load data
	stbi_image_free(loadData);
}

void Texture::bind()
{
	glActiveTexture(textureUnit);
	glBindTexture(data.dimension, texId);
}

GLuint Texture::nextAvailableUnitGet()
{
	GLint maxUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);

	if (nextAvailableUnit >= maxUnits)
	{
		std::cout << "WARNING::MAX_TEXTURE_IMAGE_UNITS: " << "\"" << maxUnits << "\"" << " ::"
				  << "CURRENT_TEXTURE_IMAGE_UNITS_USED: " << "\"" << nextAvailableUnit << "\"" 
				  << std::endl;
		return -1;
	}
	else
	{
		return nextAvailableUnit;
	}
}



