//
//  TetrisAI.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#ifndef TetrisAI_hpp
#define TetrisAI_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TetrisTexture.hpp"
#include "Font.hpp"
#include "PlayGround.hpp"
#include "SingleTetris.hpp"

enum CollisionType {NOCOLLISION, MARGINAL, BRICKS, BOTTOM};

class TetrisAI
{
public:
    //发生碰撞的时候返回true, 指有重叠部分
    CollisionType CollisionDetect(vector<vector<int>>&field, int global_x, int global_y, vector<vector<int>>& tetris_shape);
    void DetermineFinalState(vector<vector<int>>&field, int global_x, int global_y, SingleTetris& curr_tetris, int& final_x, int& final_rotate_index);
    TetrisAI(int grid_x_in, int grid_y_in);
private:
    vector<vector<int>> virtual_field;
    int grid_x;
    int grid_y;
    
    //对当前rotate和final_x的最终状态打分
    double ScoreTheState(vector<vector<int>>&field, vector<vector<int>>& tetris_shape, int final_x, int init_y);
    
    //获取各个x坐标处的高度, 空洞个数以及可以消除的行数
    void GetHeightAndEmptyHoles(vector<int>&height, int& empty_holes, int& dev_lines);
};

#endif /* TetrisAI_hpp */
