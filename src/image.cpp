#include "image.hpp"
#include "fileio.hpp"
#include <CL/cl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(std::string filePathName) {
    m_width = 0;
    m_height = 0;
    m_channels = 0;

    unsigned char *imdata = stbi_load(filePathName.c_str(), &m_width, &m_height, &m_channels, STBI_rgb);
    if (imdata != nullptr) {
        m_data = (int *) malloc(sizeof(int[m_width*m_height*m_channels]));
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                int index = (y * m_width + x) * m_channels;
                m_data[index] = static_cast<int>(imdata[index]);
                m_data[index+1] = static_cast<int>(imdata[index + 1]);
                m_data[index+2] = static_cast<int>(imdata[index + 2]);
            }
        }
     stbi_image_free(imdata);
    }
    m_grain_data = m_data;
}

// Cellular automata technique
void Image::cellular_automata(float ϵ) {
    cl_device_id device;
    clGetDeviceIDs(NULL,CL_DEVICE_TYPE_GPU,1,&device,NULL);
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    
}

Image::~Image() {
    free(m_data);
    free(m_grain_data);
}