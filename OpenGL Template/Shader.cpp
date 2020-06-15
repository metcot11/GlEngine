#include "Shader.h"


Shader::Shader(const char* pathFragmShader, const char* pathVertShader)
{
	std::fstream fileFrag(pathFragmShader);
	std::fstream fileVert(pathVertShader);

	std::string strFrag;
	std::string strVert;

	std::string line;
	while (getline(fileFrag,line)) {
		strFrag.append(line + '\n');
	}
	fileFrag.close();
	while (getline(fileVert, line)) {
		strVert.append(line + '\n');
	}
	fileVert.close();

	FragmentShader = strFrag.c_str();
	VertexShader = strVert.c_str();

	CompileFragmentShader();
	CompileVertexShader();

	ShaderId = glCreateProgram();

	glAttachShader(ShaderId, VertId);
	glAttachShader(ShaderId, FragId);
	glLinkProgram(ShaderId);

	glDeleteShader(VertId);
	glDeleteShader(FragId);
}

void Shader::On()
{
	glUseProgram(ShaderId);
}

void Shader::Off()
{
	glUseProgram(0);
}

void Shader::SetUniformInt(const char* UniformName, int value)
{
	glUniform1i(glGetUniformLocation(ShaderId, UniformName), value);
}

void Shader::SetUniformFloat(const char* UniformName, float value)
{
	glUniform1f(glGetUniformLocation(ShaderId, UniformName), value);
}

void Shader::SetUniformBool(const char* UniformName, bool value)
{
	glUniform1i(glGetUniformLocation(ShaderId, UniformName), (int)value);
}

void Shader::SetUniformVec4(const char* UniformName, float x, float y, float z, float t)
{
	glUniform4f(glGetUniformLocation(ShaderId, UniformName), x, y, z, t);
}

void Shader::CompileFragmentShader()
{
	FragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragId, 1, &FragmentShader, NULL);
	glCompileShader(FragId);

	int success;
	char infoLog[512];
	glGetShaderiv(FragId, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(FragId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::CompileVertexShader()
{
	VertId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertId, 1, &VertexShader, NULL);
	glCompileShader(VertId);

	int success;
	char infoLog[512];
	glGetShaderiv(VertId, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(VertId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
