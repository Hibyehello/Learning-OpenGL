#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

Renderer::Renderer() {
	std::cout << glGetString(GL_VERSION) << std::endl;	

}

void Renderer::onUpdate(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		

}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
