add_executable(Core 
	Application.cpp
	Renderer.cpp
)

target_link_libraries(Core PRIVATE
	glad2
	glfw
	${OPENGL_LIBRARIES}
)
