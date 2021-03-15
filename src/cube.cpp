#include "cube.h"
#include <GL/glew.h>

Cube::Cube() :
    m_side(16.0f), m_origin(0.0f, 0.0f, 0.0f),
    m_terrain_front(Grass2), m_terrain_behind(Grass2),
    m_terrain_top(Grass), m_terrain_bot(Dirt),
    m_terrain_left(Grass2), m_terrain_right(Grass2),
    m_vao(), m_posVbo(), m_texVbo() {}

Cube::Cube(float x, float y, float z) :
    m_side(16.0f), m_origin(x, y, z),
    m_terrain_front(Grass2), m_terrain_behind(Grass2),
    m_terrain_top(Grass), m_terrain_bot(Dirt),
    m_terrain_left(Grass2), m_terrain_right(Grass2),
    m_vao(), m_posVbo(), m_texVbo() {}

void Cube::init() {
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

void Cube::destroy() {
    m_posVbo.destroy();
    m_texVbo.destroy();
    m_vao.destroy();
}

void Cube::draw() {
    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);
    m_vao.unbind();
}

void Cube::initPosBuffer() {
    m_posVbo.init();
    m_posVbo.bind();

    glm::vec3 up(0.0f, m_side, 0.0f);
    glm::vec3 right(m_side, 0.0f, 0.0f);
    glm::vec3 depth(0.0f, 0.0f, m_side);

    // Front
    glm::vec3 front_bot_left  = m_origin;
    glm::vec3 front_top_left  = m_origin + up;
    glm::vec3 front_bot_right = m_origin + right;
    glm::vec3 front_top_right = front_bot_right + up;

    // Behind
    glm::vec3 behind_bot_left  = front_bot_left  + depth;
    glm::vec3 behind_top_left  = front_top_left  + depth;
    glm::vec3 behind_bot_right = front_bot_right + depth;
    glm::vec3 behind_top_right = front_top_right + depth;

    // Right
    glm::vec3 right_bot_left  = m_origin + right;
    glm::vec3 right_top_left  = right_bot_left + up;
    glm::vec3 right_bot_right = right_bot_left + depth;
    glm::vec3 right_top_right = right_bot_right + up;

    // Left
    glm::vec3 left_bot_left  = m_origin + depth;
    glm::vec3 left_top_left  = left_bot_left + up;
    glm::vec3 left_bot_right = m_origin;
    glm::vec3 left_top_right = left_bot_right + up;

    // Top
    glm::vec3 top_bot_left  = m_origin + up;
    glm::vec3 top_top_left  = top_bot_left + depth;
    glm::vec3 top_bot_right = top_bot_left + right;
    glm::vec3 top_top_right = top_bot_right + depth;

    // Bottom
    glm::vec3 bot_bot_left  = top_bot_left  - up;
    glm::vec3 bot_top_left  = top_top_left  - up;
    glm::vec3 bot_bot_right = top_bot_right - up;
    glm::vec3 bot_top_right = top_top_right - up;

    float pos_coords_data[m_num_pos_coords] {
        // Front
        front_top_left.x,  front_top_left.y,  front_top_left.z,   // top left
        front_top_right.x, front_top_right.y, front_top_right.z,  // top right
        front_bot_right.x, front_bot_right.y, front_bot_right.z,  // bottom right
        front_top_left.x,  front_top_left.y,  front_top_left.z,   // top left
        front_bot_right.x, front_bot_right.y, front_bot_right.z,  // bottom right
        front_bot_left.x,  front_bot_left.y,  front_bot_left.z,    // bottom left
        // Behind
        behind_top_left.x,  behind_top_left.y,  behind_top_left.z,   // top left
        behind_top_right.x, behind_top_right.y, behind_top_right.z,  // top right
        behind_bot_right.x, behind_bot_right.y, behind_bot_right.z,  // bottom right
        behind_top_left.x,  behind_top_left.y,  behind_top_left.z,   // top left
        behind_bot_right.x, behind_bot_right.y, behind_bot_right.z,  // bottom right
        behind_bot_left.x,  behind_bot_left.y,  behind_bot_left.z,    // bottom left
        // Right
        right_top_left.x,  right_top_left.y,  right_top_left.z,   // top left
        right_top_right.x, right_top_right.y, right_top_right.z,  // top right
        right_bot_right.x, right_bot_right.y, right_bot_right.z,  // bottom right
        right_top_left.x,  right_top_left.y,  right_top_left.z,   // top left
        right_bot_right.x, right_bot_right.y, right_bot_right.z,  // bottom right
        right_bot_left.x,  right_bot_left.y,  right_bot_left.z,    // bottom left
        // Left
        left_top_left.x,  left_top_left.y,  left_top_left.z,   // top left
        left_top_right.x, left_top_right.y, left_top_right.z,  // top right
        left_bot_right.x, left_bot_right.y, left_bot_right.z,  // bottom right
        left_top_left.x,  left_top_left.y,  left_top_left.z,   // top left
        left_bot_right.x, left_bot_right.y, left_bot_right.z,  // bottom right
        left_bot_left.x,  left_bot_left.y,  left_bot_left.z,    // bottom left
        // Top
        top_top_left.x,  top_top_left.y,  top_top_left.z,   // top left
        top_top_right.x, top_top_right.y, top_top_right.z,  // top right
        top_bot_right.x, top_bot_right.y, top_bot_right.z,  // bottom right
        top_top_left.x,  top_top_left.y,  top_top_left.z,   // top left
        top_bot_right.x, top_bot_right.y, top_bot_right.z,  // bottom right
        top_bot_left.x,  top_bot_left.y,  top_bot_left.z,    // bottom left
        // Bottom
        bot_top_left.x,  bot_top_left.y,  bot_top_left.z,   // top left
        bot_top_right.x, bot_top_right.y, bot_top_right.z,  // top right
        bot_bot_right.x, bot_bot_right.y, bot_bot_right.z,  // bottom right
        bot_top_left.x,  bot_top_left.y,  bot_top_left.z,   // top left
        bot_bot_right.x, bot_bot_right.y, bot_bot_right.z,  // bottom right
        bot_bot_left.x,  bot_bot_left.y,  bot_bot_left.z    // bottom left
    };
    
    m_posVbo.loadVertices(m_num_pos_coords, pos_coords_data);
    m_posVbo.unbind();
}

void Cube::initTexBuffer() {
    m_texVbo.init();
    m_texVbo.bind();

    float tex_coords_data[m_num_tex_coords] {
        // front
        m_terrain_front.top_lx_u, m_terrain_front.top_lx_v, // top left
        m_terrain_front.top_rx_u, m_terrain_front.top_rx_v, // top right
        m_terrain_front.bot_rx_u, m_terrain_front.bot_rx_v, // bottom right
        m_terrain_front.top_lx_u, m_terrain_front.top_lx_v, // top left
        m_terrain_front.bot_rx_u, m_terrain_front.bot_rx_v, // bottom right
        m_terrain_front.bot_lx_u, m_terrain_front.bot_lx_v,  // bottom left
        // behind
        m_terrain_behind.top_lx_u, m_terrain_behind.top_lx_v, // top left
        m_terrain_behind.top_rx_u, m_terrain_behind.top_rx_v, // top right
        m_terrain_behind.bot_rx_u, m_terrain_behind.bot_rx_v, // bottom right
        m_terrain_behind.top_lx_u, m_terrain_behind.top_lx_v, // top left
        m_terrain_behind.bot_rx_u, m_terrain_behind.bot_rx_v, // bottom right
        m_terrain_behind.bot_lx_u, m_terrain_behind.bot_lx_v,  // bottom left
        // right
        m_terrain_right.top_lx_u, m_terrain_right.top_lx_v, // top left
        m_terrain_right.top_rx_u, m_terrain_right.top_rx_v, // top right
        m_terrain_right.bot_rx_u, m_terrain_right.bot_rx_v, // bottom right
        m_terrain_right.top_lx_u, m_terrain_right.top_lx_v, // top left
        m_terrain_right.bot_rx_u, m_terrain_right.bot_rx_v, // bottom right
        m_terrain_right.bot_lx_u, m_terrain_right.bot_lx_v,  // bottom left
        // left
        m_terrain_left.top_lx_u, m_terrain_left.top_lx_v, // top left
        m_terrain_left.top_rx_u, m_terrain_left.top_rx_v, // top right
        m_terrain_left.bot_rx_u, m_terrain_left.bot_rx_v, // bottom right
        m_terrain_left.top_lx_u, m_terrain_left.top_lx_v, // top left
        m_terrain_left.bot_rx_u, m_terrain_left.bot_rx_v, // bottom right
        m_terrain_left.bot_lx_u, m_terrain_left.bot_lx_v,  // bottom left
        // top
        m_terrain_top.top_lx_u, m_terrain_top.top_lx_v, // top left
        m_terrain_top.top_rx_u, m_terrain_top.top_rx_v, // top right
        m_terrain_top.bot_rx_u, m_terrain_top.bot_rx_v, // bottom right
        m_terrain_top.top_lx_u, m_terrain_top.top_lx_v, // top left
        m_terrain_top.bot_rx_u, m_terrain_top.bot_rx_v, // bottom right
        m_terrain_top.bot_lx_u, m_terrain_top.bot_lx_v,  // bottom left
        // bottom
        m_terrain_bot.top_lx_u, m_terrain_bot.top_lx_v, // top left
        m_terrain_bot.top_rx_u, m_terrain_bot.top_rx_v, // top right
        m_terrain_bot.bot_rx_u, m_terrain_bot.bot_rx_v, // bottom right
        m_terrain_bot.top_lx_u, m_terrain_bot.top_lx_v, // top left
        m_terrain_bot.bot_rx_u, m_terrain_bot.bot_rx_v, // bottom right
        m_terrain_bot.bot_lx_u, m_terrain_bot.bot_lx_v  // bottom left
    };

    m_texVbo.loadVertices(m_num_tex_coords, tex_coords_data);
    m_texVbo.unbind();
}