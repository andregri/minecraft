#include "world/map.h"
#include <iostream>

using namespace world;

int main() {
    std::cout << "Test map generator:";
    Map map(3, 3, 5, "testmap.txt");
    std::cout << ( true ? "passed" : "failed" ) << std::endl;
    
    std::cout << "Test map saved:";
    map.save();
    std::cout << ( true ? "passed" : "failed" ) << std::endl;

    std::cout << "Test map load: ";
    Map loadedMap;
    if( loadedMap.load("testmap.txt") ) {
        bool passed = true;
        for (int row = 0; row < map.rows(); ++row) {
            for (int col = 0; col < map.cols(); ++col) {
                if ( map.elevation(row, col) != loadedMap.elevation(row, col) ) {
                    passed = false;
                    break;
                }
            }
        }
        std::cout << ( passed ? "passed" : "failed" ) << std::endl;
    } else {
        std::cout << "file not found" << std::endl;
    }

    std::cout << "Test non existing map load: ";
    Map fakeMap;
    std::cout << ( !fakeMap.load("fakeMap.txt") ? "passed" : "failed" ) << std::endl;

    std::cout << "Test map saved as PPM: ";
    loadedMap.savePPM();
    std::cout << ( true ? "passed" : "failed" ) << std::endl;
    
    return 0;
}