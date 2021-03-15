#ifndef __MAP_H__
#define __MAP_H__

namespace map {
    // Generate a noise value given the coordinates x,y
    float noise(float x, float y);

    // Generate an elevation map width x height
    void generate(int width, int height, float** elevation);

    // Save a map to PPM file
    void savePPM(const char* filename, int width, int height, float** elevation);
}

#endif