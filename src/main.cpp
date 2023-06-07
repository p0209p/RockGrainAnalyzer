#include "window.hpp"
#include "fileio.hpp"

int main() {
    Window w;
    w.init_window();
    w.run_window();
    w.close_window();
}
