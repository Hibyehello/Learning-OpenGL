#include "TestTextures3D.h"

#include <Core/VertexLayout.h>
#include <imgui.h>
#include <memory>

namespace Test {

Texture3D::Texture3D()
	: m_proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f)), m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3))), 
	  m_translationA(0, 0, 0), m_translationB(-5, -5, -10) {
	float positions[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	uint32_t indices[] = {
		0, 1, 2,
		5, 4, 3,
		6, 7, 8,
		11, 10, 9,
		12, 13, 14,
		17, 16, 15,
		18, 19, 20,
		23, 22, 21,
		24, 25, 26,
		29, 28, 27,
		30, 31, 32,
		35, 34, 33
	};
	
	m_vao = std::make_unique<VertexArray>();
	//glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f)
	
	m_vbo = std::make_unique<VertexBuffer>(positions, 36 * 5 * sizeof(float));
	VertexLayout vl;
	
	vl.push<float>(3); // Positions
	vl.push<float>(2); // Texture Coordinates
	m_vao->AddBuffer(*m_vbo, vl);

	m_ibo = std::make_unique<IndexBuffer>(indices, 36);
	m_shader = std::make_unique<Shader>("Shaders/vertex.glsl", "Shaders/fragment.glsl");
	m_shader->Bind();

	m_texture = std::make_unique<Texture>("Resources/oglImage.png");
	m_shader->SetUniform1i("u_texture", 0);
	//m_shader->SetUniform4f("u_color", 0.5f, 0.5f, 0.5f, 1.0f);
}

Texture3D::~Texture3D() {
}

void Texture3D::OnUpdate(float deltaTime) {
}

void Texture3D::OnRender() {
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;

	m_texture->Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
		model = glm::rotate(model, glm::radians(m_rotA.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotA.y), glm::vec3(0.0f, 1.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(m_rotA.z), glm::vec3(0.0f, 0.0f, 1.0f)); 
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->Bind();
		m_shader->SetUniformMat4f("u_mvp", mvp);

 		renderer.Draw(*m_vao, *m_ibo, *m_shader);
	}



	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
		model = glm::rotate(model, glm::radians(m_rotB.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotB.y), glm::vec3(0.0f, 1.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(m_rotB.z), glm::vec3(0.0f, 0.0f, 1.0f)); 
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->Bind();
		m_shader->SetUniformMat4f("u_mvp", mvp);

		renderer.Draw(*m_vao, *m_ibo, *m_shader);
	}

}

void Texture3D::OnImGuiRender() {
	ImGui::SliderFloat3("Translation A", &m_translationA.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat3("Rotation XZY A", &m_rotA.x, -180.0f, 180.0f);
	ImGui::SliderFloat3("Translation B", &m_translationB.x, -10.0f, 10.0f);
    ImGui::SliderFloat3("Rotation XYZ B", &m_rotB.x, -180.0f, 180.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

std::string Texture3D::GetName() {
	return "Texture 3D";
}

}
