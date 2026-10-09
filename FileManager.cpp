#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool FileManager::saveToFile(const std::string& filename,
                              const std::string& content) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "Error: Could not open file \"" << filename
                  << "\" for writing.\n";
        return false;
    }
    outFile << content;
    outFile.close();

    if (outFile.fail()) {
        std::cout << "Error: Failed to write to file \"" << filename << "\".\n";
        return false;
    }
    return true;
}

std::string FileManager::loadFromFile(const std::string& filename,
                                       bool& success) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open file \"" << filename
                  << "\" for reading.\n";
        success = false;
        return "";
    }

    // Read the entire file into a string using a stringstream
    std::stringstream buffer;
    buffer << inFile.rdbuf();

    if (inFile.bad()) {
        std::cout << "Error: Failed to read file \"" << filename << "\".\n";
        success = false;
        return "";
    }

    success = true;
    return buffer.str();
}

