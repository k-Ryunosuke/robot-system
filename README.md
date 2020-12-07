# robotsystem
ロボットシステム学課題
# 内容
4つのLEDが左から1~4回の任意の回数光らせたり、イルミネーションのように点滅させます。
# 動作環境
OS:Ubuntu 20.04.1LTS
# 準備するもの
* Raspbery Pi 3B+  
* 5mmLED（色は任意)  
* ジャンパーワイヤ(オスメス) 6本  
* 抵抗(250Ω)　4本    
* ブレッドボード  
# 配線方法
 <img src= "https://github.com/k-Ryunosuke/robot-system/blob/main/195941.png" width="700" > 
 
 上図のように接続してください。  
 上図LEDはすべて左がアノードとなっています。つなぎ方は,  
 一番左からGPIO25, GND, GPIO12, GND, GPIO4, GPIO16, GNDとして繋いでください。
# 実行方法
```bash
$ git clone https://github.com/k-Ryunosuke/robot-system.git
$ make
$ sudo insmod myled.ko
$ sudo chmod 666 /dev/myled0
```

以下5つの光り方で点滅させることができます。  
  
    
左から一回づつ点滅
```bash
$ echo 1 > /dev/myled0
```
左から一回づつ点滅を2回繰り返す
```bash
$ echo 2 > /dev/myled0
```
左から一回づつ点滅を3回繰り返す
```bash
$ echo 3 > /dev/myled0
```
左から一回づつ点滅を4回繰り返す
```bash
$ echo 4 > /dev/myled0
```
イルミネーションのように点滅
```bash
$ echo 5 > /dev/myled0
```
# 実行動画
[![LED](http://img.youtube.com/vi/IImJt9w2ZRg/hqdefault.jpg)](https://youtu.be/IImJt9w2ZRg)
