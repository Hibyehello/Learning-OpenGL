#include "TestTextures2D.h"

#include <Core/VertexLayout.h>
#include <imgui.h>
#include <memory>

namespace Test {

Texture2D::Texture2D()
	: m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f)), m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
	  m_translationA(200, 200, 0), m_translationB(400, 200, 0) {
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
	
	m_vao = std::make_unique<VertexArray>();
	
	
	m_vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
	VertexLayout vl;
	
	vl.push<float>(2); // Positions
	vl.push<float>(2); // Texture Coordinates
	m_vao->AddBuffer(*m_vbo, vl);

	m_ibo = std::make_unique<IndexBuffer>(indices, 6);
	m_shader = std::make_unique<Shader>("Shaders/vertex.glsl", "Shaders/fragment.glsl");
	m_shader->Bind();

	m_texture = std::make_unique<Texture>("Resources/oglImage.png");
	m_shader->SetUniform1i("u_texture", 0);
}

Texture2D::~Texture2D() {
}

void Texture2D::OnUpdate(float deltaTime) {
}

void Texture2D::OnRender() {
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;

	m_texture->Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->Bind();
		m_shader->SetUniformMat4f("u_mvp", mvp);

 		renderer.Draw(*m_vao, *m_ibo, *m_shader);
	}



	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->Bind();
		m_shader->SetUniformMat4f("u_mvp", mvp);

		renderer.Draw(*m_vao, *m_ibo, *m_shader);
	}

}

void Texture2D::OnImGuiRender() {
	ImGui::SliderFloat2("Translation A", &m_translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat2("Translation B", &m_translationB.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

std::string Texture2D::GetName() {
	return "Texture 2D";
}

}