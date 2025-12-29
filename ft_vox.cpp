#include "ft_vox.hpp"

int main(int ac, char **av) {
    FT_UNUSED(ac);
    FT_UNUSED(av);

    ft::Window window = ft::Window("SDL2 - OpenGL4.6 - ft_vox");
    if (!window.ready()) { return (1); }

    do {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } while (!window.shouldQuit());

    return (0);
}
