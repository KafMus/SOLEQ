#ifndef SOLEQ_MATRIX_MARKET_FILES_PARSER_UUID_0000
#define SOLEQ_MATRIX_MARKET_FILES_PARSER_UUID_0000

#include <SOLEQ/matrix.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>



template<typename T>
std::list<std::list<std::pair<size_t, T>>> getLilFromRealCoordinateSymmetricMatrix(std::string filepath) {
        // Opening file in needed mode
        std::string line;
        std::fstream file(filepath, file.in);
        if (!file.is_open()) {
            std::cout << "MatrixMarketFilesParser:[ERROR:[FAILED-TO-OPEN-FILE]]" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        // Skip comments
        while (std::getline(file, line) && line[0] == '%');
        
        // Declaring variables
        size_t size, number_of_nonzero, i, j;
        T value;
        std::list<std::list<std::pair<size_t, T>>> result;
        
        // Initial parsing
        std::istringstream(line) >> size >> size >> number_of_nonzero;
        result.resize(size);
        
        
        // Main parsing
        for (size_t z = 0; z < number_of_nonzero; ++z) {
            std::getline(file, line);
            std::istringstream(line) >> i >> j >> value;
            
            if (0 == value) {
                continue;
            }
            --i;
            --j;
            auto iter = result.begin();
            std::advance(iter, i);
            (*iter).push_back(std::make_pair(j, value));
            if (i != j) {
                iter = result.begin();
                std::advance(iter, j);
                (*iter).push_back(std::make_pair(i, value));
            }
        }
        
        
        file.close();
        return result;
}

template<typename T>
kfsoleq::Matrix getMatrixFromRealCoordinateSymmetricMatrix(std::string filepath) {
        // Opening file in needed mode
        std::string line;
        std::fstream file(filepath, file.in);
        if (!file.is_open()) {
            std::cout << "MatrixMarketFilesParser:[ERROR:[FAILED-TO-OPEN-FILE]]" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        // Skip comments
        while (std::getline(file, line) && line[0] == '%');
        
        // Declaring variables
        size_t size, number_of_nonzero, i, j;
        T value;
        
        // Initial parsing
        std::istringstream(line) >> size >> size >> number_of_nonzero;
        kfsoleq::Matrix result(size, size);
        
        
        // Main parsing
        for (size_t z = 0; z < number_of_nonzero; ++z) {
            std::getline(file, line);
            std::istringstream(line) >> i >> j >> value;
            
            if (0 == value) {
                continue;
            }
            --i;
            --j;
            result(i, j) = value;
            if (i != j) {
                result(j, i) = value;
            }
        }
        
        
        file.close();
        return result;
}



#endif
