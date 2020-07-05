#include "Lighting.h"

PointLight::PointLight(std::string name)
	:Name(name)
{
}

PointLight::PointLight(glm::vec3 Position, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float Constant, float Linear, float Quad)
	:Name("0")
{
	ambient = Ambient;
	position = Position;
	diffuse = Diffuse;
	specular = Specular;
	constant = Constant;
	linear = Linear;
	quadratic = Quad;
}

PointLight::PointLight(std::string name, glm::vec3 Position, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float Constant, float Linear, float Quad)
	:Name(name)
{
	ambient = Ambient;
	position = Position;
	diffuse = Diffuse;
	specular = Specular;
	constant = Constant;
	linear = Linear;
	quadratic = Quad;
}

PointLight::~PointLight()
{

}

void PointLight::operator=(PointLight p)
{
	position = p.position;
	ambient = p.ambient;
	diffuse = p.diffuse;
	specular = p.specular;

	constant = p.constant;
	linear = p.linear;
	quadratic = p.quadratic;
}

void PointLight::RenderPntLight(glm::vec3 Pos, Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
	shader.SetUniformVec3((Name + ".position").c_str(), Pos);
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);

	shader.SetUniformFloat((Name + ".constant").c_str(), constant);
	shader.SetUniformFloat((Name + ".linear").c_str(), linear);
	shader.SetUniformFloat((Name + ".quadratic").c_str(), quadratic);
}

void PointLight::SendUniforms(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
	shader.SetUniformVec3((Name + ".position").c_str(), position);
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);

	shader.SetUniformFloat((Name + ".constant").c_str(), constant);
	shader.SetUniformFloat((Name + ".linear").c_str() , linear);
	shader.SetUniformFloat((Name + ".quadratic").c_str(), quadratic);
}

void PointLight::SendUniformPosition(Shader shader)
{
	shader.SetUniformVec3((Name + ".position").c_str(), position);
}

void PointLight::SendUniformDiffuse(Shader shader)
{
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
}

void PointLight::SendUniformSpecular(Shader shader)
{
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);
}

void PointLight::SendUniformAmbient(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
}

void PointLight::SendUniformConstant(Shader shader)
{
	shader.SetUniformFloat((Name + ".constant").c_str(), constant);
}

void PointLight::SendUniformLinear(Shader shader)
{
	shader.SetUniformFloat((Name + ".linear").c_str(), linear);
}

void PointLight::SendUniformQuadratic(Shader shader)
{
	shader.SetUniformFloat((Name + ".quadratic").c_str(), quadratic);
}

//Directional Light

DirectionalLight::DirectionalLight(std::string name)
	:Name(name)
{
}

DirectionalLight::DirectionalLight(glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
	:Name("0")
{
	direction = Direction;
	ambient = Ambient;
	diffuse = Diffuse;
	specular = Specular;
}

DirectionalLight::DirectionalLight(std::string name, glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
	:Name(name)
{
	direction = Direction;
	ambient = Ambient;
	diffuse = Diffuse;
	specular = Specular;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::operator=(DirectionalLight d)
{
	direction = d.direction;
	ambient = d.ambient;
	diffuse = d.diffuse;
	specular = d.specular;
}


void DirectionalLight::RenderDirLight(Shader shader, glm::vec3 Dir)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
	shader.SetUniformVec3((Name + ".direction").c_str(), Dir);
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);
}

void DirectionalLight::SendUniforms(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
	shader.SetUniformVec3((Name + ".direction").c_str(), direction);
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);
}

void DirectionalLight::SendUniformDirection(Shader shader)
{
	shader.SetUniformVec3((Name + ".direction").c_str(), direction);
}

void DirectionalLight::SendUniformDiffuse(Shader shader)
{
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
}

void DirectionalLight::SendUniformSpecular(Shader shader)
{
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);
}

void DirectionalLight::SendUniformAmbient(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
}

	//SpotLight

SpotLight::SpotLight( Camera& c, std::string name)
	:Name(name), cam(c), cutOff(13.5f), outerCutOff(15.5f)
{
}

SpotLight::SpotLight(Camera& c, std::string name, glm::vec3 Ambient,
						glm::vec3 Diffuse, glm::vec3 Specular, float Constant,
						float Linear, float Quad, float ang1, float ang2)
	:Name(name), cam(c), cutOff(ang1), outerCutOff(ang2)
{
	ambient = Ambient;
	diffuse = Diffuse;
	specular = Specular;

	constant = Constant;
	linear = Linear;
	quadratic = Quad;
}

void SpotLight::RenderSpotLight(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
	shader.SetUniformVec3((Name + ".position").c_str(), cam.Position);
	shader.SetUniformVec3((Name + ".direction").c_str(), cam.Front);
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);

	shader.SetUniformFloat((Name + ".constant").c_str(), constant);
	shader.SetUniformFloat((Name + ".linear").c_str(), linear);
	shader.SetUniformFloat((Name + ".quadratic").c_str(), quadratic);
	shader.SetUniformFloat((Name + ".cutOff").c_str(), glm::cos(glm::radians(cutOff)));
	shader.SetUniformFloat((Name + ".outerCutOff").c_str(), glm::cos(glm::radians(outerCutOff)));
}

void SpotLight::SendUniforms(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
	shader.SetUniformVec3((Name + ".position").c_str(), cam.Position);
	shader.SetUniformVec3((Name + ".direction").c_str(), cam.Front);
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);

	shader.SetUniformFloat((Name + ".constant").c_str(), constant);
	shader.SetUniformFloat((Name + ".linear").c_str(), linear);
	shader.SetUniformFloat((Name + ".quadratic").c_str(), quadratic);
	shader.SetUniformFloat((Name + ".cutOff").c_str(), glm::cos(glm::radians(cutOff)));
	shader.SetUniformFloat((Name + ".outerCutOff").c_str(), glm::cos(glm::radians(outerCutOff)));
}

void SpotLight::SendUniformDiffuse(Shader shader)
{
	shader.SetUniformVec3((Name + ".diffuse").c_str(), diffuse);
}

void SpotLight::SendUniformSpecular(Shader shader)
{
	shader.SetUniformVec3((Name + ".specular").c_str(), specular);
}

void SpotLight::SendUniformAmbient(Shader shader)
{
	shader.SetUniformVec3((Name + ".ambient").c_str(), ambient);
}

void SpotLight::SendUniformConstant(Shader shader)
{
	shader.SetUniformFloat((Name + ".constant").c_str(), constant);
}

void SpotLight::SendUniformLinear(Shader shader)
{
	shader.SetUniformFloat((Name + ".linear").c_str(), linear);
}

void SpotLight::SendUniformQuadratic(Shader shader)
{
	shader.SetUniformFloat((Name + ".quadratic").c_str(), quadratic);
}

void SpotLight::SendUniformAngules(Shader shader)
{
	shader.SetUniformFloat((Name + ".cutOff").c_str(), cutOff);
	shader.SetUniformFloat((Name + ".outerCutOff").c_str(), outerCutOff);
}



