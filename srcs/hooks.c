#include "../includes/fractal.h"

int	mouse_hook(int x, int y, t_vars *vars)
{
	vars->x_mouse = x;
	vars->y_mouse = y;
	fractal(vars);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		free_mlx(vars);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_UP)
		vars->vert -= MOVE_DIST;
	else if (keycode == KEY_DOWN)
		vars->vert += MOVE_DIST;
	else if (keycode == KEY_LEFT)
		vars->side -= MOVE_DIST;
	else if (keycode == KEY_RIGHT)
		vars->side += MOVE_DIST;
	else if (keycode == KEY_A && vars->color >= COLOR_CHANGE)
		vars->color -= COLOR_CHANGE;
	else if (keycode == KEY_D && vars->color <= COLOR_MAX)
		vars->color += COLOR_CHANGE;
	else if (keycode == KEY_S && vars->i_max > INIT_IMAX)
		vars->i_max -= CHANGE_IMAX;
	else if (keycode == KEY_W && vars->i_max < MAX_IMAX)
		vars->i_max += CHANGE_IMAX;
	fractal(vars);
	return (0);
}

int	mouse_click(int button, int x, int y, t_vars *vars)
{
	t_complex	c;
	double		n;

	c = mappoint(vars, x, y);
	n = 0.0;
	if (button == KEY_SCROLLUP)
	{
		n = vars->mag * MAGNIFICATION;
		vars->mag += n;
		vars->side -= n * c.x / ((double)WIDTH * vars->mag) - n * c.x;
		vars->vert -= n * c.y / ((double)HEIGHT * vars->mag) - n * c.y;
	}
	else if (button == KEY_SCROLLDOWN)
	{
		if (vars->mag > 0.1)
			n = vars->mag * MAGNIFICATION;
		vars->mag -= n;
		vars->side += n * c.x / ((double)WIDTH * vars->mag) - n * c.x;
		vars->vert += n * c.y / ((double)HEIGHT * vars->mag) - n * c.y;
	}
	else if (button != KEY_SCROLLDOWN &&\
	button != KEY_SCROLLLEFT && button != KEY_SCROLLRIGHT)
		printf("(%f,%f)\n", c.x, c.y);
	fractal(vars);
	return (0);
}

int	cross_button(t_vars *vars)
{
	free_mlx(vars);
	exit(EXIT_SUCCESS);
	return (0);
}
