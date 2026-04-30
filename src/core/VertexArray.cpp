#include <core/VertexArray.h>
#include <utils/GLDebug.h>

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &id));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &id));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();

    vb.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        
        GLCall(glEnableVertexAttribArray(i));

        GLCall(glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalize,
            layout.getStride(),
            (const void*) (size_t)offset
        ));

        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(id));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}

unsigned int VertexArray::getID() const {
    return id;
}