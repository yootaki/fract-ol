#include "../includes/fractal.h"

int	create_trgb(t_vars *vars, int i)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = 0;
	if (i == I_MAX)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		r = sin(0.6 * i + 0) * 127 + 128 + vars->color;
		g = sin(0.6 * i + 2 * M_PI / 3) * 127 + 128 + vars->color;
		b = sin(0.6 * i + 4 * M_PI / 3) * 127 + 128 + vars->color;
	}
	return (t << 24 | r << 16 | g << 8 | b);
}

int	mandelbrot(t_vars *vars, int ix, int iy)
{
	t_complex	c;
	t_complex	z0;
	t_complex	z1;
	int			i;

	c = mappoint(vars, ix, iy);
	z0 = init(0.0, 0.0);
	z1 = init(0.0, 0.0);
	i = 0;
	while (++i < I_MAX)
	{
		z1 = add(sqr(z0), c);
		if (mod(z1) > RADIUS)
			break ;
		z0 = z1;
	}
	return (create_trgb(vars, i));
}

int	julia(t_vars *vars, int ix, int iy)
{
	t_complex	c;
	t_complex	z0;
	t_complex	z1;
	int			i;

	if (vars->type == 2)
		c = mappoint(vars, vars->x_mouse, vars->y_mouse);
	else
		c = init(vars->x_param, vars->y_param * -1.0);
	z0 = mappoint(vars, ix, iy);
	i = 0;
	while (++i < I_MAX)
	{
		z1 = add(sqr(z0), c);
		if (mod(z1) > RADIUS)
			break ;
		z0 = z1;
	}
	return (create_trgb(vars, i));
}

int	burningship(t_vars *vars, int ix, int iy)
{
	t_complex	c;
	t_complex	z0;
	t_complex	z1;
	int			i;

	c = mappoint(vars, ix, iy);
	z0 = init(0.0, 0.0);
	z1 = init(0.0, 0.0);
	i = 0;
	while (++i < I_MAX)
	{
		z1 = add(sqr(z0), c);
		if (mod(z1) > RADIUS)
			break ;
		z0.x = fabs(z1.x);
		z0.y = fabs(z1.y);
	}
	return (create_trgb(vars, i));
}

void	fractal(t_vars *vars)
{
	int		ix;
	int		iy;
	int		color;

	mlx_clear_window(vars->mlx, vars->win);
	iy = -1;
	while (++iy < HEIGHT)
	{
		ix = -1;
		while (++ix < WIDTH)
		{
			if (vars->type == 1)
				color = mandelbrot(vars, ix, iy);
			else if (vars->type == 2 || vars->type == 3)
				color = julia(vars, ix, iy);
			else if (vars->type == 4)
				color = burningship(vars, ix, iy);
			my_mlx_pixel_put(vars, ix, iy, color);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}
