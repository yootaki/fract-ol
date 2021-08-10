#ifndef FRACTAL_H
# define FRACTAL_H

# ifdef __linux
#  include "./minilibx-linux/mlx.h"
#  include "./minilibx-linux/mlx_int.h"
# else
#  include "./minilibx_opengl_20191021/mlx.h"
# endif

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/* window */
# define WIDTH  600		/* 横幅 */
# define HEIGHT 600		/* 高さ */

/* calc */
# define DIV_VALUE       2			/* 判定値 */
# define REDUCED_SCALE   100.0		/* 縮尺 */
# define INIT_X_POSITION -3.0		/* x初期位置 */
# define INIT_Y_POSITION -3.0		/* y初期位置 */
# define MOVE_DIST       0.5		/* 移動距離 */
# define INIT_MAG        1.0		/* 初期倍率 */
# define MAGNIFICATION   0.5		/* 拡大縮小倍率 */
# define INIT_IMAX       25			/* 計算回数初期値 */
# define MAX_IMAX        100		/* 計算回数最大値 */
# define CHANGE_IMAX     5			/* 回数増減幅 */

/* color */
# define INIT_COLOR   0
# define COLOR_CHANGE 16
# define COLOR_MAX    1600

/* keycode */
# ifdef __linux
#  define KEY_LEFT        65361
#  define KEY_RIGHT       65363
#  define KEY_DOWN        65364
#  define KEY_UP          65362
#  define KEY_A           97
#  define KEY_D           100
#  define KEY_S           115
#  define KEY_W           119
#  define KEY_SCROLLUP    5
#  define KEY_SCROLLDOWN  4
#  define KEY_SCROLLLEFT  6
#  define KEY_SCROLLRIGHT 7
#  define KEY_ESC         65307
#  define BUTTON_CROSS    33
# else
#  define KEY_LEFT        123
#  define KEY_RIGHT       124
#  define KEY_DOWN        125
#  define KEY_UP          126
#  define KEY_A           0
#  define KEY_D           2
#  define KEY_S           1
#  define KEY_W           13
#  define KEY_SCROLLUP    5
#  define KEY_SCROLLDOWN  4
#  define KEY_SCROLLLEFT  6
#  define KEY_SCROLLRIGHT 7
#  define KEY_ESC         53
#  define BUTTON_CROSS    17
# endif

/* fractal number */
enum
{
	MANDELBROT = 1,
	JULIA_MOUSE,
	JULIA_PARAM,
	BURNINGSHIP
};

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		type;
	double	x_param;
	double	y_param;
	int		x_mouse;
	int		y_mouse;
	int		color;
	double	side;
	double	vert;
	double	mag;
	int		i_max;
}t_vars;

typedef struct s_complex
{
	double	x;
	double	y;
}t_complex;

/* main */
void		err_print(void);
void		free_mlx(t_vars *vars);
int			args_check(t_vars *vars, int argc, char **argv);
int			vars_init(t_vars *vars);
int			make_image(t_vars *vars);

/* calcs */
void		init(t_complex *c, double a, double b);
void		add(t_complex *c, t_complex a, t_complex b);
void		sqr(t_complex *c, t_complex a);
double		mod(t_complex a);
void		mappoint(t_vars *vars, t_complex *c, int x, int y);

/* hooks */
int			mouse_hook(int x, int y, t_vars *vars);
int			mouse_click(int button, int x, int y, t_vars *vars);
int			key_hook(int keycode, t_vars *vars);
int			cross_button(t_vars *vars);

/* fractal */
int			create_trgb(t_vars *vars, int i);
int			mandelbrot(t_vars *vars, int ix, int iy);
int			julia(t_vars *vars, int ix, int iy);
int			burningship(t_vars *vars, int ix, int iy);
void		fractal(t_vars *vars);

/* utils */
void		my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
double		myatof(char *s);
int			ft_strcmp_f(const char *s1, const char *s2);

#endif
