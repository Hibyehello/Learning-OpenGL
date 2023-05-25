#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <vector>

#include "Error.h"

struct VertexElement {
	uint32_t type;
	uint32_t count;
	unsigned char normalized;

	static uint32_t GetSizeOfType(uint32_t type) { 
		switch(type) {
			case GL_FLOAT: 			return 4;
			case GL_UNSIGNED_INT: 	return 4;
			case GL_UNSIGNED_BYTE: 	return 1;
		}
		std::runtime_error("Unsupported Type");
		return 0;
	}
};

class VertexLayout {
private:
	std::vector<VertexElement> m_elements;
	uint32_t m_stride;
public:
	VertexLayout()
		: m_stride(0) {}

	template<typename T>
	void push(uint32_t) {
		std::runtime_error("Unsupported Type");
	}

	template<>
	void push<float>(uint32_t count) {
		m_elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_stride += VertexElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<uint32_t>(uint32_t count) {
		m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		m_stride += VertexElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(uint32_t count) {
		m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_stride += VertexElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexElement>& getElements() const { return m_elements; }
	inline uint32_t getStride() const { return m_stride; }
};
