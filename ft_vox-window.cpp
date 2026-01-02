#include "ft_vox.hpp"

using namespace ft;

Window::Window(void) : m_window(nullptr), m_context(nullptr), m_title(""), m_width(0), m_height(0), m_mousePositionX(0.0), m_mousePositionY(0.0), m_ready(false) { }

Window::Window(const std::string &t) : ft::Window(t, 800, 600) { }

Window::Window(const std::string &t, const size_t w, const size_t h) : m_window(nullptr), m_context(nullptr), m_title(t), m_width(w), m_height(h), m_mousePositionX(0.0), m_mousePositionY(0.0), m_ready(false) {
    this->create(t, w, h);
}

Window::Window(const Window &other) : m_title(other.m_title), m_width(other.m_width), m_height(other.m_height), m_mousePositionX(other.m_mousePositionX), m_mousePositionY(other.m_mousePositionY), m_ready(other.m_ready) { } 

Window::~Window(void) {
    this->quit();
}

const Window &Window::operator = (const Window &other) {
    if (this == &other) { return (*this); }

    this->m_title = other.m_title;
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_mousePositionX = other.m_mousePositionX;
    this->m_mousePositionY = other.m_mousePositionY;
    this->m_ready = other.m_ready;
    return (*this);
}

Window &Window::create(const std::string &t, const size_t w, const size_t h) {
    if (this->m_ready != false) {
        FT_LOGE("window: already created\n");
        return (*this);
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        FT_LOGE("window: %s\n", SDL_GetError());
        return (*this);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    this->m_window = SDL_CreateWindow(t.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!this->m_window) {
        FT_LOGE("window: %s\n", SDL_GetError());
        SDL_Quit();
        
        return (*this);
    }

    this->m_context = SDL_GL_CreateContext(this->m_window);
    if (!this->m_context) {
        FT_LOGE("window: %s\n", SDL_GetError());
        SDL_DestroyWindow(this->m_window);
        SDL_Quit();

        return (*this);
    }

    SDL_GL_MakeCurrent(this->m_window, this->m_context);

    if (!gloadLoadGLLoader((t_gloadLoader) SDL_GL_GetProcAddress)) {
        FT_LOGE("window: failed to load OpenGL\n");
        SDL_GL_DeleteContext(this->m_context);
        SDL_DestroyWindow(this->m_window);
        SDL_Quit();

        return (*this);
    }

    int gl_major = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
    int gl_minor = 0;
    glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
    
    if (gl_major != 4 && gl_minor != 6) {
        FT_LOGE("window: invalid OpenGL version | VERSION: %d.%d (expected: 4.6)\n", gl_major, gl_minor);
        SDL_GL_DeleteContext(this->m_context);
        SDL_DestroyWindow(this->m_window);
        SDL_Quit();

        return (*this);
    }

    this->m_ready = true;
    FT_LOG("window: created successfully | WIDTH: %zu | HEIGHT: %zu\n", w, h);
    FT_LOG("window: OpenGL loaded successfully | VERSION: %d.%d\n", gl_major, gl_minor);
    return (*this);
}

Window &Window::quit(void) {
    if (!this->m_ready) { return (*this); }

    if (!gloadUnloadGL()) { return (*this); }
    if (this->m_context)  { SDL_GL_DeleteContext(this->m_context), this->m_context = 0; }
    if (this->m_window)   { SDL_DestroyWindow(this->m_window), this->m_window = 0; }
    SDL_Quit();

    this->m_ready = false;
    return (*this);
}

Window &Window::clear(const float r, const float g, const float b) {
    return (this->clear((float [4]) { r, g, b, 1.0 } ));
}

Window &Window::clear(const float r, const float g, const float b, const float a) {
    return (this->clear((float [4]) { r, g, b, a } ));
}

Window &Window::clear(const float color[4]) {
    if (!this->m_ready) { return (*this); }

    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return (*this);
}

bool Window::ready(void) const {
    return (this->m_ready);
}

bool Window::shouldQuit(void) {
    if (!this->m_ready) { return (true); }

    SDL_GL_SwapWindow(this->m_window);

    SDL_Event event = { };
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case (SDL_QUIT): { return (true); }

            default: { } break;
        }
    }

    return (false);
}
