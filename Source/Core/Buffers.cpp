#include "Buffers.h"

#include "Error.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
	GLCall(glGenBuffers(1, &m_renderer_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::UnBind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

IndexBuffer::IndexBuffer(const void* data, uint32_t count)
	: m_count(count) {
	GLCall(glGenBuffers(1, &m_renderer_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::UnBind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
