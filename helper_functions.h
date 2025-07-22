#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>

#include "cube.h" 


unsigned int load_tex(std::string texturePath);
void drawTwoCubes(Shader& shader, Cube& cube);

unsigned int load_tex(std::string texturePath)
{
    unsigned int textureId;
    // Generate texture handle
    glGenTextures(1, &textureId);

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
        glBindTexture(GL_TEXTURE_2D, textureId);
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

    return textureId;
}

void drawTwoCubes(Shader& shader, Cube& cube)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader.setMat4("model", model);
    cube.Draw(shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader.setMat4("model", model);
    cube.Draw(shader);
}

