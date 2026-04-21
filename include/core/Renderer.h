#pragma once

#include <GL/glew.h>
#include <core/VertexArray.h>
#include <core/IndexBuffer.h>
#include <core/Shader.h>

class Renderer {
public:
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};