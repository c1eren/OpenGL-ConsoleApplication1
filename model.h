#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

extern std::vector<Texture> textures_loaded;

class Model {
	
public:
	Model(std::string path);

	void Draw(Shader& shader);
	std::vector<Mesh> meshes;

private:
	// Model data
	
	// Each model has an array of meshes

	// Filepath
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};