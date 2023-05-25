#pragma once

#include <string>
#include <unordered_map>

class Shader {
private:
	std::string m_filepath_v;
	std::string m_filepath_f;
	uint32_t m_renderer_id;
	std::unordered_map<std::string, uint32_t> m_location_cache;
public:
	Shader(const std::string& vfile, const std::string& ffile);
	~Shader();

	void Bind() const;
	void UnBind() const;

	// Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	uint32_t GetUniformLocation(const std::string& name);
	uint32_t CompileShader(uint32_t type, std::string source);
	uint32_t CreateShader(const std::string& vertex, const std::string& fragment);
};
