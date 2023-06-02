#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

Renderer::Renderer() {
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
		

}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::PrintGLVersion() {
	std::cout << glGetString(GL_VERSION) << std::endl;	
}
