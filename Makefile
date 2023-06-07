os = $(shell uname -s)
cc = clang++
cflags += -std=c++17 -O3 -Wall
cflags += -Ilib/glad/include -Ilib/glfw/include -Ilib/imgui/ -Ilib/imgui/backends/
cflags += -Ilib/ImGuiFileDialog/ -Ilib/stb/
ldflags = lib/glfw/src/libglfw3.a lib/glad/src/glad.o

src = $(wildcard src/*.cpp) $(wildcard lib/imgui/*.cpp) lib/imgui/backends/imgui_impl_glfw.cpp
src += lib/imgui/backends/imgui_impl_opengl3.cpp lib/ImGuiFileDialog/ImGuiFileDialog.cpp
obj = $(src:.cpp=.o)

.PHONY: all clean dir ga lib

lib:
	cd lib/glfw && cmake . && make
	cd lib/glad && gcc -c src/glad.c -Iinclude/ -o src/glad.o
dir:
	mkdir -p bin


clean:
	rm -r $(obj)
	rm -r bin/ga

ga: $(obj)
	$(cc) -o bin/ga $^ $(ldflags)
	./bin/ga

%.o: %.cpp
	$(cc) -o $@ -c $< $(cflags)
