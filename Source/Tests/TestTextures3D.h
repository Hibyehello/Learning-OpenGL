#pragma once

#include "Test.h"
#include <Core/Buffers.h>
#include <Core/Error.h>
#include <Core/Renderer.h>
#include <Core/Shader.h>
#include <Core/Texture.h>
#include <Core/VertexArray.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>


namespace Test {

class Texture3D : public Test {
private:
	std::unique_ptr<VertexArray> m_vao;
	std::unique_ptr<VertexBuffer> m_vbo;
	std::unique_ptr<IndexBuffer> m_ibo;
	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Texture> m_texture;
	
	glm::mat4 m_proj;
	glm::mat4 m_view;
	glm::vec3 m_translationA, m_translationB;
	glm::vec3 m_rotA, m_rotB;
public: 
	Texture3D();
	~Texture3D();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;

	std::string GetName() override;

};

}

