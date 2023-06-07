#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ImGuiFileDialog.h"
#include "image.hpp"
#include "fileio.hpp"
#include <memory>
#include <algorithm>

class Window {
  private:
        GLFWwindow *m_window;
        int m_width;
        int m_height;
  public:
        Window();
        void init_window();
        void run_window();
        void close_window();
};

#endif
