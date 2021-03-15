#ifndef __CUBE_H__
#define __CUBE_H__

#include <glm/glm.hpp>
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "terrain.h"

class Cube {
    public:
        Cube();
        Cube(float, float, float);

        void init();
        void destroy();

        void setTerrains();

        void draw();

    private:
        const int m_num_vertices   = 36;
        const int m_num_pos_coords = 3 * m_num_vertices;
        const int m_num_tex_coords = 2 * m_num_vertices;

        float m_side;  // width of the cube
        glm::vec3 m_origin; // bottom-left coord of the cube
        
        Terrain m_terrain_front;
        Terrain m_terrain_behind;
        Terrain m_terrain_right;
        Terrain m_terrain_left;
        Terrain m_terrain_top;
        Terrain m_terrain_bot;


        VertexArray m_vao;
        VertexBuffer m_posVbo;
        VertexBuffer m_texVbo;

        void initPosBuffer();
        void initTexBuffer();
};

#endif