#pragma once

#include<GL/glew.h>


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__)) //# makes it string, __Name__ calls that variable

void GLClearError();

bool GLCheckError(const char* function, const char* file, int line);