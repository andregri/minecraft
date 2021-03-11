#ifndef __QUAD__H_
#define __QUAD__H_

#include <glm/glm.hpp>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "terrain.h"

class Quad {
    public:
        Quad();
        Quad(float w, float h);
        Quad(float w, float h, glm::vec3 origin);

        void init();
        void destroy();

        void draw();

    private:
        const int m_num_vertices   = 6;
        const int m_num_pos_coords = 3 * m_num_vertices;
        const int m_num_tex_coords = 2 * m_num_vertices;

        float m_w;  // width of the quad
        float m_h;  // height of the quad
        glm::vec3 m_origin;  // bottom-left coord of the quad
        glm::vec3 m_right;  // vector from the bottom-left vertex to the bottom-right
        glm::vec3 m_up; // vector from the bottom-left vertex to the top-left
        Terrain m_terrain;

        VertexArray m_vao;
        VertexBuffer m_posVbo;
        VertexBuffer m_texVbo;

        void initPosBuffer();
        void initTexBuffer();
};

#endif