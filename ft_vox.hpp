#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#if !defined (_ft_vox_hpp_)
# define _ft_vox_hpp_ 1
#
# include <string>
# include <fstream>
# include <iostream>
# include <unordered_map>
# include <cstdint>
# include <cstddef>
# include <cstdlib>
#
# include "SDL2/SDL.h"      /* SDL2 - windowing library */
# include "gload/gload.h"   /* gload.h - OpenGL loader (v.1.0 - v.4.6, ES 1.0 - 3.3) */
# include "stb/stb_image.h" /* stb_image.h - image file format loader */
#
# if !defined FT_UNUSED
#  define FT_UNUSED(x) ((void) x)
# endif /* FT_UNUSED */

namespace ft {

    class Window;

    class Buffer;
    class Shader;
    class Texture;

    class Renderer;

    class Window {
        private:
            SDL_Window   *m_window;
            SDL_GLContext m_context;

            std::string m_title;
            size_t m_width;
            size_t m_height;
            
            float m_mousePositionX;
            float m_mousePositionY;

            bool m_ready;

        public:
            Window(void);
            Window(const std::string &);
            Window(const std::string &, const size_t, const size_t);
            Window(const Window &);
            ~Window(void);

            const Window &operator = (const Window &);

            Window &create(const std::string &, const size_t, const size_t);
            Window &quit(void);
            Window &clear(const float, const float, const float);
            Window &clear(const float, const float, const float, const float);
            Window &clear(const float [4]);

            bool ready(void) const;
            bool shouldQuit(void);
    };
    
    class Buffer {
        private:
            GLuint m_id;
            GLsizei m_size;

        public:
            Buffer(void);
            Buffer(const void *, GLsizei);
            Buffer(const Buffer &);
            ~Buffer(void);

            const Buffer &operator = (const Buffer &);

            Buffer &create(const void *, GLsizei);
            Buffer &destroy(void);
            Buffer &setData(const void *, GLsizei, GLsizei);

            GLuint getID(void) const;
            GLsizei getSize(void) const;

            bool ready(void);
    };

    class Shader {
        private:
            GLuint m_id;

            std::unordered_map<std::string, GLint> m_uniforms;

        public:
            Shader(void);
            Shader(const GLchar *, const GLchar *);
            Shader(const Shader &);
            ~Shader(void);

            const Shader &operator = (const Shader &);

            Shader &setVertexShader(const GLchar *);        /* type: raw */
            Shader &setVertexShader(const std::string &);   /* type: file */

            Shader &setFragmentShader(const GLchar *);      /* type: raw */
            Shader &setFragmentShader(const std::string &); /* type: file */

            GLuint getID(void) const;
            GLint getUniform(const std::string &);

            bool ready(void) const;

        private:
            Shader &createProgram(void);
    };

    class Texture {
        private:
            GLuint m_id;
            GLsizei m_width;
            GLsizei m_height;
            GLsizei m_channels;

        public:
            Texture(void);
            Texture(const size_t, const size_t, void *);
            Texture(const size_t, const size_t, const size_t, void *);
            Texture(const std::string &);
            Texture(const Texture &);
            ~Texture(void);

            const Texture &operator = (const Texture &);

            Texture &load(const std::string &);
            Texture &create(const size_t, const size_t, void *);
            Texture &create(const size_t, const size_t, const size_t, void *);
            Texture &destroy(void);

            GLuint getID(void) const;
            GLsizei getWidth(void) const;
            GLsizei getHeight(void) const;
            GLsizei getChannels(void) const;

            bool ready(void) const;
    };

    class Renderer {
        private:
            ft::Window &m_window;

            ft::Shader m_shaderDefault,
                      *m_shaderCurrent;

            ft::Texture m_textureDefault,
                       *m_textureCurrent;

            ft::Buffer *m_vertexBuffer;
            ft::Buffer *m_indexBuffer;

            bool m_ready;

        public:
            Renderer(const ft::Window &);
            Renderer(const Renderer &);
            ~Renderer(void);

            const Renderer &operator = (const Renderer &);

            ft::Shader &getCurrentShader(void) const;
            ft::Shader &getDefaultShader(void) const;
            Renderer &setCurrentShader(const ft::Shader &);

            ft::Texture &getCurrentTexture(void) const;
            ft::Texture &getDefaultTexture(void) const;
            Renderer &setCurrentTexture(const ft::Texture &);

            ft::Buffer &getCurrentVertexBuffer(void) const;
            ft::Buffer &getCurrentIndexBuffer(void) const;
            Renderer &setCurrentVertexBuffer(const ft::Buffer &);
            Renderer &setCurrentIndexBuffer(const ft::Buffer &);

            Renderer &display(void) const;

            bool ready(void) const;
    };
};

#endif /* _ft_vox_hpp_ */
