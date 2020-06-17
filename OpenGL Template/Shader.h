#pragma once
#include <glew.h>

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int ShaderId;
	unsigned int FragId;
	unsigned int VertId;

	const char* FragmentShader;
	const char* VertexShader;
public:
	Shader(const char* pathFragmShader, const char* pathVertShader);
	
	void On();
	void Off();

		/*Uniforms*/
	void SetUniformInt(const char* UniformName, int value);
	void SetUniformFloat(const char* UniformName, float value);
	void SetUniformBool(const char* UniformName, bool value);
	void SetUniformVec4(const char* UniformName, float x, float y, float z, float t);
	void SetUniformMat4(const char* UniformName, glm::mat4 value);
private:
	void CompileFragmentShader();
	void CompileVertexShader();
};

