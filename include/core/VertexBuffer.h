#pragma once

#include <GL/glew.h>

class VertexBuffer {
private:
    // Buffer ID
    unsigned int id;

public:
    /// @brief Initialze the Vertex buffer
    /// @param data pointer to the actual data buffer
    /// @param size size of the buffer
    VertexBuffer(const void* data, unsigned int size);

    /// @brief Free the memory
    ~VertexBuffer();

    /// @brief Bind to the current running Buffer
    void bind() const;

    /// @brief UnBind from the current runnign Buffer
    void unbind() const;

    /// @brief Gets the buffer id
    /// @return id
    unsigned getID() const;
};