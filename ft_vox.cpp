#include "ft_vox.hpp"

const GLfloat g_vertices[] = {
    0.0, 0.0, 0.0,    1.0, 1.0, 1.0, 1.0,    0.0, 0.0,
    1.0, 0.0, 0.0,    1.0, 1.0, 1.0, 1.0,    1.0, 0.0,
    0.0, 1.0, 0.0,    1.0, 1.0, 1.0, 1.0,    0.0, 1.0,
    1.0, 1.0, 0.0,    1.0, 1.0, 1.0, 1.0,    1.0, 1.0,
};

const GLuint g_indices[] = {
    0, 1, 2,
    1, 2, 3
};

int main(int ac, char **av) {
    FT_UNUSED(ac);
    FT_UNUSED(av);

    ft::Window window = ft::Window("SDL2 - OpenGL4.6 - ft_vox");
    if (!window.ready()) { return (1); }

    ft::Shader shader = ft::Shader();
    int u_proj = shader.getUniform("u_proj"); FT_UNUSED(u_proj);
    int u_view = shader.getUniform("u_view"); FT_UNUSED(u_view);

    ft::Buffer vertex_buffer = ft::Buffer(g_vertices, sizeof(g_vertices));
    ft::Buffer index_buffer = ft::Buffer(g_indices, sizeof(g_indices));

    uint32_t data = 0xffffffff;
    ft::Texture texture = ft::Texture(1, 1, &data);

    do {
        window.clear(0.1, 0.1, 0.1, 1.0);
    } while (!window.shouldQuit());

    return (0);
}
