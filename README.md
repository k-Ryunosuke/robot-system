# robotsystem
4つのledをイルミネーションのように点滅させます。
# 動作環境
OS:Ubuntu 20.04.1LTS
# 準備するもの
* raspbery pi 3b+  
* 5mmmLED（色は任意)  
* ジャンパーワイヤ(オスメス) 6本  
* 抵抗(25Ω)　４本    
* ブレッドボード  
# 配線方法
 <img src= "https://github.com/k-Ryunosuke/robot-system/blob/main/195941.png" width="700" > 
 
 上図のように接続する。  
 上図Ledはすべて左がアノードである。つなぎ方は,  
 一番左からGPIO25, GND, GPIO12, GND, GPIO4, GPIO16, GNDとして繋いでいく。 
# インストール方法
```bash
$ git clone https://github.com/k-Ryunosuke/robot-system.git
$ make
$ sudo insmod myled.ko
$ sudo chmod 666 /dev/myled0
```
# 実行方法
以下5つの方法で点滅させることができます。  
  
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
