#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

Renderer::Renderer() {
	std::cout << glGetString(GL_VERSION) << std::endl;	

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_vao = new VertexArray();
	m_vbo = new VertexBuffer(positions, 4 * 2 * sizeof(float));
	m_vl = new VertexLayout();
	
	m_vl->push<float>(2);
	m_vao->AddBuffer(*m_vbo, *m_vl);

	m_ibo = new IndexBuffer(indices, 6);

	std::ifstream vertex("Shaders/vertex.glsl");
	std::ifstream fragment("Shaders/fragment.glsl");

	std::stringstream vs;
	std::stringstream fs;

	vs << vertex.rdbuf();
	fs << fragment.rdbuf();

	m_shader = CreateShader(vs.str(), fs.str());

}

float r = 0.0f;
float increment = 0.05f;

void Renderer::onUpdate() {
	int u_color_loc = glGetUniformLocation(m_shader, "u_color");
	GLASSERT(u_color_loc != -1);


	
	GLCall(glUniform4f(u_color_loc, r, 0.3f, 0.8f, 1.0f));
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	if(r > 1.0f)
		increment = -0.05f;
	if(r < 0.0f)
		increment = 0.05f;

	r+=increment;
		

}

void Renderer::terminate() {
	glDeleteProgram(m_shader);
}

uint32_t Renderer::CreateShader(const std::string& vertex, const std::string& fragment) {
	uint32_t program = glCreateProgram();

	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertex);
	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	GLCall(glUseProgram(program));

	return program;
}

uint32_t Renderer::CompileShader(uint32_t type, const std::string& source) {
	uint32_t id = glCreateShader(type);

	const char* src = source.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if(result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));

		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cerr << "Failed to compile shader: " << type << ": " << message << std::endl;
	}

	return id;
}
