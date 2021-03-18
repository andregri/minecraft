#ifndef __BIOME_H__
#define __BIOME_H__

#include "world/terrain.h"
#include "world/terrain_cube.h"

namespace world {

enum class Biome {WATER, BEACH, FOREST, JUNGLE, SAVANNAH, DESERT, SNOW};

Biome biome(int elevation, int maxElevation);

}

#endif /* __BIOME_H__ */