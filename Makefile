
CC = gcc

CFLAGS = -Wall -Wextra -Werror -Lmlx_Linux -L includes/minilibx-linux/ -lmlx_Linux -lXext -lX11 -lm -g -fsanitize=address

INCLUDE = -I includes/minilibx-linux/ -I includes/

SRCS = srcs/main.c\
srcs/fractal.c\
srcs/calc.c\
srcs/hooks.c\
srcs/utils.c


all:
	$(CC) $(SRCS) $(CFLAGS) $(INCLUDE)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
