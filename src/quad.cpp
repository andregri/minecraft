#include "quad.h"
#include <GL/glew.h>

Quad::Quad() :
    m_w(1.0f), m_h(1.0f), m_origin(0.0f, 0.0f, 0.0f),
    m_right(1.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
    m_terrain(Dirt),
    m_vao(), m_posVbo(), m_texVbo() {}

Quad::Quad(float w, float h) :
    m_w(w), m_h(h), m_origin(0.0f, 0.0f, 0.0f),
    m_right(1.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
    m_terrain(Dirt),
    m_vao(), m_posVbo(), m_texVbo() {}

Quad::Quad(float w, float h, glm::vec3 origin) :
    m_w(w), m_h(h), m_origin(origin),
    m_right(1.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
    m_terrain(Dirt),
    m_vao(), m_posVbo(), m_texVbo() {}

void Quad::init() {
    m_vao.init();
    m_vao.bind();

    initPosBuffer();
    initTexBuffer();
    
    // position attribute
    m_posVbo.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    m_posVbo.unbind();

    // texture coord attribute
    m_texVbo.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    m_texVbo.unbind();
    
    m_vao.unbind();
}

void Quad::destroy() {
    m_posVbo.destroy();
    m_texVbo.destroy();
    m_vao.destroy();
}

void Quad::draw() {
    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_vao.unbind();
}

void Quad::initPosBuffer() {
    m_posVbo.init();
    m_posVbo.bind();

    int num_vertices = 18;

    glm::vec3 bot_left = m_origin;
    glm::vec3 top_left = m_origin + m_up * m_h;
    glm::vec3 bot_right = m_origin + m_right * m_w;
    glm::vec3 top_right = bot_right + m_up * m_h;

    float pos_coords_data[num_vertices] {
        // Triangle 1
        top_left.x,  top_left.y,  top_left.z,   // top left
        top_right.x, top_right.y, top_right.z,  // top right
        bot_right.x, bot_right.y, bot_right.z,  // bottom right
        // Triangle 2
        top_left.x,  top_left.y,  top_left.z,   // top left
        bot_right.x, bot_right.y, bot_right.z,  // bottom right
        bot_left.x,  bot_left.y,  bot_left.z    // bottom left
    };
    
    m_posVbo.loadVertices(num_vertices, pos_coords_data);
    m_posVbo.unbind();
}

void Quad::initTexBuffer() {
    m_texVbo.init();
    m_texVbo.bind();

    int num_vertices = 12;

    float tex_coords_data[num_vertices] {
        // Triangle 1
        m_terrain.top_lx_u, m_terrain.top_lx_v, // top left
        m_terrain.top_rx_u, m_terrain.top_rx_v, // top right
        m_terrain.bot_rx_u, m_terrain.bot_rx_v, // bottom right
        // Triangle 2
        m_terrain.top_lx_u, m_terrain.top_lx_v, // top left
        m_terrain.bot_rx_u, m_terrain.bot_rx_v, // bottom right
        m_terrain.bot_lx_u, m_terrain.bot_lx_v  // bottom left
    };

    m_texVbo.loadVertices(num_vertices, tex_coords_data);
    m_texVbo.unbind();
}