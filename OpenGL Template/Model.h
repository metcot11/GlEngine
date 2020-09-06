#pragma once
#include <string>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Shader.h"
#include "Mesh/Mesh.h"

class Model
{
private:
	std::vector<Texture> vTextures_loaded;
	std::vector<Mesh> vMeshes;
	std::string mDirectory;

public:
	Model(std::string path);
	~Model();

	void Draw(Shader& shader);
	void Draw(Shader& shader, glm::vec3 pos);

private:
	void LoadModel(std::string Path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

