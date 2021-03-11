#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>

struct Terrain {
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

    Terrain(int row, int col) {
        if(row >= 0 && row < num_rows && col >= 0 && col < num_cols) {
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

extern Terrain Stone;
extern Terrain Grass;
extern Terrain Dirt;
extern Terrain Grass2;
extern Terrain Planks;

#endif