#pragma once

#include <iostream>

#include <glad/glad.h>

#define GLASSERT(x) if (!(x)) abort();

#define GLCall(x) Error::GLClearError();\
	x;\
	GLASSERT(Error::GLLogCall(#x, __FILE__, __LINE__))

namespace Error {

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

}; // Namespace Error
