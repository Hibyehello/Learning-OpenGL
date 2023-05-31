#pragma once

#include <string>

namespace Test {
	
class Test {
public:
	Test() {}
	virtual ~Test() {}

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnImGuiRender() {}

	virtual std::string GetName() { return ""; }

public:
	bool m_state;
};

}
