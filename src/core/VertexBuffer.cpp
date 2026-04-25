#include <core/VertexBuffer.h>
#include <utils/GLDebug.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    // Generate the Buffer
    GLCall(glGenBuffers(1, &id));
    // Select the Buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    // Fill it with data and put the usage to be for drawing
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    // Free the memory
    GLCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::bind() const {
    // Select the Buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unbind() const {
    // Unselect the Buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int VertexBuffer::getID() const {
    return id;
}