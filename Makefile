# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= ft_vox

# ========

NAME		= $(MK_ROOT)$(MK_NAME)

# ========

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++11 -O3 -ggdb3
LXXFLAGS	= -lSDL2

# ========

OBJS		= $(SRCS:.cpp=.o)
SRCS		= $(MK_ROOT)ft_vox.cpp				\
			  $(MK_ROOT)ft_vox-window.cpp		\
			  $(MK_ROOT)ft_vox-shader.cpp		\
			  $(MK_ROOT)ft_vox-texture.cpp		\
			  $(MK_ROOT)ft_vox-buffer.cpp		\
			  $(MK_ROOT)ft_vox-vertexarray.cpp	\
			  $(MK_ROOT)ft_vox-renderer.cpp		\
			  $(MK_ROOT)ft_vox-deps.cpp

# ========

.PHONY : all

all : $(NAME)

.PHONY : clean

clean :
	rm -f $(OBJS)

.PHONY : fclean

fclean : clean
	rm -f $(NAME)

.PHONY : re

re : fclean all

# ========

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LXXFLAGS)

$(OBJS) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# ========
