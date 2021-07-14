
NAME = fractal
CC = gcc

CFLAGS = -L includes/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit

INCLUDE = -I includes/minilibx_opengl_20191021/

SRCS = srcs/main.c\
srcs/fractal.c\
srcs/calc.c\
srcs/hooks.c\
srcs/utils.c


all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
