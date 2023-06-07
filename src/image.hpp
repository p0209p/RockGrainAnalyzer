#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <CL/opencl.hpp>

class Image {

private:
    int *m_data;
    int *m_grain_data; // Stores the modified image for rendering
    int m_width;
    int m_height;
    int m_channels;

public:
    Image(std::string filePathName);
    ~Image();
    void cellular_automata(float ϵ);
};

#endif
