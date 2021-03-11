#include "vertex_buffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer() : m_id(0) {}


void VertexBuffer::init() {
    glGenBuffers(1, &m_id);
}

void VertexBuffer::destroy() {
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::loadVertices(int num, float* vertices) {
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num, vertices, GL_DYNAMIC_DRAW);
}

// Getters
unsigned int VertexBuffer::getID() {
    return m_id;
}