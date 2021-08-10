#include "../includes/fractal.h"
#include "../includes/libft/libft.h"

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

int	args_check(t_vars *vars, int argc, char **argv)
{
	if (argc == 2 && (!ft_strcmp_f(argv[1], "1") || \
	!ft_strcmp_f(argv[1], "2") || !ft_strcmp_f(argv[1], "4")))
		vars->type = argv[1][0] - '0';
	else if (argc == 4 && !ft_strcmp_f(argv[1], "3") && \
	argv_check(argv[2]) && argv_check(argv[3]))
	{
		vars->type = argv[1][0] - '0';
		vars->x_param = myatof(argv[2]);
		vars->y_param = myatof(argv[3]);
	}
	else
		return (1);
	return (0);
}

int	vars_init(t_vars *vars)
{
	vars->color = INIT_COLOR;
	vars->side = INIT_X_POSITION;
	vars->vert = INIT_Y_POSITION;
	vars->mag = INIT_MAG;
	vars->i_max = INIT_IMAX;
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (1);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (vars->win == NULL)
		return (1);
	return (0);
}

int	make_image(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (vars->img == NULL)
	{
		printf("\n\x1b[41m Failed to malloc \
in mlx_new_image. \x1b[49m\n");
		return (1);
	}
	vars->addr = mlx_get_data_addr(vars->img, \
	&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_bzero(&vars, 17);
	if (args_check(&vars, argc, argv))
	{
		err_print();
		return (1);
	}
	if (vars_init(&vars) || make_image(&vars))
	{
		free_mlx(&vars);
		return (1);
	}
	fractal(&vars);
	mlx_mouse_hook(vars.win, mouse_click, &vars);
	mlx_hook(vars.win, 6, 1L << 6, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, BUTTON_CROSS, 1L << 17, cross_button, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
