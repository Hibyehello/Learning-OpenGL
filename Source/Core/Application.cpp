#include "Application.h"
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
		-50.0f, -50.0f, 0.0f, 0.0f, // 0
         50.0f, -50.0f, 1.0f, 0.0f, // 1
         50.0f,  50.0f, 1.0f, 1.0f, // 2
		-50.0f,  50.0f, 0.0f, 1.0f  // 3
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
	
	vl.push<float>(2); // Positions
	vl.push<float>(2); // Texture Coordinates
	vao.AddBuffer(vbo, vl);

	IndexBuffer ibo(indices, 6);

	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	Shader shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
	shader.Bind();

	Texture texture("Resources/oglImage.png");
	texture.Bind();
	shader.SetUniform1i("u_texture", 0);

	vao.UnBind();
	vbo.UnBind();
	ibo.UnBind();
	shader.UnBind();

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(400, 200, 0);

	while (!glfwWindowShouldClose(m_window)) {

		m_renderer->Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();			
			shader.SetUniformMat4f("u_mvp", mvp);

 			m_renderer->Draw(vao, ibo, shader);
		}

       
		
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniformMat4f("u_mvp", mvp);

			m_renderer->Draw(vao, ibo, shader);
		}

        

		{          
            ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f); 
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        }

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
   
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
