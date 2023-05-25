add_executable(Core 
	Application.cpp
	Buffers.cpp
	Error.cpp
	Renderer.cpp
	VertexArray.cpp
)

target_link_libraries(Core PRIVATE
	glad2
	glfw
	${OPENGL_LIBRARIES}
)
