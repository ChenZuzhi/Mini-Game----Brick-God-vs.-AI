# 小游戏-"方块神大战人工智能"

这是本人设计和开发的小游戏"方块神大战人工智能"(别称："角色互换系列"-俄罗斯方块)的源代码。


## 游戏玩法简介
本游戏是玩家和电脑角色互换的俄罗斯方块。在游戏中，玩家不再操控方块的旋转和降落，玩家将扮演选择下一秒会下落的方块的类型(共有7种)，而电脑会操纵当前下落方块的移动和旋转。
与传统俄罗斯方块类似，当某一行出现不间断的方块时，这一行就会被消除。

玩家的目的是通过选择下一秒下落的方块类型，使得最后堆叠的无法被消除的方块积累到一定高度，从而获胜。
(共有7种方块类型，通过键盘数字1,2,3,4,5,6,7指定下一个下落的方块的形态，通过键盘R可以指定下落时的初始角度)

电脑会通过算法选择方块的旋转形态和下落位置，算法会让堆叠起来的方块的高度尽可能低。

**
聪明的玩家朋友，发挥你的聪明才智，打败这个邪恶的电脑吧。**

## 界面介绍
UI界面见下图：
绿色框所包含的是玩家可以使用的方块类型，按下上面的键盘数字即可指定下一个下落的方块为对应的类型。
红色框为下一个要落下的方块类型。
蓝色的方框所对应的线是玩家获胜的高度。
![image](game_ui_illustration/ui.jpg)

如果玩家获胜，将会出现下列节面
![image](game_ui_illustration/game_over_ui.jpg)
 

## 程序简介





## 为什么叫"方块神大战人工智能"？
