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

	while (!glfwWindowShouldClose(m_window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        m_renderer->onUpdate();

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }

	m_renderer->terminate();
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
