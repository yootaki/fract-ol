#include "../includes/fractal.h"

void	make_image(t_vars *vars, t_data *img)
{
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (img->img == NULL)
	{
		printf("\n\x1b[41m Failed to malloc \
in mlx_new_image. \x1b[49m\n");
		err_print(vars);
	}
	img->addr = mlx_get_data_addr(img->img, \
	&img->bits_per_pixel, &img->line_length, &img->endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

double	myatof(char *s)
{
	double	sign;
	double	n;
	double	i;

	sign = 1;
	n = 0;
	i = 1;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		s++;
		sign = -1;
	}
	while (ft_isdigit(*s))
	{
		n = n * 10 + *s - '0';
		s++;
	}
	if (*s == '.')
	{
		while (ft_isdigit(*++s))
			n += (*s - '0') * (i *= 0.1);
	}
	return (n * sign);
}
