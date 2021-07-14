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
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_desplay(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	else
	{
		if (keycode == KEY_UP)
			vars->vert -= 0.5;
		else if (keycode == KEY_DOWN)
			vars->vert += 0.5;
		else if (keycode == KEY_LEFT)
			vars->side -= 0.5;
		else if (keycode == KEY_RIGHT)
			vars->side += 0.5;
		fractal(vars);
	}
	return (0);
}

int	mouse_click(int button, int x, int y, t_vars *vars)
{
	t_complex	c;

	c = mappoint(vars, x, y);
	if (button == KEY_SCROLLUP)
	{
		vars->mag += 1.0;
		vars->side -= (1.0 - vars->mag) * c.x / (600.0 * vars->mag) - c.x;
		vars->vert -= (1.0 - vars->mag) * c.y / (400.0 * vars->mag) - c.y;
	}
	else if (button == KEY_SCROLLDOWN && vars->mag >= 1.1)
	{
		vars->mag -= 1.0;
		vars->side += (1.0 - vars->mag) * c.x / (600.0 * vars->mag) - c.x;
		vars->vert += (1.0 - vars->mag) * c.y / (400.0 * vars->mag) - c.y;
	}
	else if (button != 4 && button != 6 && button != 7)
		printf("(%f,%f)\n", c.x, c.y);
	fractal(vars);
	return (0);
}
