#include "TestClearColor.h"

#include <Core/Error.h>
#include <imgui.h>

namespace Test {

ClearColor::ClearColor()
	: m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

ClearColor::~ClearColor() {
}

void ClearColor::OnUpdate(float deltaTime) {
}

void ClearColor::OnRender() {
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void ClearColor::OnImGuiRender() {
	ImGui::ColorEdit4("Clear Color", m_ClearColor);
}

std::string ClearColor::GetName() {
	return "Clear Color";
}

}
