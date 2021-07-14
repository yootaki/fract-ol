
NAME = a.out

CC = gcc

LINUX_FLAGS = -Wall -Wextra -Werror -Lmlx_Linux -L includes/minilibx-linux/ -lmlx_Linux -lXext -lX11 -lm
LINUX_INCLUDE = -I includes/minilibx-linux/

MAC_FLAGS = -L includes/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit
MAC_INCLUDE = -I includes/minilibx_opengl_20191021/

SRCS = srcs/main.c\
srcs/fractal.c\
srcs/calc.c\
srcs/hooks.c\
srcs/utils.c

DEBUG_DIR = a.out.dSYM


all:
ifeq ($(shell uname),Linux)
	$(CC) $(SRCS) $(LINUX_INCLUDE) $(LINUX_FLAGS)
else
	$(CC) $(SRCS) $(MAC_INCLUDE) $(MAC_FLAGS)
endif

bonus: all

clean:
	rm -rf $(DEBUG_DIR)

fclean: clean
	rm -f $(NAME)

debug: CC += -g3 -fsanitize=address

debug: re

re: fclean all

.PHONY: all bonus debug fclean clean re
