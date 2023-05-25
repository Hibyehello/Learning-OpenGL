#include "VertexArray.h"

#include "Error.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_renderer_id));
}

VertexArray::~VertexArray() {
	GLCall(glad_glDeleteVertexArrays(1, &m_renderer_id));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexLayout& vl) {
	Bind();
	vb.Bind();

	const auto& elements = vl.getElements();
	uint32_t offset = 0;
	for(uint32_t i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vl.getStride(), reinterpret_cast<const void*>(offset)));

		offset+= element.count * VertexElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_renderer_id));
}

void VertexArray::UnBind() const {
	GLCall(glBindVertexArray(0));
}
