#ifndef __TERRAIN_CUBE_H__
#define __TERRAIN_CUBE_H__

#include "world/terrain.h"

namespace world {

struct TerrainCube {
    Terrain front;
    Terrain back;
    Terrain right;
    Terrain left;
    Terrain bottom;
    Terrain top;
};

const TerrainCube TC_Dirt  {Dirt, Dirt, Dirt, Dirt, Dirt, Dirt};
const TerrainCube TC_Water {Water, Water, Water, Water, Water, Water};
const TerrainCube TC_Sand  {Sand, Sand, Sand, Sand, Sand, Sand};
const TerrainCube TC_Gravel  {Gravel, Gravel, Gravel, Gravel, Gravel, Gravel};
const TerrainCube TC_Grass  {SideGrass, SideGrass, SideGrass, SideGrass, Dirt, LightGreenCloth};
const TerrainCube TC_DarkGrass {SideGrass, SideGrass, SideGrass, SideGrass, Dirt, DarkGreenCloth};
const TerrainCube TC_DirtSnow {SideSnow, SideSnow, SideSnow, SideSnow, Dirt, Snow};
const TerrainCube TC_Ice {Snow, Snow, Snow, Snow, Snow, Snow};

}

#endif