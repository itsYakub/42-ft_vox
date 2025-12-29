#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#if !defined (_ft_vox_hpp_)
# define _ft_vox_hpp_ 1
#
# include <string>
# include <cstdint>
# include <cstddef>
# include <cstdlib>
#
# include "SDL2/SDL.h"      /* SDL2 - windowing library */
# include "gload/gload.h"   /* gload.h - OpenGL loader (v.1.0 - v.4.6, ES 1.0 - 3.3) */
#
# if !defined FT_UNUSED
#  define FT_UNUSED(x) ((void) x)
# endif /* FT_UNUSED */

namespace ft {

    class Window;
    class Buffer;
    class VertexBuffer;
    class IndexBuffer;
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

            bool ready(void);
            bool shouldQuit(void);
    };
    
    class Buffer {
        private:
            GLuint m_id;

        public:
            Buffer(void);
            Buffer(const Buffer &);
            ~Buffer(void);

            const Buffer &operator = (const Buffer &);

            Buffer &bind(void) = 0;
            BUffer &unbind(void) = 0;

            GLuint getID(void);
    };
    
    class VertexBuffer : public Buffer {
        public:
            VertexBuffer(void);
            VertexBuffer(const size_t);
            VertexBuffer(const std::vector<float> &);
            VertexBuffer(const float [], const size_t);
            VertexBuffer(const VertexBuffer &);
            ~VertexBuffer(void);

            const VertexBuffer &operator = (const VertexBuffer &);
    };

    class IndexBuffer : public Buffer {
        public:
            IndexBuffer(void);
            IndexBuffer(const size_t);
            IndexBuffer(const std::vector<float> &);
            IndexBuffer(const float [], const size_t);
            IndexBuffer(const IndexBuffer &);
            ~IndexBuffer(void);

            const IndexBuffer &operator = (const IndexBuffer &);
    };

    class Shader {
        private:
            GLuint m_id;

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

            GLuint getID();
    };

    class Texture {
        private:
            GLuint m_id;
            GLsizei m_width;
            GLsizei m_height;
            GLsizei m_channels;

        public:
            Texture(void);
            Texture(const void *);          /* type: raw */
            Texture(const std::string &);   /* type: file */
            Texture(const Texture &);
            ~Texture(void);

            const Texture &operator = (const Texture &);

            GLuint getID(void);
            GLsizei getWidth(void);
            GLsizei getHeight(void);
            GLsizei getChannels(void);
    };

    class Renderer {
        private:
            ft::Window &m_window;

            ft::Shader m_shaderDefault,
                      *m_shaderCurrent;

            ft::Texture m_textureDefault,
                       *m_textureCurrent;

            ft::VertexBuffer *m_vertexBuffer;
            ft::IndexBuffer  *m_indexBuffer;

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

            ft
    };
};

#endif /* _ft_vox_hpp_ */
