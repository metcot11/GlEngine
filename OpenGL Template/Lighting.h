#pragma once
#include "Shader.h"
#include "Camera/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class PointLight
{
public:
	std::string Name;

	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	PointLight(glm::vec3 Position, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float Constant, float Linear, float Quad);
	PointLight(std::string name, glm::vec3 Position, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float Constant, float Linear, float Quad);
	PointLight(std::string name);
	~PointLight();

	void operator=(PointLight p);

	void RenderPntLight(glm::vec3 Pos, Shader shader);
 	void SendUniforms(Shader shader);

	void SendUniformPosition(Shader shader);
	void SendUniformDiffuse(Shader shader);
	void SendUniformSpecular(Shader shader);

	void SendUniformAmbient(Shader shader);
	void SendUniformConstant(Shader shader);
	void SendUniformLinear(Shader shader);
	void SendUniformQuadratic(Shader shader);
};	
class DirectionalLight {
public:
	std::string Name;

	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	
	DirectionalLight(glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	DirectionalLight(std::string name, glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	DirectionalLight(std::string name);
	~DirectionalLight();

	void operator=(DirectionalLight d);
	void RenderDirLight(Shader shader, glm::vec3 Dir);

	void SendUniforms(Shader shader);
	void SendUniformDirection(Shader shader);
	void SendUniformDiffuse(Shader shader);
	void SendUniformSpecular(Shader shader);
	void SendUniformAmbient(Shader shader);
};
class SpotLight {
public:
	std::string Name;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;

	Camera& cam;

	SpotLight(Camera& c, std::string name);
	SpotLight(Camera& c, std::string name, glm::vec3 Ambient,
				glm::vec3 Diffuse, glm::vec3 Specular, float Constant,
				float Linear, float Quad, float ang1, float ang2);
	~SpotLight() = default;

	void RenderSpotLight(Shader shader);

	void SendUniforms(Shader shader);
	void SendUniformDiffuse(Shader shader);
	void SendUniformSpecular(Shader shader);
	void SendUniformAmbient(Shader shader);

	void SendUniformConstant(Shader shader);
	void SendUniformLinear(Shader shader);
	void SendUniformQuadratic(Shader shader);

	void SendUniformAngules(Shader shader);
};

