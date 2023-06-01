#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
private:
	std::string m_filepath_v;
	std::string m_filepath_f;
	uint32_t m_renderer_id;
	mutable std::unordered_map<std::string, int> m_location_cache;
public:
	Shader(const std::string& vfile, const std::string& ffile);
	~Shader();

	void Bind() const;
	void UnBind() const;

	// Set Uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, float v0, float v2);
	void SetUniform3f(const std::string& name, float v0, float v2, float v3);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	
	void SetUniformMat3f(const std::string& name, glm::mat3 matrix);
	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);

private:
	int GetUniformLocation(const std::string& name) const;
	uint32_t CompileShader(uint32_t type, std::string source);
	uint32_t CreateShader(const std::string& vertex, const std::string& fragment);
};
