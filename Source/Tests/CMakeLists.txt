add_library(Tests
	Test.h
	TestClearColor.h
	TestMenu.h
	TestTextures.h
	TestClearColor.cpp
	TestMenu.cpp
	TestTextures.cpp
)

target_link_libraries(Tests PRIVATE
	glad2
	imgui	
)
