#pragma once

#include <core/VertexBuffer.h>
#include <core/VertexBufferLayout.h>

class VertexArray {
private:
    unsigned int id;
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

    unsigned int getID() const;
};