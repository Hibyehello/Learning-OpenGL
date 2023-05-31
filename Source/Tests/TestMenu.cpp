#include "TestMenu.h"
#include "imgui.h"

namespace Test {

Menu::Menu(Test*& current_test) 
	: m_current_test(current_test) {

}

Menu::~Menu(){
}

void Menu::OnImGuiRender() {
	for(const auto& test : m_tests) {
		Test* t = test();
		if(ImGui::Button(t->GetName().c_str()))
			m_current_test = t;
	}
	
}	

std::string Menu::GetName() {
	return "Tests Menu";
}

}
