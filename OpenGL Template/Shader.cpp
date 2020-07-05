#include "Shader.h"


Shader::Shader(const char* pathFragmShader, const char* pathVertShader)
	:FragId(0), VertId(0)
{

	std::fstream fileFrag(pathFragmShader);
	std::fstream fileVert(pathVertShader);
	if (!fileFrag.is_open()) {
		std::cout << "ERROR::SHADER_FRAGMENT::NOT_FOUND" << '\n';
		return;
	}
	if (!fileVert.is_open()) {
		std::cout << "ERROR::SHADER_VERTEX::NOT_FOUND" << '\n';
		return;
	}

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

Shader::~Shader()
{
	glDeleteShader(ShaderId);
}

void Shader::operator=(Shader s)
{
	ShaderId = s.ShaderId;
	FragId   = s.FragId;
	VertId   = s.VertId;

	FragmentShader	= s.FragmentShader;
	VertexShader	= s.VertexShader;

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

void Shader::SetUniformVec3(const char* UniformName, float x, float y, float z )
{
	glUniform3f(glGetUniformLocation(ShaderId, UniformName), x, y, z);
}

void Shader::SetUniformVec3(const char* UniformName, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(ShaderId, UniformName), value.x, value.y, value.z);
}

void Shader::SetUniformVec4(const char* UniformName, float x, float y, float z, float t)
{
	glUniform4f(glGetUniformLocation(ShaderId, UniformName), x, y, z, t);
}

void Shader::SetUniformMat3(const char* UniformName, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(ShaderId, UniformName), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformMat4(const char* UniformName, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderId, UniformName), 1, GL_FALSE, glm::value_ptr(value));
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
