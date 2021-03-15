#include "map.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdint>
#include <noise/noise.h>
#include <noise/noiseutils.h>

float map::noise(float x, float y) {
    noise::module::Perlin myModule;
    double value = myModule.GetValue (x, y, 0.0f);
    return static_cast<float>(value);
}

void map::generate(int width, int height, float** elevation) {
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

            // make terraces
            float fudge_factor = 1.2;
            elevation[y][x] = pow(e * fudge_factor, 2);
        }
    }
}

void map::savePPM(const char* filename, int width, int height, float** elevation) {
    //std::cout << "Save" << std::endl;
    std::ofstream outFile(filename, std::ios::binary);
    outFile << "P6\n" << width << " " << height << "\n255\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint8_t color = static_cast<uint8_t>(elevation[y][x] * 255);
            //std::cout << x << " " << y << ": " << elevation[x][y] << " " << color << std::endl;
            outFile << static_cast<char>(color)
                    << static_cast<char>(color)
                    << static_cast<char>(color);
        }
    }
    outFile.close();
}