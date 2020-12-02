# robotsystem
4つのledをイルミネーションのように点滅させます。
# 動作環境
OS:Ubuntu 20.04.1LTS
# 準備するもの
・raspbery pi 3b+  
・5mmmLED（色は任意)  
・ジャンパーワイヤ(オスメス) 6本  
・抵抗(25Ω)  
・ブレッドボード  
# 回路
 <img src= "https://github.com/k-Ryunosuke/robot-system/blob/main/195941.png" width="700" >
 上図のように接続する。   
 上図Ledはすべて左がアノードである。つなぎ方は、     
 一番左からGPIO25, GND, GPIO12, GND, GPIO4, GPIO16, GNDとして繋いでいく。
