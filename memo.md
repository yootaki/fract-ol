
# 質問
- juliaの計算回数は実部、虚部の値によって変化させるか？同じだと見えやすい図形と見えにくい図形が出てしまわないか？

- プログラム終了時に「Bye!!!」みたいなメッセージ出す
- プログラム開始時に「hello!!!」みたいなメッセージと「ウインドウ上でクリックすると実部と虚部の値がターミナルに表示されるよ。」って感じのメッセージ出す


# Todo
## Mandatory
- コマンドライン引数で表示するフラクタルを指定
- 無効なパラメータが渡された場合などのエラー処理
- ESCキーでウインドウを閉じる&プログラム終了
- マンデルブロを表示
- ジュリアを表示
- ジュリアを実部と虚部の値によって形状変化させる
- サイケデリックな色の変化を追加
- 矢印キーによる移動機能の実装
- マウスカーソル部を基準とした拡大縮小機能の実装
## Bonus
- もう一つ以上のフラクタルを実装
- マウス位置に従ったズーム機能
- 矢印キーでの移動
- 色の範囲を変化させる

# Studynote
- mandelbrot set
(https://rosettacode.org/wiki/Mandelbrot_set#C)
・c = 1 - 2i
・Z0 = 0
Z1 = 0^2 + 1 - 2i
Z2 = (1 - 2i)^2 + 1 - 2i
...
Z30 =...
Zを適当な回数繰り返して発散するか調べる

・発散：絶対値が2を超えたら発散
（例えば上記の例の場合）
Z1で絶対値が2を超えるため、1-2iはマンデルブロ集合に含まれない

・マンデルブロ集合は実部と虚部が-2から1の間しかない

## 参考文献：
- miniLibx
(https://scrapbox.io/42tokyo-42cursus/miniLibX%E3%81%A3%E3%81%A6%E4%BD%95)
- X11 events
(http://7ujm.net/X/event.html)
- カーソル中心ズーム
(https://www.notion.so/baa967b962e740fe9d82769ea0819aec)
- julia set
(https://en.wikipedia.org/wiki/Julia_set)
- Bresenham’s Line
(https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm)
- 虚数とは何か
(https://atarimae.biz/archives/500)
- Cのフラクタル
(https://www.geeksforgeeks.org/fractals-in-cc/)
- マルチフラクタル，Tsallis統計による医用画像認識
(https://www.jstage.jst.go.jp/article/pjsai/JSAI01/0/JSAI01_0_223/_pdf/-char/ja)

## 動画
- ヘロンの数学チャンネル
(https://youtu.be/7KHRYUOikPA)
- julia set in processing
(https://youtu.be/fAsaSkmbF5s)
- This equation will change how you see the world
(https://youtu.be/ovJcsL7vyrk)

## PDF
- Fractal coding
(https://www.researchgate.net/publication/323607730_Fractal_Coding)
- Fractal - Stanford University
(https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1178/lectures/8-Fractals/8-Fractals.pdf)

## Man page
- perror
https://linuxjm.osdn.jp/html/LDP_man-pages/man3/perror.3.html
- strerror
https://linuxjm.osdn.jp/html/LDP_man-pages/man3/strerror.3.html
- exit
https://linuxjm.osdn.jp/html/LDP_man-pages/man3/exit.3.html
- math.h
(https://nxmnpg.lemoda.net/ja/3/math)
