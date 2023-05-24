#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

Renderer::Renderer() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    std::cerr << "Failed to initialize GLAD" << std::endl;
	    abort();
	}

	std::cout << glGetString(GL_VERSION) << std::endl;	

	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
	
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	std::ifstream vertex("Shaders/vertex.glsl");
	std::ifstream fragment("Shaders/fragment.glsl");

	std::stringstream vs;
	std::stringstream fs;


	vs << vertex.rdbuf();

	std::cout << vs.str() << std::endl;

	fs << fragment.rdbuf();

	std::cout << fs.str() << std::endl;

	uint32_t shader = CreateShader(vs.str(), fs.str());
}

void Renderer::onUpdate() {
	std::cout << "Update" << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

uint32_t Renderer::CreateShader(const std::string& vertex, const std::string& fragment) {
	uint32_t program = glCreateProgram();

	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertex);
	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

uint32_t Renderer::CompileShader(uint32_t type, const std::string& source) {
	uint32_t id = glCreateShader(type);

	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);

		std::cerr << "Failed to compile shader: " << type << ": " << message << std::endl;
	}

	return id;
}
