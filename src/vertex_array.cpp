#include "vertex_array.h"
#include <GL/glew.h>

VertexArray::VertexArray() : m_id(0) {}

void VertexArray::init() {
    glGenVertexArrays(1, &m_id);
}

void VertexArray::destroy() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() {
    if (m_id > 0) {
        glBindVertexArray(m_id);
    } else {
        throw "vao not initialized\n";
    }
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

// Getters
unsigned int VertexArray::getID() {
    return m_id;
}