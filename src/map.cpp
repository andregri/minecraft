#include "map.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdint>
#include <noise/noise.h>
#include <noise/noiseutils.h>

Map::Map(int width, int height, const std::string& filepath)
: m_width(width), m_height(height), m_filepath(filepath) {
    // init the elevation array
    m_elevation = new float*[m_height];
    if (m_elevation) {
        for (int y = 0; y < m_height; ++y) {
            m_elevation[y] = new float[m_width];
        }
    } 
}

Map::~Map() {

}

void Map::generate() {
    noise::module::Perlin perlineNoise;
}

map::Color map::toColor(map::Biome biome) {
    switch (biome) {
        case map::Biome::WATER:
            return {0, 0, 255};
        case map::Biome::BEACH:
            return {255, 255, 0};
        case map::Biome::FOREST:
            return {10, 110, 5};
        case map::Biome::JUNGLE:
            return {80, 170, 70};
        case map::Biome::SAVANNAH:
            return {160, 120, 20};
        case map::Biome::DESERT:
            return {85, 100, 100};
        case map::Biome::SNOW:
            return {176, 230, 223};
    }
}

float map::noise(float x, float y) {
    noise::module::Perlin myModule;
    double value = myModule.GetValue (x, y, 0.0f);
    return static_cast<float>(value);
}

void map::generate(int width, int height, int numLevels, int** elevation) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // nx, ny are constrained in [-0.5; +0.5]
            float nx = (float)x / width - 0.5f;
            float ny = (float)y / height - 0.5f;

            // noise with octves
            float e =   1  * map::noise(1 * nx, 1 * ny)
                    + 0.5  * map::noise(2 * nx, 2 * ny)
                    + 0.25 * map::noise(4 * nx, 4 * ny);

            // normalize
            e   /= (1 + 0.5 + 0.25);

            //
            elevation[y][x] = static_cast<int>( pow(e, 2) * numLevels);
        }
    }
}

map::Biome map::biome(float elevation) {
    if (elevation < 0.1) return map::Biome::WATER;
    else if (elevation < 0.2) return map::Biome::BEACH;
    else if (elevation < 0.3) return map::Biome::FOREST;
    else if (elevation < 0.5) return map::Biome::JUNGLE;
    else if (elevation < 0.7) return map::Biome::SAVANNAH;
    else if (elevation < 0.9) return map::Biome::DESERT;
    else return map::Biome::SNOW;
}

void map::savePPM(const char* filename, int width, int height, int numLevels, int** elevation) {
    //std::cout << "Save" << std::endl;
    std::ofstream outFile(filename, std::ios::binary);
    outFile << "P6\n" << width << " " << height << "\n255\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Biome b = biome( (float)elevation[y][x] / numLevels );
            Color color = toColor(b);
            //std::cout << x << " " << y << ": " << elevation[x][y] << " " << color << std::endl;
            outFile << static_cast<char>(color.r)
                    << static_cast<char>(color.g)
                    << static_cast<char>(color.b);
        }
    }
    outFile.close();
}

bool map::isVisible(int row, int col, float e, int rowMax, int colMax, int** elevation) {
    if ( col == 0 || col == colMax || row == 0 || row == rowMax ) {
        return true;
    }

    if (e == elevation[row][col]) {
        return true;
    }

    if (e <= elevation[row-1][col] && // front
        e <= elevation[row+1][col] && // back
        e <= elevation[row][col+1] && // right
        e <= elevation[row][col-1]    // left
    ) {
        return false;
    }

    return true;
}