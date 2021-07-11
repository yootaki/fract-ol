
# 質問
- juliaの計算回数は実部、虚部の値によって変化させるか？同じだと見えやすい図形と見えにくい図形が出てしまわないか？
-


# Todo
- Manderbrotとjuliaを表示する
ウインドウ上の一点一点をfor文で見ていく(全探索みたいな感じ)
一点一点（複素数）がマンデルブロ集合に属すかを計算する。ここで指定回数Zの計算を回していく。
もし、発散したらfalse。発散しなければtrueを返すようにする。
trueが帰ってきたらウインドウに表示する
- 移動、拡大縮小などの実装
- カラー変化を実装

# Studynote
- X11
(http://7ujm.net/X/event.html)

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

- julia set
(https://en.wikipedia.org/wiki/Julia_set)


## 参考文献：
・miniLibx
(https://scrapbox.io/42tokyo-42cursus/miniLibX%E3%81%A3%E3%81%A6%E4%BD%95)
・ヘロンの数学チャンネル
(https://youtu.be/7KHRYUOikPA)
・julia set in processing
(https://youtu.be/fAsaSkmbF5s)
・虚数とは何か
(https://atarimae.biz/archives/500)
・Cのフラクタル
(https://www.geeksforgeeks.org/fractals-in-cc/)
・フラクタルファウンデーション
(https://fractalfoundation.org/resources/learn-to-code/)
・ユーチューブ(フラクタル)
(https://youtu.be/ovJcsL7vyrk)
・カオス論研究 :古代カオス神話から現代数理カオス理論まで
(https://rnavi.ndl.go.jp/mokuji_html/024418167.html)
・マルチフラクタル，Tsallis統計による医用画像認識
(https://www.jstage.jst.go.jp/article/pjsai/JSAI01/0/JSAI01_0_223/_pdf/-char/ja)


## PDF
・Fractal coding
(https://www.researchgate.net/publication/323607730_Fractal_Coding)
・Fractal - Stanford University
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
