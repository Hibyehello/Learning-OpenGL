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

target_include_directories(Core PUBLIC ${CMAKE_SOURCE_DIR}/Source/Core)

target_link_libraries(Core PRIVATE
	glad2
	glfw
	glm
	stb_image
	${OPENGL_LIBRARIES}
)
