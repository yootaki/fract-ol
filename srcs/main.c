#include "../includes/fractal.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");
	vars.side = -3.0;
	vars.vert = -2.0;
	vars.mag = 1.1;
	if (argc == 2 && \
	(argv[1][0] == '1' || argv[1][0] == '2' || argv[1][0] == '4'))
		vars.type = argv[1][0] - '0';
	else if (argc == 4 && argv[1][0] == '3')
	{
		vars.type = argv[1][0] - '0';
		vars.x_param = myatof(argv[2]);
		vars.y_param = myatof(argv[3]);
	}
	else
		err_print();
	mlx_hook(vars.win, 6, 1L << 6, mouse_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_click, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
