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

# define WIDTH  600
# define HEIGHT 600
# define I_MAX  25
# define RADIUS 2

# ifdef __linux
#  define KEY_LEFT       65361
#  define KEY_RIGHT      65363
#  define KEY_DOWN       65364
#  define KEY_UP         65362
#  define KEY_SCROLLUP   5
#  define KEY_SCROLLDOWN 4
#  define KEY_ESC        65307
# else
#  define KEY_LEFT       123
#  define KEY_RIGHT      124
#  define KEY_DOWN       125
#  define KEY_UP         126
#  define KEY_A          0
#  define KEY_D          2
#  define KEY_SCROLLUP   5
#  define KEY_SCROLLDOWN 4
#  define KEY_ESC        53
# endif

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
t_complex	init(double a, double b);
t_complex	add(t_complex a, t_complex b);
t_complex	sqr(t_complex a);
double		mod(t_complex a);
t_complex	mappoint(t_vars *vars, int x, int y);

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
int			ft_isdigit(int c);
double		myatof(char *s);

#endif
