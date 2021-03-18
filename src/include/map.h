#ifndef __MAP_H__
#define __MAP_H__

#include <string>

class Map {
public:
    Map(int width, int height, const std::string& filepath);
    Map(const Map&);
    Map(Map&&);
    Map& operator = (const Map&);
    Map& operator = (const Map&&);
    ~Map();

    void load();
    void generate();
    void save();

private:
    Map();
    int m_width;
    int m_height;
    std::string m_filepath;
    float** m_elevation;
};

namespace map {
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    enum class Biome {WATER, BEACH, FOREST, JUNGLE, SAVANNAH, DESERT, SNOW};

    Color toColor(Biome);

    // Generate a noise value given the coordinates x,y
    float noise(float x, float y);

    // Generate an elevation map width x height
    void generate(int width, int height, int numLevels, int** elevation);

    // Return biome based on elevation
    Biome biome(float elevation);

    // Save a map to PPM file
    void savePPM(const char* filename, int width, int height, int numLevels, int** elevation);
    
    // Determine if a cube located at (x,y,z) is visible or not
    bool isVisible(int row, int col, float e, int rowMax, int colMax, int** elevation);
}

#endif