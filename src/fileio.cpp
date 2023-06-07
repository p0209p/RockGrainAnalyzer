#include "fileio.hpp"

std::string read_shader(std::string filename) {
    std::ifstream f(filename.c_str());
    if (!f) {
        exit(1);
    }

    // https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
    std::string data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();
    return data;
}

std::string read_kernel_function(std::string filename) {
    std::ifstream f(filename.c_str());
    if (!f) {
        exit(1);
    }
    std::string data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();
    return data;
}
