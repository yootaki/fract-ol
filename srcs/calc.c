#include "../includes/fractal.h"

t_complex	init(double a, double b)
{
	t_complex	c;

	c.x = a;
	c.y = b;
	return (c);
}

t_complex	add(t_complex a, t_complex b)
{
	t_complex	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_complex	sqr(t_complex a)
{
	t_complex	c;

	c.x = pow(a.x, 2.0) - pow(a.y, 2.0);
	c.y = 2 * a.x * a.y;
	return (c);
}

double	mod(t_complex a)
{
	return (sqrt(pow(a.x, 2.0) + pow(a.y, 2.0)));
}

t_complex	mappoint(t_vars *vars, int x, int y)
{
	t_complex	c;

	c.x = (x / (WIDTH / (WIDTH / 100.0)) + vars->side) / vars->mag;
	if (vars->type == 2 || vars->type == 3)
		c.y = (y / (HEIGHT / (HEIGHT / 100.0)) + vars->vert) * -1.0 / vars->mag;
	else
		c.y = (y / (HEIGHT / (HEIGHT / 100.0)) + vars->vert) / vars->mag;
	return (c);
}
