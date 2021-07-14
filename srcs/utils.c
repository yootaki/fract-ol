#include "../includes/fractal.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	err_print(void)
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
	exit(1);
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
