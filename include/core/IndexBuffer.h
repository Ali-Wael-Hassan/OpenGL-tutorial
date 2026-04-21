#pragma once

#include <GL/glew.h>

class IndexBuffer {
private:
    unsigned int id;
    unsigned int m_Count;

public:
    /// @brief Initialize the Index buffer
    /// @param data pointer to the actual data
    /// @param count The number of indices (elements)
    IndexBuffer(const unsigned int* data, unsigned int count);

    /// @brief Free the memory from the GPU
    ~IndexBuffer();

    /// @brief Bind to the GL_ELEMENT_ARRAY_BUFFER slot
    void bind() const;

    /// @brief Unbind the GL_ELEMENT_ARRAY_BUFFER
    void unbind() const;

    /// @brief Gets the number of indices in this buffer
    /// @return count
    unsigned int getCount() const;

    /// @brief Gets the internal OpenGL buffer id
    /// @return id
    unsigned int getID() const;
};