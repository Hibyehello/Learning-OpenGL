#pragma once

#include "Test.h"
#include "TestClearColor.h"

#include <vector>
#include <functional>


namespace Test {

class Menu : public Test{
private:
	Test*& m_current_test;
	std::vector<std::function<Test*()>> m_tests;
public:
	Menu(Test*& current_test);
	~Menu();

	void OnImGuiRender() override;

	template<typename T>
	void RegisterTest() {
		m_tests.push_back([](){ return new T; });
	}	

	std::string GetName() override;
};

} 
