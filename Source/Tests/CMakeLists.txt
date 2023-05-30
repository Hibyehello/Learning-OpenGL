add_library(Tests
	Test.h
	TestClearColor.h
	TestClearColor.cpp
)

target_link_libraries(Tests PRIVATE
	glad2
	imgui	
)
