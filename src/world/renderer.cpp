#include "world/renderer.h"
#include "world/biome.h"

namespace world {

Renderer::Renderer(const world::Map& map)
{
    for (int z = 0; z < map.rows(); ++z) {
        for (int x = 0; x < map.cols(); ++x) {
            
            int localMaxElevation = map.elevation(z, x);
            for (int e = 0; e <= localMaxElevation; ++e) {
            
                // Add only outer cubes
                if ( map.isVisible(z, x, e) ) {
                    Cube c(x*16.0f, e*16.0f, z*16.0f);

                    // Set the texture based on the biome
                    Biome b = biome(e, map.maxElevation());
                    TerrainCube tc = computeTerrain(b, e, localMaxElevation);
                    c.setTexture(tc);

                    c.init();
                    m_cubes.push_back(c);
                }
            }

            // Add water cubes
            if ( localMaxElevation < map.seaLevel() ) {
                for (int e = localMaxElevation + 1; e < map.seaLevel(); ++e) {
                    Cube c(x*16.0f, e*16.0f, z*16.0f);
                    c.setTexture(TC_Water);
                    c.init();
                    m_cubes.push_back(c);
                }
            }
        }
    }
}

void Renderer::draw(const Shader& shader)
{
    shader.Use();
    for (auto c : m_cubes) {
        c.draw();
    }
}

TerrainCube Renderer::computeTerrain(Biome biome, int elevation, int maxElevation)
{
    switch (biome)
    {
    case Biome::BEACH:
        return TC_Sand;

    case Biome::FOREST:
        if (elevation < maxElevation) {
            return TC_Dirt;
        } else {
            return TC_Grass;
        }

    case Biome::JUNGLE:
        if (elevation < maxElevation) {
            return TC_Dirt;
        } else {
            return TC_DarkGrass;
        }

    case Biome::SAVANNAH:
        return TC_Gravel;

    case Biome::DESERT:
        return TC_Ice;
    
    default:
        break;
    }
}

}