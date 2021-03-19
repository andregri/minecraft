#include "world/map.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdint>
#include <noise/noise.h>
#include <noise/noiseutils.h>


namespace world {

Map::Map() :
    m_numRows(0),
    m_numCols(0),
    m_maxElevation(0),
    m_seaLevel(0),
    m_filepath("") {}

Map::Map(int rows, int cols, int levels, const std::string& filepath) :
    m_numRows(rows),
    m_numCols(cols),
    m_maxElevation(levels),
    m_seaLevel( levels/10 ),
    m_filepath(filepath)
{
    generate();
}

/*
    Determine if a cube located at (row,col,e) is visible or not due to the 
    surrounding cubes 
*/
bool Map::isVisible(int row, int col, int e) const
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

int Map::rows() const {
    return m_numRows;
}

int Map::cols() const {
    return m_numCols;
}

int Map::maxElevation() const {
    return m_maxElevation;
}

int Map::elevation(int row, int col) const 
{
    return m_elevation.at(row).at(col);
}

int Map::seaLevel() const {
    return m_seaLevel;
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

    m_seaLevel = m_maxElevation / 10;

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

void Map::save() const
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

void Map::savePPM() const
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

}