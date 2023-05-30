#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Buffers.h"
#include "Error.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer {
private:
	VertexBuffer* m_vbo;
	IndexBuffer*  m_ibo;
	VertexArray*  m_vao;
	VertexLayout* m_vl;
	Shader* 	  m_shader;
public:
	Renderer();
	~Renderer() = default;

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;
};
