# SimulateNetHack
Copyright 2018 Zcxsythenew
###
This project is created with Visual Studio 2017. The type of project is Linux console app written in C++.

## 项目主要内容
改编NetHack使规则大大简化，然后实现改编后的游戏。
该项目在Linux的终端上运行。
 
## 近期更新
优化了随机生成墙的算法，使墙的曲折更多，更有可玩性。

## **已知问题**
在 Ubuntu 18.10 下编译此游戏会导致 Segmentation Fault（在queue.push()引发），而在 Ubuntu 16.04 LTS 下无此问题。考虑到此问题，开发者已将最终生成的程序 game.out 一并提交，如果你编译时出错，可以使用此 game.out 代替，并请在评语留下系统信息以便开发者排查。

其它内容详见 report.pdf。
