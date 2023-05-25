#pragma once

#include <cstdint>

class VertexBuffer {
private:
	uint32_t m_renderer_id;
public:
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};

class IndexBuffer {
private:
	uint32_t m_renderer_id;
	uint32_t m_count;
public:
	IndexBuffer(const void* data, uint32_t count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline uint32_t getCount() const { return m_count; }
};
