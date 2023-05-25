#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Buffers.h"
#include "Error.h"
#include "VertexArray.h"

class Renderer {
private:
	VertexBuffer* m_vbo;
	IndexBuffer*  m_ibo;
	VertexArray*  m_vao;
	VertexLayout* m_vl;
	uint32_t m_shader;
public:
	Renderer();
	~Renderer() = default;

	void onUpdate();
	void terminate();

	static uint32_t CreateShader(const std::string& vertex, const std::string& fragment);
	static uint32_t CompileShader(uint32_t type, const std::string& src);
};
