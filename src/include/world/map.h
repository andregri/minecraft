#ifndef __MAP_H__
#define __MAP_H__

#include <string>
#include <vector>

namespace world {

class Map {
public:
    Map();
    Map(int rows, int cols, int levels, const std::string& filepath);

    bool isVisible(int row, int col, int e) const;
    void generate();

    // getters
    int rows() const;
    int cols() const;
    int maxElevation() const;
    int elevation(int row, int col) const;
    int seaLevel() const;
    
    // file utilities
    bool load(const std::string&);
    void save() const;
    void savePPM() const;

private:
    int m_numRows;
    int m_numCols;
    int m_maxElevation;
    int m_seaLevel;
    std::string m_filepath;
    std::vector< std::vector<int> > m_elevation;
    
};

}

#endif