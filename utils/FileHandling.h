#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include "../stb_image.h"

inline unsigned char* loadImage(const std::string& filepath, int& width, int& height, int& n_channels)
{
    return stbi_load(filepath.c_str(), &width, &height, &n_channels, 0);
}

inline std::string readFile(const std::string& filename)
{
    std::ifstream file(filename);
    
    if (!file.is_open()) return "";

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    
    return stream.str();
}