#include "../includes/fractal.h"

int	argv_check(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && s[i] != '.')
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (s[i])
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	err_print(t_vars *vars)
{
	printf("\x1b[33m\n\
-< Give a number as an argument. >-\n\
\n\
 ex) $ ./a.out 1\n\
     $ ./a.out 2\n\
     $ ./a.out 3 -0.8 0.156\n\
     $ ./a.out 4\n\
\n\
 1 : Mandelbrot\n\
 2 : Julia with mouse coordinate\n\
 3 : Julia with params\n\
 4 : Burning Ship\n\
-----------------------------------\n\n\
\x1b[39m");
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(1);
}

void	vars_init(t_vars *vars, int argc, char **argv)
{
	vars->side = -3.0;
	vars->vert = -2.0;
	vars->mag = 1.2;
	if (argc == 2 && \
	(argv[1][0] == '1' || argv[1][0] == '2' || argv[1][0] == '4'))
		vars->type = argv[1][0] - '0';
	else if (argc == 4 && \
	argv[1][0] == '3' && argv_check(argv[2]) && argv_check(argv[3]))
	{
		vars->type = argv[1][0] - '0';
		vars->x_param = myatof(argv[2]);
		vars->y_param = myatof(argv[3]);
	}
	else
		err_print(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (0);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fract-ol");
	if (vars.win == NULL)
		return (0);
	vars_init(&vars, argc, argv);
	mlx_mouse_hook(vars.win, mouse_click, &vars);
	mlx_hook(vars.win, 6, 1L << 6, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
