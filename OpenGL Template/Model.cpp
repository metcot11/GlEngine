#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Model::Model(std::string path)
{
	LoadModel(path);

}


Model::~Model()
{
}

void Model::Draw(Shader& shader)
{
	for (auto i : vMeshes)
		i.Draw(shader);
}

void Model::Draw(Shader& shader, glm::vec3 pos)
{
	for (auto i : vMeshes)
		i.Draw(shader);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetUniformMat4("model", model);
}

void Model::LoadModel(std::string Path)
{
		/*Read File*/
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(Path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		/*Error check*/
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << '\n';
		return;
	}
	mDirectory = Path.substr(0, Path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		vMeshes.push_back(ProcessMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::vector<Texture>		textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;

		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;

		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < vTextures_loaded.size(); j++)
		{
			if (std::strcmp(vTextures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(vTextures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			std::string Filename = std::string(str.C_Str());
			Filename = mDirectory + '/' + Filename;
			texture.LoadTexture2D(Filename.c_str(),0);
			texture.Type = typeName;
			texture.path = str.C_Str();

			textures.push_back(texture);
			vTextures_loaded.push_back(texture);
		}
	}
	return textures;
}
