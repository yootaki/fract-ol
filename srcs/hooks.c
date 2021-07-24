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
		exit(0);
	}
	else if (keycode == KEY_UP)
		vars->vert -= 0.5;
	else if (keycode == KEY_DOWN)
		vars->vert += 0.5;
	else if (keycode == KEY_LEFT)
		vars->side -= 0.5;
	else if (keycode == KEY_RIGHT)
		vars->side += 0.5;
	else if (keycode == KEY_A && vars->color >= 16)
		vars->color -= 16;
	else if (keycode == KEY_D && vars->color <= 2147483631)
		vars->color += 16;
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
		n = vars->mag * 0.5;
		vars->mag += n;
		vars->side -= n * c.x / (600.0 * vars->mag) - n * c.x;
		vars->vert -= n * c.y / (600.0 * vars->mag) - n * c.y;
	}
	else if (button == KEY_SCROLLDOWN)
	{
		if (vars->mag > 0.1)
			n = vars->mag * 0.5;
		vars->mag -= n;
		vars->side += n * c.x / (600.0 * vars->mag) - n * c.x;
		vars->vert += n * c.y / (600.0 * vars->mag) - n * c.y;
	}
	else if (button != 4 && button != 6 && button != 7)
		printf("(%f,%f)\n", c.x, c.y);
	fractal(vars);
	return (0);
}

int	cross_button(t_vars *vars)
{
	free_mlx(vars);
	exit(0);
	return (0);
}
