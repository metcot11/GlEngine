#include "Material.h"



Material::Material(glm::vec3 ambient, glm::vec3 difuse, glm::vec3 specular, float shininess)
	:Ambient(ambient), Difuse(difuse),Specular(specular),Shininess(shininess)
{
}

Material::Material(Material& mat)
{
	Ambient = mat.Ambient;
	Difuse = mat.Difuse;
	Specular = mat.Specular;
	Shininess = mat.Shininess;
}

Material::Material()
	:Shininess(0)
{
}



Material::~Material()
{
}

void Material::operator=(Material& mat)
{
	Ambient = mat.Ambient;
	Difuse = mat.Difuse;
	Specular = mat.Specular;
	Shininess = mat.Shininess;
}

void Material::SetMaterial(glm::vec3 ambient, glm::vec3 difuse, glm::vec3 specular, float shininess)
{
	Ambient = ambient;
	Difuse = difuse;
	Specular = specular;
	Shininess = shininess;
}

void Material::SetMaterial(Material mat)
{
	Ambient = mat.Ambient;
	Difuse = mat.Difuse;
	Specular = mat.Specular;
	Shininess = mat.Shininess;
}

void Material::SetUniforms(Shader shader)
{
	shader.SetUniformVec3("material.ambient", Ambient);
	shader.SetUniformVec3("material.diffuse", Difuse);
	shader.SetUniformVec3("material.specular", Specular);
	shader.SetUniformFloat("material.shininess", Shininess);
}
void Material::SetAmbientUniform(Shader shader)
{
	shader.SetUniformVec3("material.ambient", Ambient);
}

void Material::SetDifuseUniforms(Shader shader)
{
	shader.SetUniformVec3("material.diffuse", Difuse);
}

void Material::SetSpecularUniforms(Shader shader)
{
	shader.SetUniformVec3("material.specular", Specular);
}

void Material::SetShininessUniforms(Shader shader)
{
	shader.SetUniformFloat("material.shininess", Shininess);
}
