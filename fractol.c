#include "./minilibx_mms_20200219/mlx.h"
#include <math.h>
#include <stdio.h>

#define HEIGHT 800
#define WIDTH 800
#define I_MAX 25

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

//メモリオフセットを計算
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// 計算する関数たち
typedef struct s_complex
{
	double x;
	double y;
}t_complex;

//初期化
void init(t_complex *a)
{
	a->x = 0;
	a->y = 0;
}

// 足し算
t_complex add(t_complex a, t_complex b){
	t_complex c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

// 実部と虚部の計算
t_complex sqr(t_complex a)
{
	t_complex c;
	c.x = pow(a.x, 2.0) - pow(a.y, 2.0);
	c.y = 2 * a.x * a.y;
	return (c);
}

// 発散するか計算
double mod(t_complex a)
{
	return (sqrt(pow(a.x, 2.0) + pow(a.y, 2.0)));
}

t_complex map(double radius, int ix, int iy)
{
	t_complex c;
	int l;

	if (WIDTH < HEIGHT)
		l = WIDTH;
	else
		l = HEIGHT;
	c.x = 2 * radius * (ix - WIDTH / 2.0) / l;
	c.y = 2 * radius * (iy - HEIGHT / 2.0) / l;
	return (c);
}

//マンデルブロ
void mandelbrot(t_data *img,
	t_complex c,
	const double radius,
	const double cx_min,
	const double cx_max,
	const double cy_min,
	const double cy_max)
{
	//ウインドウ
	int	ix, iy;
	//x,y平面
	double cx, cy;
	//縦横計算
	double pixel_height;
	double pixel_width;

	int i;
	t_complex z0;
	t_complex z1;

	pixel_height = (cy_max - cy_min) / HEIGHT;
	pixel_width = (cx_max - cx_min) / WIDTH;
	for (iy = 0; iy < HEIGHT; iy++)
	{
		cy = cy_min + iy * pixel_height;
		if (fabs(cy) < pixel_height / 2)
			cy = 0.0;
		for (ix = 0; ix < WIDTH; ix++)
		{
			cx = cx_min + ix * pixel_width;
			//初期化
			init(&z0);
			init(&z1);
			//zを計算
			for (i = 1; i < I_MAX && (z1.x + z1.y) < pow(radius, 2.0); i++)
			{
				z0.y = 2 * z0.x * z0.y + cy;
				z0.x = z1.x - z1.y + cx;
				z1.x = pow(z0.x, 2.0);
				z1.y = pow(z0.y, 2.0);
			}
			if (i == I_MAX)
				my_mlx_pixel_put(img, ix, iy, 0x00FFFFFF);
		}
	}
}

//ジュリア
void julia(t_data *img, t_complex c, const double radius)
{
	int	ix;
	int	iy;
	int i;
	t_complex z0;
	t_complex z1;

	for (iy = 0; iy < HEIGHT; iy++)
	{
		for (ix = 0; ix < WIDTH; ix++)
		{
			z0 = map(radius, ix, iy);
			for (i = 1; i < I_MAX; i++)
			{
				z0 = sqr(z0);
				z1 = add(z0, c);
				if (mod(z1) > radius)
				{
					my_mlx_pixel_put(img, ix, iy, 0x00000000);
					break;
				}
				z0 = z1;
			}
			if (i == I_MAX)
				my_mlx_pixel_put(img, ix, iy, 0x00FFFFFF);
		}
	}
}

void	err_print(void)
{
	printf("\x1b[33m\n\
-< Give a number as an argument. >-\n\
\n\
 ex)\
 $ ./a.out 1\n\
\n\
 1 : Mandelbrot\n\
 2 : Julia\n\
-----------------------------------\n\n\
\x1b[39m");
}

int main(int argc, char **argv)
{
	t_vars vars;
	t_data img;
	t_complex c;

	vars.mlx = mlx_init();
	//ウインドウを作成
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");
	//ウインドウに表示するイメージを作成
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	//mlxに適宜値を設定させる(画像アドレス)
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	if (argc == 2 && argv[1][0] == '1')
	{
		//マンデルブロ
		c.x = 0.0;
		c.y = 0.0;
		mandelbrot(&img, c, 2, -2.5, 1.5, -2.0, 2.0);
	}
	else if (argc == 2 && argv[1][0] == '2')
	{
		//ジュリア
		c.x = -0.8;
		c.y = 0.156;
		julia(&img, c, 2);
	}
	else
	{
		err_print();
		return (0);
	}

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}
