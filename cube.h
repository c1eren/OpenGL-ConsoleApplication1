#pragma once

#include <vector>
#include <span>
#include <string>
#include <array>
#include "shader.h"

// LOAD
// Get vertices
// Get indices
// Get texture/s
// Save these
// Create VAO, VBO, EBO, VAP

// DRAW
// Load properties
// Draw

//const unsigned int NumberOfTextures = 2;

#define vertNo 192		// 288 for vector

extern std::array<std::string, 4> texTypes;

struct CubeTex {
	unsigned int id;
	std::string type; // eg. diffuse, specular
	std::string path;
};


class Cube {
public:
	// Mesh data
	std::span<float>			vertices;
	std::span<unsigned int>		indices;
	std::vector<CubeTex>		textures;
	static std::vector<CubeTex> textures_loaded;

	Cube(std::span<float> vertices, std::span<unsigned int> indices, std::vector<std::string> texturePaths);
	Cube(std::span<float> vertices, std::vector<std::string> texturePaths);
	Cube(std::span<float> vertices);


	void Draw(Shader& shader);
	void DrawNoTex(Shader& shader);

private:
	// Render data
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	// Optional EBO, Tex
	bool hasEBO;
	bool hasTex;

	void setUpCube();
	void setUpCubeNoEBO();
	void setUpCubeScreen();



	CubeTex loadTextures(std::string texturePath);
};
