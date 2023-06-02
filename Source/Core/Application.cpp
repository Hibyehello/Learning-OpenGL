#include "Application.h"
#include "Tests/TestMenu.h"
#include "glm/ext/matrix_transform.hpp"

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Common/structures.h>

#include <Core/Buffers.h>
#include <Core/Error.h>
#include <Core/Shader.h>
#include <Core/Texture.h>
#include <Core/VertexArray.h>
#include <Core/VertexLayout.h>

#include <Tests/TestClearColor.h>
#include <Tests/TestColorCubes.h>
#include <Tests/TestMenu.h>
#include <Tests/TestTextures3D.h>
#include <Tests/TestTextures2D.h>

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
	Renderer::PrintGLVersion();
}

int Application::Run() {
	GLCall(glEnable(GL_BLEND));
	glEnable(GL_DEPTH_TEST);  
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	Test::Test* current = nullptr;
	Test::Menu* menu = new Test::Menu(current);
	current = menu;

	menu->RegisterTest<Test::ClearColor>();
	menu->RegisterTest<Test::Texture2D>();
	menu->RegisterTest<Test::Texture3D>();
	menu->RegisterTest<Test::ColorCubes>();

	while (!glfwWindowShouldClose(m_window)) {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		m_renderer->Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if(current) {
			current->OnUpdate(0.0f);
			current->OnRender();
			ImGui::Begin(current->GetName().c_str());
			if(current != menu && ImGui::Button("<-")) {
				delete current;
				current = menu;
			}
			current->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
	
	if(current != menu)
		delete menu;
	delete current;
   
   	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
