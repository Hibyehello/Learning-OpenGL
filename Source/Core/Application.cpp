#include "Application.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffers.h"
#include "Error.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexLayout.h"

Application::Application(uint32_t width, uint32_t height, const char* title) {
	this->m_width = width;
	this->m_height = height;
	this->m_title = title;
	this->m_monitor = NULL;

	m_window = glfwCreateWindow(m_width, m_height, m_title, m_monitor, NULL);
	if(!m_window) {
			std::cerr << "Window is not initialized" << std::endl;
			glfwTerminate();
			abort();
	}

	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    std::cerr << "Failed to initialize GLAD" << std::endl;
	    abort();
	}

	this->m_renderer = new Renderer();
}

int Application::Run() {

	float positions[] = {
		 100.0f,  100.0f, 0.0f, 0.0f, // 0
		 200.0f,  100.0f, 1.0f, 0.0f, // 1
		 200.0f,  200.0f, 1.0f, 1.0f, // 2
		 100.0f,  200.0f, 0.0f, 1.0f  // 3
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	VertexArray vao;
	VertexBuffer vbo(positions, 4 * 4 * sizeof(float));
	VertexLayout vl;
	
	vl.push<float>(2);
	vl.push<float>(2);
	vao.AddBuffer(vbo, vl);

	IndexBuffer ibo(indices, 6);

	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

	Shader shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
	shader.Bind();
	shader.SetUniformMat4f("u_mvp", proj);

	Texture texture("Resources/oglImage.png");
	texture.Bind();
	shader.SetUniform1i("u_texture", 0);

	vao.UnBind();
	vbo.UnBind();
	ibo.UnBind();
	shader.UnBind();
	

	while (!glfwWindowShouldClose(m_window)) {

		m_renderer->Clear();
        m_renderer->onUpdate(vao, ibo, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void Application::SetMonitor(GLFWmonitor* monitor) {
	this->m_monitor = monitor;
}

void Application::SetMonitorFromCurrent() {
	this->m_monitor = glfwGetWindowMonitor(m_window);
}


int main() {
	if(!glfwInit()) {
		std::cerr << "glfw failed to Init" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	Application* app = new Application(960, 540, "Test App");

	app->SetMonitorFromCurrent();
	
	return app->Run();
}
