#pragma once

#include<GL/glew.h>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__)) //# makes it string, __Name__ calls that variable

void GLClearError();

bool GLCheckError(const char* function, const char* file, int line);

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};