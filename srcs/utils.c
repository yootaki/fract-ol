#include "../includes/fractal.h"
#include "../includes/libft/libft.h"

void	err_print(void)
{
	printf("\x1b[33m\n\
-< Give a number as an argument. >-\n\
\n\
 ex) $ ./fractol 1\n\
     $ ./fractol 2\n\
     $ ./fractol 3 -0.8 0.156\n\
     $ ./fractol 4\n\
\n\
 1 : Mandelbrot\n\
 2 : Julia with mouse coordinate\n\
 3 : Julia with params\n\
 4 : Burning Ship\n\
-----------------------------------\n\n\
\x1b[39m");
}

void	free_mlx(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
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

int	ft_strcmp_f(const char *s1, const char *s2)
{
	int	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
