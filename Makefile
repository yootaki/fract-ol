
EXE = ./a.out
DEBUG_DIR = a.out.dSYM
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

#osがlinuxの場合とその他の場合でコンパイルを分ける
all: $(MINILIBX_LINUX)
ifeq ($(shell uname),Linux)
	$(CC) $(CFLAGS) $(SRCS) $(LINUX_INCLUDE) $(LINUX_FLAGS)
else
	$(CC) $(CFLAGS) $(SRCS) $(MAC_INCLUDE) $(MAC_FLAGS)
endif

#ディレクトリがない場合はgitcloneしてmake
$(MINILIBX_LINUX):
ifeq (,${$(MINILIBX_LINUX)})
	@git clone https://github.com/42Paris/minilibx-linux.git $(MINILIBX_LINUX)
endif
	$(MAKE) -C $(MINILIBX_LINUX)

bonus: all

clean:
	rm -rf $(DEBUG_DIR)
	rm -rf $(MINILIBX_LINUX)

fclean: clean
	rm -f $(EXE)

#セグフォなどのデバッグ用フラグ
debug: CFLAGS += -g3 -fsanitize=address

debug: re

re: fclean all

.PHONY: all bonus debug fclean clean re
