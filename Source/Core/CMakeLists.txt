add_executable(Core 
	Application.cpp
	Buffers.cpp
	Error.cpp
	Renderer.cpp
	Shader.cpp
	Texture.cpp
	VertexArray.cpp
	Application.h
	Buffers.h
	Error.h
	Renderer.h
	Shader.h
	Texture.h
	VertexArray.h
)

target_include_directories(Core PUBLIC 
	${CMAKE_SOURCE_DIR}/Source
)

target_link_libraries(Core PRIVATE
	Tests
	glad2
	glfw
	glm
	stb_image
	imgui
	${OPENGL_LIBRARIES}
)
