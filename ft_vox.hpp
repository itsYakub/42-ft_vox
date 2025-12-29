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

};

#endif /* _ft_vox_hpp_ */
