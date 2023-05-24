#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Renderer {
private:
	uint32_t m_buffer;
public:
	Renderer();
	~Renderer() = default;

	void onUpdate();

	static uint32_t CreateShader(const std::string& vertex, const std::string& fragment);
	static uint32_t CompileShader(uint32_t type, const std::string& src);
};
