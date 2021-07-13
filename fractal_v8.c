#include "./minilibx_opengl_20191021/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 600
#define HEIGHT 400
#define I_MAX 25//50
#define RADIUS 2

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		type;
	float	x_param;
	float	y_param;
	int		x_mouse;
	int		y_mouse;
	float	side;
	float	vert;
	float	mag;//magnification
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

//縮尺を合わせる
t_complex mappoint(t_vars *vars, int x, int y)
{
	t_complex c;

	//-3 <= x < 3
	//-2 <= x < 2
	//(600,400)→(6,4)の平面に変換した
	//前半部分で縮小、後半部分で表示位置を調整
	// ジュリアは上下反転だから-1をかける
	c.x = (x / (WIDTH / (WIDTH / 100.0)) + vars->side) / vars->mag;
	if (vars->type == 2 || vars->type == 3)
		c.y = (y / (HEIGHT / (HEIGHT / 100.0)) + vars->vert) * (-1.0) / vars->mag;
	else
		c.y = (y / (HEIGHT / (HEIGHT / 100.0)) + vars->vert) / vars->mag;
	return (c);
}

//Color-encoder(先頭の数字(0.*)を変更すると周期を変えられる。)
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

	c = mappoint(vars, ix, iy);
	//初期化
	z0 = init(0.0, 0.0);
	z1 = init(0.0, 0.0);
	for (i = 1; i < I_MAX && (mod(z0)) < pow(RADIUS, 2.0); i++)
	{
		z0.y = 2 * z0.x * z0.y + c.y;
		z0.x = z1.x - z1.y + c.x;
		z1.x = pow(z0.x, 2.0);
		z1.y = pow(z0.y, 2.0);
	}
	return (create_trgb(vars, c, i));
}

//ジュリア(マウス座標で変化とパラメータ渡して固定表示)
int julia(t_vars *vars, int ix, int iy)
{
	t_complex c;
	t_complex z0;
	t_complex z1;
	int i;

	if (vars->type == 2)
		c = mappoint(vars, vars->x_mouse, vars->y_mouse);
	else
		c = init(vars->x_param, vars->y_param);
	z0 = mappoint(vars, ix, iy);
	for (i = 1; i < I_MAX; i++)
	{
		z1 = add(sqr(z0), c);
		if (mod(z1) > RADIUS)
			break;
		z0 = z1;
	}
	return (create_trgb(vars, c, i));
}

//バーニングシップ
int burningship(t_vars *vars, int ix, int iy)
{
	t_complex c;
	t_complex z0;
	t_complex z1;
	int i;

	c = mappoint(vars, ix, iy);
	z0 = init(0.0, 0.0);
	z1 = init(0.0, 0.0);
	for (i = 1; i < I_MAX && mod(z0) < pow(RADIUS, 2.0); i++)
	{
		z0.y = 2 * fabs(z0.x) * fabs(z0.y) + c.y;
		z0.x = z1.x - z1.y + c.x;
		z1.x = pow(z0.x, 2.0);
		z1.y = pow(z0.y, 2.0);
	}
	return (create_trgb(vars, c, i));
}

//ブレセンハムの線描画アルゴリズム&コッホ曲線
void	line(t_data *img, int x0, int y0, int x1, int y1)
{
	t_complex c;
	float	t;
	int		x;
	int		y;

	for (t = 0.0; t < 1.0; t += 0.01)
	{
		x = x0 + (x1 - x0) * t;
		y = y0 + (y1 - y0) * t;
		c = init((float)x, (float)y);
		my_mlx_pixel_put(img, x, y, create_trgb(NULL, c, t));
	}
}
void	koch_culc(t_data *img,t_complex p1,t_complex p2,int r)
{
	t_complex p3,p4,p5;
	double theta = M_PI/3;

	if(r>0){
		p3 = init((2*p1.x+p2.x)/3,(2*p1.y+p2.y)/3);
		p5 = init((2*p2.x+p1.x)/3,(2*p2.y+p1.y)/3);

		p4 = init(p3.x + (p5.x - p3.x)*cos(theta) + (p5.y - p3.y)*sin(theta),p3.y - (p5.x - p3.x)*sin(theta) + (p5.y - p3.y)*cos(theta));

		koch_culc(img,p1,p3,r-1);
		koch_culc(img,p3,p4,r-1);
		koch_culc(img,p4,p5,r-1);
		koch_culc(img,p5,p2,r-1);
	}
	else{
		line(img, p1.x, p1.y, p2.x, p2.y);
	}
}
void	kochCurve(t_vars *vars)
{
	t_data img;
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	t_complex p1,p2;

	//幅と高さから引いている数を変更で移動
	p1 = init(10, HEIGHT + vars->vert);//(point){10,h-10};
	p2 = init(WIDTH + vars->side, HEIGHT + vars->vert);//(point){w-10,h-10};
	koch_culc(&img,p1,p2,10);

	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}

//マウスカーソルが動くor矢印キーを押すと呼ばれる描画関数
void	fractal(t_vars *vars)
{
	t_data img;
	int	ix;
	int	iy;
	int	color;

	mlx_clear_window(vars->mlx, vars->win);
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (img.img == NULL)
		exit(1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (iy = 0; iy < HEIGHT; iy++)
	{
		for (ix = 0; ix < WIDTH; ix++)
		{
			if (vars->type == 1)
				color = mandelbrot(vars, ix, iy);
			else if (vars->type == 2 || vars->type == 3)
				color = julia(vars, ix, iy);
			else if (vars->type == 4)
				color = burningship(vars, ix, iy);
			//imgに描き込む
			my_mlx_pixel_put(&img, ix, iy, color);
		}
	}
	//ウインドウに描画する
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}

//マウス移動で座標を取得して再描画する
int	mouse_hook(int x, int y, t_vars *vars)
{
	vars->x_mouse = x;
	vars->y_mouse = y;
	fractal(vars);
	return (0);
}

//ESCボタンでウインドウを閉じてプログラムを終了する
//矢印で移動して再描画
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else
	{
		if (keycode == 126)
			vars->vert -= 0.5;
		else if (keycode == 125)
			vars->vert += 0.5;
		else if (keycode == 123)
			vars->side -= 0.5;
		else if (keycode == 124)
			vars->side += 0.5;
		fractal(vars);
	}
	return (0);
}

//マウスがクリックされた場所での実部と虚部の値を取得
int	mouse_click(int button, int x, int y, t_vars *vars)
{
	t_complex c;

	c = mappoint(vars, x, y);
	//上スクロールが5、下が4
	//倍率は1.5
	if (button == 5)
	{
		vars->mag += 1.0;
		vars->side -= (1.0 - vars->mag) * c.x / 600.0 - c.x;
		vars->vert -= (1.0 - vars->mag) * c.y / 400.0 - c.y;
	}
	else if (button == 4)
	{
		vars->mag -= 1.0;
		vars->side += (1.0 - vars->mag) * c.x / 600.0 - c.x;
		vars->vert += (1.0 - vars->mag) * c.y / 400.0 - c.y;
	}
	fractal(vars);
	printf("(%f,%f)\n", c.x, c.y);
	return (0);
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

	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		s++;
		type = -1;
	}

	// 整数部分の処理
	while (ft_isdigit(*s))
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

	//イニシャライズ
	vars.mlx = mlx_init();
	//ウインドウを作成
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Fractol");

	//初期化
	vars.side = -3.0;
	vars.vert = -2.0;
	vars.mag = 1.0;
	// 引数によってフラクタルを選択
	if (argc == 2 && (argv[1][0] == '1' || argv[1][0] == '2' || argv[1][0] == '4'))
	{
		vars.type = argv[1][0] - '0';
		mlx_hook(vars.win, 6, 1L<<6, mouse_hook, &vars);
	}
	else if (argc == 4 && argv[1][0] == '3')
	{
		vars.type = argv[1][0] - '0';
		vars.x_param = myatof(argv[2]);
		vars.y_param = myatof(argv[3]);
		mlx_hook(vars.win, 6, 1L<<6, mouse_hook, &vars);
	}
	// else if (argv[1][0] == '5')
	// {
	// 	kochCurve(&vars);
	// }
	else
		err_print();

	//マウスクリックした場所の座標をターミナルに表示
	mlx_mouse_hook(vars.win, mouse_click, &vars);
	//ESCキーでウインドウを閉じてプログラム終了&矢印移動
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_loop(vars.mlx);
}
