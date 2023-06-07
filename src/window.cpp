#include "window.hpp"

Window::Window() {
  m_window = nullptr;
  m_width = m_height = 0;
}

void Window::init_window() {
  glfwInit();
  glfwWindowHint(GLFW_RESIZABLE,true);
  m_window = glfwCreateWindow(1366,768,"Grain Analyzer",NULL,NULL);
  if(m_window == nullptr) {
    std::cout << "Window cannot be opened !";
    exit(1);
  }
  glfwMakeContextCurrent(m_window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD";
        exit(1);
    }
  glViewport(0,0,m_width,m_height);
}

void Window::run_window() {

  bool show_automata_para = false;
  bool show_texture = false;
  bool show_grains = false;


  std::string filePathName;

  // ImGui configuration, see imgui_demo.cpp for details
  const char* glsl_version = "#version 460";
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
  io.Fonts->AddFontFromFileTTF("assets/fonts/JuliaMono-Regular.ttf",20.0);

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  std::unique_ptr<Image> img = std::make_unique<Image> ("");

  // Rendering the two triangles for using the texture

  std::string shader = read_shader("assets/shaders/vertex_shader.vert");
  const char* vertex_shader_source = shader.c_str();
  shader = read_shader("assets/shaders/fragment_shader.frag");
  const char* fragment_shader_source = shader.c_str();

  unsigned int VBO;
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
  }

  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  unsigned int shader_program;
  shader_program = glCreateProgram();
  glAttachShader(shader_program,vertex_shader);
  glAttachShader(shader_program,fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(shader_program, 512, NULL, infoLog);

  }

  if(!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
  }

  glUseProgram(shader_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);


  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void *)0);
  // The first parameter is the location ID defined in the vertex shader
  // The second parameter is the size, since we have vec3 so it is composed of 3 values

  glEnableVertexArrayAttrib(0);

  float l = 0.95f;
  float vertices[18] = {
    -l,-l,0.0f,
    l,-l,0.0f,
    -l,l,0.0f,
    l,-l,0.0f,
    l,l,0.0f,
    -l,l,0.0f
  };

  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
          if (ImGui::MenuItem("Open")) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*,.bmp,.png,.jpeg,.jpg,.tiff", ".");
          }
          if (ImGui::MenuItem("Exit")) {
            break;
          }
          ImGui::EndMenu();
      }
      if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))  {
        if (ImGuiFileDialog::Instance()->IsOk())  {
          filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
          img = std::make_unique<Image> (filePathName);
          //std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
        }
        ImGuiFileDialog::Instance()->Close();
      }
      if (ImGui::BeginMenu("Analyze")) {
        if(ImGui::MenuItem("Cellular Automata Grain Boundary")) {
          ImGui::Begin("Cellular Automata Parameters");
          float ϵ;
          ImGui::SliderFloat("float", &ϵ, 0.0f, 25.0f);
          ImGui::End();
          img->cellular_automata(ϵ);
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Clear")) {
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Export to CSV")) {
        // TODO Export the grain information to CSV for further analysis
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    ImGui::Render();

    glClearColor(0.22f,0.22f,0.22f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    glfwSwapBuffers(m_window);
  }
}

void Window::close_window() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(m_window);
  glfwTerminate();
}
