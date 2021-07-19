
NAME = fractol
DEBUG_DIR = fractol.dSYM
MINILIBX_LINUX = includes/minilibx-linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LINUX_FLAGS =  -Lmlx_Linux -L $(MINILIBX_LINUX) -lmlx_Linux -lXext -lX11 -lm
LINUX_INCLUDE = -I $(MINILIBX_LINUX)

MAC_FLAGS = -L includes/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit
MAC_INCLUDE = -I includes/minilibx_opengl_20191021/

SRCS = srcs/main.c\
srcs/fractal.c\
srcs/calc.c\
srcs/hooks.c\
srcs/utils.c

OBJS = $(SRCS:.c=.o)

# **************************************************
# **************************************************

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

#osがlinuxの場合とその他の場合でコンパイルを分ける
$(NAME): $(MINILIBX_LINUX) $(OBJS)
ifeq ($(shell uname),Linux)
	$(CC) $(CFLAGS) $(SRCS) $(LINUX_INCLUDE) $(LINUX_FLAGS)
else
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MAC_INCLUDE) $(MAC_FLAGS)
endif

#ディレクトリがない場合はgitcloneしてmake
$(MINILIBX_LINUX):
ifeq (,${$(MINILIBX_LINUX)})
	@git clone https://github.com/42Paris/minilibx-linux.git $(MINILIBX_LINUX)
endif
	$(MAKE) -C $(MINILIBX_LINUX)

# **************************************************
# **************************************************

bonus: all

clean:
	rm -f $(OBJS)
	rm -rf $(DEBUG_DIR)
	rm -rf $(MINILIBX_LINUX)

fclean: clean
	rm -f $(NAME)

re: fclean all

# **************************************************
# **************************************************

#セグフォなどのデバッグ用フラグ
debug: CFLAGS += -g3 -fsanitize=address

debug: re

# **************************************************
# **************************************************

.PHONY: all bonus debug fclean clean re
