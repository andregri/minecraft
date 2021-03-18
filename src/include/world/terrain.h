#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>

namespace world {

struct Color {
    float r, g, b;
    float alpha;
};

struct Terrain {
    Color color;

    // position of the terrain texture in the texture_atlas
    float top_lx_u;
    float top_lx_v;
    float top_rx_u;
    float top_rx_v;
    float bot_rx_u;
    float bot_rx_v;
    float bot_lx_u;
    float bot_lx_v;

    static const int num_rows = 16;
    static const int num_cols = 16;

    Terrain(int row, int col, Color color) {
        if(row >= 0 && row < num_rows && col >= 0 && col < num_cols) {
            this->color = color;

            top_lx_u = (float)col     /num_cols;
            top_lx_v = (float)(row+1) /num_rows;

            top_rx_u = (float)(col+1) /num_cols;
            top_rx_v = (float)(row+1) /num_rows;
            
            bot_rx_u = (float)(col+1) /num_cols;
            bot_rx_v = (float)row     /num_rows;
            
            bot_lx_u = (float)col     /num_cols;
            bot_lx_v = (float)row     /num_rows;
        }
    }
};

constexpr Color white {1.0f, 1.0f, 1.0f, 1.0f};
constexpr Color green {0.0f, 1.0f, 0.0f, 1.0f};
constexpr Color blue_opaque {0.0f, 0.0f, 1.0f, 0.5f};

const Terrain Dirt      (15, 2, white);
const Terrain Water     (11, 3, blue_opaque);
const Terrain Sand      (4, 0, white);
const Terrain Gravel    (15, 0, white);
const Terrain Grass     (15, 0, green);
const Terrain SideGrass (15, 3, white);
const Terrain Snow      (11, 2, white);
const Terrain SideSnow  (11, 4, white);
const Terrain LightGreenCloth (6, 2, white);
const Terrain DarkGreenCloth  (6, 1, white);

}

#endif