#ifndef __CUBE_H__
#define __CUBE_H__

#include <memory>
#include <glm/glm.hpp>
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "world/terrain_cube.h"

class Cube {
    public:
        Cube();
        Cube(float, float, float);
        Cube(const Cube&);
        Cube& operator = (const Cube&);

        void init();
        void destroy();

        void setTexture(const world::TerrainCube&);

        void draw();

    private:
        const int m_num_vertices   = 36;
        const int m_num_pos_coords = 3 * m_num_vertices;
        const int m_num_tex_coords = 2 * m_num_vertices;

        float m_side;  // width of the cube
        glm::vec3 m_origin; // bottom-left coord of the cube
        
        std::unique_ptr<world::TerrainCube> m_texCube;


        VertexArray m_vao;
        VertexBuffer m_posVbo;
        VertexBuffer m_texVbo;

        void initPosBuffer();
        void initTexBuffer();
};

#endif