#include "../includes/fractal.h"

void	init(t_complex *c, double a, double b)
{
	c->x = a;
	c->y = b;
}

void	add(t_complex *c, t_complex a, t_complex b)
{
	c->x = a.x + b.x;
	c->y = a.y + b.y;
}

void	sqr(t_complex *c, t_complex a)
{
	c->x = (a.x * a.x) - (a.y * a.y);
	c->y = 2 * a.x * a.y;
}

double	mod(t_complex a)
{
	return ((a.x * a.x + a.y * a.y));
}

void	mappoint(t_vars *vars, t_complex *c, int x, int y)
{
	c->x = (x / (double)REDUCED_SCALE + vars->side) / vars->mag;
	c->y = (y / (double)REDUCED_SCALE + vars->vert) / vars->mag;
}
