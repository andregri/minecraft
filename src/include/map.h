#ifndef __MAP_H__
#define __MAP_H__

#include <string>
#include <vector>

class Map {
public:
    Map();
    Map(int rows, int cols, int levels, const std::string& filepath);

    bool isVisible(int row, int col, int e);
    void generate();

    // getters
    int rows();
    int cols();
    int maxElevation();
    int elevation(int row, int col);
    
    // file utilities
    bool load(const std::string&);
    void save();
    void savePPM();

private:
    int m_numRows;
    int m_numCols;
    int m_maxElevation;
    std::string m_filepath;
    std::vector< std::vector<int> > m_elevation;
    
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