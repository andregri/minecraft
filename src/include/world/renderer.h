#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "shader.h"
#include "cube.h"
#include "world/map.h"
#include "world/biome.h"
#include "world/terrain_cube.h"

namespace world {

class Renderer {
public:
    explicit Renderer(const world::Map&);

    void draw(const Shader&);

private:
    Renderer(); // no default constructor
    TerrainCube computeTerrain(Biome biome, int elevation, int maxElevation);
    std::vector<Cube> m_cubes;
};

}

#endif