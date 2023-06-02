add_library(Tests
	Test.h
	TestClearColor.h
	TestMenu.h
	TestTextures2D.h
	TestTextures3D.h
	TestClearColor.cpp
	TestMenu.cpp
	TestTextures2D.cpp
	TestTextures3D.cpp
)

target_link_libraries(Tests PRIVATE
	glad2
	imgui	
)
