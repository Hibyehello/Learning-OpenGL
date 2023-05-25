#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Error.h"

#include "Renderer.h"

class Application {
private:
	GLFWwindow* m_window;
	uint32_t m_width;
	uint32_t m_height;
	const char* m_title;
	GLFWmonitor* m_monitor;
	Renderer* m_renderer;
public:
	Application(uint32_t width, uint32_t height, const char* title);
	~Application() = default;

	int Run();

	void SetMonitor(GLFWmonitor* monitor);
	void SetMonitorFromCurrent();
};
