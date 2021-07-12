

//Mac用コマンド
// gcc fractol_v4.c -I ./minilibx_opengl_20191021/ -L ./minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit

//linux用コマンド
// gcc fractol_v4.c -I ./minilibx-linux/ -L ./minilibx-linux/ -lmlx -lXext -lX11 -L/usr/X11R6/lib

#include "./minilibx_mms_20200219/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 600
#define HEIGHT 400
#define I_MAX 50
#define RADIUS 2

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		type;
	float	x_param;
	float	y_param;
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
	float x;
	float y;
}t_complex;

//初期化
t_complex init(float a, float b)
{
	t_complex c;

	c.x = a;
	c.y = b;
	return (c);
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

//Color-encoder (先頭の数字(0.*)を変更すると周期を変えられる。)
int	create_trgb(t_vars *vars, t_complex c, int i)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = 0;
	if (i == I_MAX)
	{
		r = cos(0.6 * 100 * c.x + 0) * 127 + 128;
		g = cos(0.6 * 100 * c.y + 2 * M_PI/3) * 127 + 128;
		b = cos(0.6 * 100 * (c.x + c.y) + 4 * M_PI/3) * 127 + 128;
		if (vars->type == 1)
		{
			r = 0;
			g = 0;
			b = 0;
		}
	}
	else
	{
		r = sin(0.6 * i + 0) * 127 + 128;
		g = sin(0.6 * i + 2 * M_PI/3) * 127 + 128;
		b = sin(0.6 * i + 4 * M_PI/3) * 127 + 128;
	}
	return (t << 24 | r << 16 | g << 8 | b);
}

//マンデルブロ
int mandelbrot(t_vars *vars, int ix, int iy)
{
	t_complex c;
	t_complex z0;
	t_complex z1;
	int i;

	c = mappoint(ix - WIDTH / 8, iy);
	//初期化
	z0 = init(0.0, 0.0);
	z1 = init(0.0, 0.0);
	for (i = 1; i < I_MAX && mod(z0) < pow(RADIUS, 2.0); i++)
	{
		z0.y = 2 * z0.x * z0.y + c.y;
		z0.x = z1.x - z1.y + c.x;
		z1.x = pow(z0.x, 2.0);
		z1.y = pow(z0.y, 2.0);
	}
	return (create_trgb(vars, c, i));
}

//ジュリア(マウス座標で変化)
int julia(t_vars *vars, int ix, int iy)
{
	t_complex c;
	t_complex z0;
	t_complex z1;
	int i;

	if (vars->type == 2)
		c = mappoint(vars->x_param, vars->y_param);
	else
		c = init(vars->x_param, vars->y_param);
	z0 = mappoint(ix, iy);
	for (i = 1; i < I_MAX; i++)
	{
		z1 = add(sqr(z0), c);
		if (mod(z1) > RADIUS)
			break;
		z0 = z1;
	}
	return (create_trgb(vars, c, i));
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
				color = mandelbrot(vars, ix, iy);
			else if (vars->type == 2)
			{
				vars->x_param = x;
				vars->y_param = y;
				color = julia(vars, ix, iy);
			}
			else if (vars->type == 3)
				color = julia(vars, ix, iy);
			// else if (vars->type == 4)
			// 	color = ;
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
 ex) $ ./a.out 1\n\
     $ ./a.out 2\n\
     $ ./a.out 3 -0.8 0.156\n\
\n\
 1 : Mandelbrot\n\
 2 : julia with mouse coordinate\n\
 3 : julia with params\n\
-----------------------------------\n\n\
\x1b[39m");
	exit(1);
}

//実部と虚部の引数を計算
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
double myatof(char *s)
{
	double type  = 1;
	double etype = 1;
	double n = 0;
	double e = 0;
	while(*s == ' ') { s++; }

	if ( *s == '+' )
		s++;
	else if ( *s == '-' )
	{
		s++;
		type = -1;
	}

	// 整数部分の処理
	while(ft_isdigit(*s))
	{
		n = n * 10 + *s - '0';
		s++;
	}

	// 小数点部分の処理
	if ( *s == '.' )
	{
		double i = 1;
		while(ft_isdigit(*++s))
			n += (*s - '0') * (i*=0.1);
	}

	// 指数部分の処理
	if ( *s == 'e' || *s == 'E' ) {
		s++;
		if ( *s == '+' )
			s++;
		else if ( *s == '-' )
		{
			s++;
			etype = -1;
		}
		while(ft_isdigit(*s))
		{
			e = e * 10 + *s - '0';
			s++;
		}
		n *= pow(10,e*etype);
	}
	return n * type;
}

int main(int argc, char **argv)
{
	t_vars vars;
	t_data img;

	//イニシャライズ
	vars.mlx = mlx_init();
	//ウインドウを作成
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");

	//引数によってフラクタルを選択
	if (argc == 2 && (argv[1][0] == '1' || argv[1][0] == '2' || argv[1][0] == '4'))
	{
		//コマンドライン引数をint型にして格納
		vars.type = argv[1][0] - '0';
		mlx_hook(vars.win, 6, 0L, fractal, &vars);
	}
	else if (argc == 4 && argv[1][0] == '3')
	{
		vars.type = argv[1][0] - '0';
		vars.x_param = myatof(argv[2]);
		vars.y_param = myatof(argv[3]);
		mlx_hook(vars.win, 6, 0L, fractal, &vars);
	}
	else
		err_print();

	//マウスクリックした場所の座標をターミナルに表示
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//ESCキーでウインドウを閉じてプログラム終了
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}
