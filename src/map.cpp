#include "map.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdint>
#include <noise/noise.h>
#include <noise/noiseutils.h>

Map::Map()
: m_numRows(0), m_numCols(0), m_maxElevation(0), m_filepath("") {}

Map::Map(int rows, int cols, int levels, const std::string& filepath)
: m_numRows(rows), m_numCols(cols), m_maxElevation(levels),
 m_filepath(filepath)
{
    generate();
}

/*
    Determine if a cube located at (row,col,e) is visible or not due to the 
    surrounding cubes 
*/
bool Map::isVisible(int row, int col, int e)
{
    if ( col == 0 || col == m_numCols - 1 || row == 0 || row == m_numRows - 1 ) {
        return true;
    }

    if ( e == m_elevation.at(row).at(col) ) {
        return true;
    }

    if (e <= m_elevation.at(row-1).at(col) && // front
        e <= m_elevation.at(row+1).at(col) && // back
        e <= m_elevation.at(row).at(col+1) && // right
        e <= m_elevation.at(row).at(col-1)    // left
    ) {
        return false;
    }

    return true;
}

int Map::rows() {
    return m_numRows;
}

int Map::cols() {
    return m_numCols;
}



int Map::elevation(int row, int col)
{
    return m_elevation.at(row).at(col);
}

void Map::generate() {
    noise::module::Perlin perlineNoise;

    for (int row = 0; row < m_numRows; ++row) {
        std::vector<int> rowValues;
        for (int col = 0; col < m_numCols; ++col) {
            // nc, nr are constrained in [-0.5; +0.5]
            double nc = static_cast<double>(col) / m_numCols - 0.5f;
            double nr = static_cast<double>(row) / m_numRows - 0.5f;

            // noise with octves
            double e =      1  * perlineNoise.GetValue(1 * nc, 1 * nr, 0.0f)
                        + 0.5  * perlineNoise.GetValue(2 * nc, 2 * nr, 0.0f)
                        + 0.25 * perlineNoise.GetValue(4 * nc, 4 * nr, 0.0f);

            // normalize
            e   /= (1 + 0.5 + 0.25);

            //
            rowValues.push_back( static_cast<int>( pow(e, 2) * m_maxElevation) );
        }
        m_elevation.push_back( rowValues );
    }
}

bool Map::load(const std::string& filepath)
{
    m_filepath = filepath;

    std::ifstream inFile(m_filepath);

    if (!inFile) return false; 
    
    std::string s;
    
    inFile >> s;
    m_numRows = std::stoi(s);

    inFile >> s;
    m_numCols = std::stoi(s);

    inFile >> s;
    m_maxElevation = std::stoi(s);

    for (int row = 0; row < m_numRows; ++row) {
        std::vector<int> rowValues;
        for (int col = 0; col < m_numCols; ++col) {
            inFile >> s;
            rowValues.push_back( std::stoi(s) );
        }
        m_elevation.push_back( rowValues );
    }

    return true;
}

void Map::save()
{
    std::ofstream outFile(m_filepath);

    outFile << m_numRows << '\n';
    outFile << m_numCols << '\n';
    outFile << m_maxElevation << '\n';
    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            outFile << m_elevation.at(row).at(col) << '\n';
        }
    }
}

void Map::savePPM()
{
    std::ofstream outFile(m_filepath + ".ppm", std::ios::binary);
    outFile << "P6\n" << m_numCols << " " << m_numRows << "\n" << m_maxElevation << "\n";
    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            uint8_t color = static_cast<uint8_t>( (float)m_elevation.at(row).at(col) / m_maxElevation * 255 );
            outFile << static_cast<char>(color)
                    << static_cast<char>(color)
                    << static_cast<char>(color);
        }
    }
    outFile.close();
}

/**/


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