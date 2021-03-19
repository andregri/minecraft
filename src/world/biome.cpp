#include "world/biome.h"
#include "world/terrain_cube.h"

namespace world {

Biome biome(int elevation, int maxElevation)
{
    float e = (float)elevation / maxElevation;
    if (e < 0.2) return Biome::BEACH;
    else if (e < 0.3) return Biome::FOREST;
    else if (e < 0.5) return Biome::JUNGLE;
    else if (e < 0.7) return Biome::SAVANNAH;
    else if (e < 0.9) return Biome::DESERT;
    else return Biome::SNOW;
}

}