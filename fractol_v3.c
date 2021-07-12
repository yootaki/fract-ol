#include "./minilibx_mms_20200219/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 800
#define WIDTH 800
#define I_MAX 25
#define RADIUS 2

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int	type;
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

//Color encoder
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// 計算する関数たち
typedef struct s_complex
{
	float x;
	float y;
}t_complex;

//初期化
void init(t_complex *a)
{
	a->x = 0.0;
	a->y = 0.0;
}

// 足し算
t_complex add(t_complex a, t_complex b)
{
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
float mod(t_complex a)
{
	return (sqrt(pow(a.x, 2.0) + pow(a.y, 2.0)));
}

t_complex mappoint(int x, int y)
{
	t_complex c;
	int l;

	if (WIDTH < HEIGHT)
		l = WIDTH;
	else
		l = HEIGHT;
	c.x = 2 * RADIUS * (x - WIDTH / 2.0) / l;
	c.y = 2 * RADIUS * (y - HEIGHT / 2.0) / l;
	return (c);
}

//マンデルブロ
int mandelbrot(t_data *img, int ix, int iy)
{
	t_complex c;
	t_complex z0;
	t_complex z1;
	int i;

	c = mappoint(ix - 100, iy);
	//初期化
	init(&z0);
	init(&z1);
	for (i = 1; i < I_MAX && mod(z0) < pow(RADIUS, 2.0); i++)
	{
		z0.y = 2 * z0.x * z0.y + c.y;
		z0.x = z1.x - z1.y + c.x;
		z1.x = pow(z0.x, 2.0);
		z1.y = pow(z0.y, 2.0);
	}
	if (i == I_MAX)
		return (create_trgb(0, ix, iy, ix + iy));
	else
	{
		int r = 255 - (10 * i);
		int g = 255 - (10 * i);
		int b = 255 - (10 * i);
		return (create_trgb(0, r, g, b));
	}
}

//ジュリア
int julia(t_data *img, int ix, int iy, int x, int y)
{
	t_complex c;
	t_complex z0;
	t_complex z1;
	int i;

	c = mappoint(x, y); //mappointでやっていることを説明できるように！！
	z0 = mappoint(ix, iy);
	for (i = 1; i < I_MAX; i++)
	{
		z1 = add(sqr(z0), c);
		if (mod(z1) > RADIUS)
		{
			int r = 255 - (10 * i);
			int g = 255 - (10 * i);
			int b = 255 - (10 * i);
			return (create_trgb(0, r, g, b));
		}
		z0 = z1;
	}
	return (create_trgb(0, 0, 0, 0));
}

//マウスカーソルの動きによって再描画する
int	fractal(int x, int y, t_vars *vars)
{
	t_data img;
	int	ix;
	int	iy;
	int	color;

	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (iy = 0; iy < HEIGHT; iy++)
	{
		for (ix = 0; ix < WIDTH; ix++)
		{
			if (vars->type == 1)
				color = mandelbrot(&img, ix, iy);
			else if (vars->type == 2)
				color = julia(&img, ix, iy, x, y);
			//imgに描き込む
			my_mlx_pixel_put(&img, ix, iy, color);
		}
	}
	//ウインドウに描画する
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}

//ESCボタンでウインドウを閉じてプログラムを終了する
int	close(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
}

//マウスがクリックされた場所での実部と虚部の値を取得
int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	t_complex c;

	c = mappoint(x, y);
	printf("(%f,%f)\n", c.x, c.y);
}

//エラー時の表示
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


	vars.mlx = mlx_init();
	//ウインドウを作成
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");

	//引数によってフラクタルを選択
	if (argc == 2 && (argv[1][0] == '1' || argv[1][0] == '2'))
	{
		//コマンドライン引数をint型にして格納
		vars.type = argv[1][0] - '0';
		mlx_hook(vars.win, 6, 0L, fractal, &vars);
	}
	else
	{
		err_print();
		return (0);
	}

	//マウスクリックした場所の座標をターミナルに表示
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//ESCキーでウインドウを閉じてプログラム終了
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}
