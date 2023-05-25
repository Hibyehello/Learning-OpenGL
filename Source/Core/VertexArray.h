#pragma once

#include <glad/glad.h>

#include "Buffers.h"
#include "VertexLayout.h"

class VertexArray {
private:
	uint32_t m_renderer_id;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer& vb, const VertexLayout& vl);
};
