#include <core/IndexBuffer.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
    : m_Count(count) 
{
    // Generate a buffer and store the ID
    glGenBuffers(1, &id);
    
    // Binds it to the current running buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    
    // Put the data inside the Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    // Clean up the GPU memory
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() const {
    // Set the running buffer to be this buffer 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const {
    // Reset the binding slot
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const {
    return m_Count;
}

unsigned int IndexBuffer::getID() const {
    return id;
}