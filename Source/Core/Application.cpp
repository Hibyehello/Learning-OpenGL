#include "Application.h"

#include <iostream>

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
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	VertexBuffer vbo(positions, 4 * 2 * sizeof(float));
	VertexLayout vl;
	
	vl.push<float>(2);
	vao.AddBuffer(vbo, vl);

	IndexBuffer ibo(indices, 6);

	Shader shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
	shader.Bind();
	shader.SetUniform4f("u_color", 0.4f, 0.5f, 0.7f, 1.0f);

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

	Application* app = new Application(640, 480, "Test App");

	app->SetMonitorFromCurrent();
	
	return app->Run();
}
