
NAME = a.out

CC = gcc

LINUX_FLAGS = -Wall -Wextra -Werror -Lmlx_Linux -L includes/minilibx-linux/ -lmlx_Linux -lXext -lX11 -lm

MAC_FLAGS = -L includes/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit

LINUX_INCLUDE = -I includes/minilibx-linux/ -I includes/

MAC_INCLUDE = -I includes/minilibx_opengl_20191021/

SRCS = srcs/main.c\
srcs/fractal.c\
srcs/calc.c\
srcs/hooks.c\
srcs/utils.c


all:
	$(CC) $(SRCS) $(LINUX_FLAGS) $(LINUX_INCLUDE)

mac:
	$(CC) $(SRCS) $(MAC_FLAGS) $(MAC_INCLUDE)

bonus: all

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all mac bonus clean re
