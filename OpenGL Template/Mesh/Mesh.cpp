#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<Texture> tex)
	:VAO(0), EBO(0), VBO(0)
{
	this->mVertices = ver;
	this->mIndices = ind;
	this->mTextures = tex;

	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < mTextures.size(); i++)
	{
		std::string number;
		std::string name = mTextures[i].Type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr);
		else if (name == "texture_normal")
			number = std::to_string(normalNr);
		else if (name == "texture_heigth")
			number = std::to_string(heightNr);

		mTextures[i].textureName = ("material." + name + number).c_str();
		mTextures[i].BindTexture2D(shader, i);
		}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
void Mesh::Draw(Shader& shader, glm::vec3 pos)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < mTextures.size(); i++)
	{
		std::string number;
		std::string name = mTextures[i].Type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr);
		else if (name == "texture_normal")
			number = std::to_string(normalNr);
		else if (name == "texture_heigth")
			number = std::to_string(heightNr);

		mTextures[i].textureName = ("material." + name + number).c_str();
		mTextures[i].BindTexture2D(shader, i);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetUniformMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
}

Mesh::~Mesh()
{
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));


	glBindVertexArray(0);

}
