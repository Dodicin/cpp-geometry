#pragma once

#include <GL/glew.h>
#include <assert.h> 

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define GLCall(x) GLClearError();\
    x;\
    assert(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& iv, const Shader& shader) const;
};