#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include "Error.h"

Shader::Shader(const std::string& vfile, const std::string& ffile)
	: m_filepath_v(vfile),  m_filepath_f(ffile)
{
	std::ifstream vs(vfile);
	std::ifstream fs(ffile);
	std::stringstream v;
	std::stringstream f;

	v << vs.rdbuf();
	f << fs.rdbuf();

	m_renderer_id = CreateShader(v.str(), f.str());
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_renderer_id));
}

void Shader::Bind() const {
	GLCall(glUseProgram(m_renderer_id));
}

void Shader::UnBind() const {
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value) {
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1) {
	GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat3f(const std::string& name, glm::mat3 matrix) {
	GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const {
	if(m_location_cache.find(name) != m_location_cache.end())
		return m_location_cache[name];

	GLCall(int loc = glGetUniformLocation(m_renderer_id, name.c_str()));

	if(loc == -1) 
		std::cerr << "Uniform not found: " << name << std::endl;
	else
		m_location_cache[name] = loc;
	return loc;
}

uint32_t Shader::CompileShader(uint32_t type, std::string source) {
	uint32_t id = glCreateShader(type);

	const char* src = source.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if(result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));

		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cerr << "Failed to compile shader: " << type << ": " << message << std::endl;
	}

	return id;
}

uint32_t Shader::CreateShader(const std::string& vertex, const std::string& fragment) {
	uint32_t program = glCreateProgram();

	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertex);
	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}
