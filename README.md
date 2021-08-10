# Fract-ol

![fractal](https://raw.github.com/wiki/yootaki/fract-ol/images/fractal.gif)

Fract-olは42Tokyoのプロジェクトです。\
このプロジェクトの目的はLinuxとMacで動作するフラクタルレンダラーを作成することです。
<br>
<br>

## 使用方法
ファイルをクローンします。
```
$ git clone <repository url>
```
<br>

クローンを作成したら、ディレクトリ内に移動し、次のコマンドを実行します。
```
$ make
```
もしMacOS上でプログラムを実行する場合は以下の行(mlx_destroy_display)をコメントアウトしてください
```:utils.c
void	free_mlx(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}
```
<br>

makeができたら次のコマンドでプログラムを実行します。
```
$ ./fractol <option number>
```
<br>

### マンデルブロフラクタル
```
$ ./fractol 1
```
![fractal](https://raw.github.com/wiki/yootaki/fract-ol/images/mandelbrot.png)
<br>
<br>

### ジュリアフラクタル
マウスカーソルによる形状変化
```
$ ./fractol 2
```
もしくは、パラメータを指定
```
$ ./fractol 3 -0.8 0.156
```
![fractal](https://raw.github.com/wiki/yootaki/fract-ol/images/julia.png)
<br>
<br>

### バーニングシップ
```
$ ./fractol 4
```
![fractal](https://raw.github.com/wiki/yootaki/fract-ol/images/burningship.png)
<br>
<br>

## キーコントロール

キーボードとマウスを使ってフラクタルをコントロールすることができます。
- A：カラー変更
- D：カラー変更
- W：計算回数増加
- S：計算回数減少
- 矢印キー(←)：左に移動
- 矢印キー(↑)：上に移動
- 矢印キー(→)：右に移動
- 矢印キー(↓)：下に移動
- 上スクロール：ズームイン
- 下スクロール：ズームアウト
