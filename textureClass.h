#pragma once
#include "stb_image.h"  

#include <glad/glad.h>

struct texData {
    const char* texPath;
    GLint internalFormat;
    GLenum dimension;
    GLenum format;
};

class Texture {
public:

    unsigned int texId;
    static GLuint nextAvailableUnit; // shared across all instances
    GLenum textureUnit;

    texData data;

    Texture(const texData& texData);

    void load();
    void bind();
    GLuint nextAvailableUnitGet();

};

/*
//generating a texture
unsigned int texture1;
glGenTextures(1, &texture1);

//activate texture unit 0
glActiveTexture(GL_TEXTURE0);

//bind texture to active texture (GL_TEXTURE0 currently)
glBindTexture(GL_TEXTURE_2D, texture1);

//set the texture filtering/wrapping options (on currently bound texture)
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


//load texture with stb_i
const char* texPath1 = "textures/container.jpg";
int width;
int height;
int nrChannels;
unsigned char* data = stbi_load(texPath1, &width, &height, &nrChannels, 0);

if (data)
{
    //generate texture 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    std::cout << "Failed to load texture at: " << "\"" << texPath1 << "\"" << std::endl;
}

//free image load data
stbi_image_free(data);
*/
