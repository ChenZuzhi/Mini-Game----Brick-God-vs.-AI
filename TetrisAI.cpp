//
//  TetrisAI.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#include "TetrisAI.hpp"


CollisionType TetrisAI::CollisionDetect(vector<vector<int>>&field, int global_x, int global_y, vector<vector<int>>& tetris_shape)
{
    CollisionType flag=NOCOLLISION;
    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            if(tetris_shape[y][x]==0)continue;
            if(global_x+x>=grid_x)
            {
                flag=MARGINAL;
                break;
            }
            if(global_y+y>=grid_y)
            {
                flag=BOTTOM;
                break;
            }
            if(field[global_y+y][global_x+x]!=-1)
            {
                flag=BRICKS;
                break;
            }
        }
    }
    return flag;
}
void TetrisAI::DetermineFinalState(vector<vector<int>>&field, int global_x, int global_y, SingleTetris& curr_tetris, int& final_x, int& final_rotate_index)
{
    for(int y=0;y<grid_y;y++)
    {
        for(int x=0;x<grid_x;x++)
            virtual_field[y][x] = field[y][x];
    }
    
    double min_score = MAXFLOAT, tmp_score;
    final_x = 0;
    int garbage;
//    vector<double> null_vector(grid_x, MAXFLOAT);
//    vector<vector<double>> score_list(4, null_vector);
    for(int rotate_index=0;rotate_index<4;rotate_index++)
    {        vector<vector<int>>&tetris_shape = curr_tetris.GetTetrisState(garbage, garbage);
        for(int x=0;x<grid_x;x++)
        {
            tmp_score = ScoreTheState(field, tetris_shape, x, global_y);
//            score_list[rotate_index][x] = tmp_score;
            if(tmp_score < min_score - 1e-10)
            {
                final_x = x;
                final_rotate_index = curr_tetris.GetRotateIndex();
                min_score = tmp_score;
            }
        }
        curr_tetris.UpdateMove(1,0);
    }
}
TetrisAI::TetrisAI(int grid_x_in, int grid_y_in){
    grid_x = grid_x_in;
    grid_y = grid_y_in;
    vector<int> null_vector(grid_x, -1);
    for(int y=0;y<grid_y;y++)
        virtual_field.push_back(null_vector);
}

double TetrisAI::ScoreTheState(vector<vector<int>>&field, vector<vector<int>>& tetris_shape, int final_x, int init_y)
{
    //确认最终域的状态,存储在virtual_field中
    int y_located=init_y;
    for(int y=init_y;y<grid_y;y++)
    {
        CollisionType collision_t = CollisionDetect(field,final_x,y,tetris_shape);
        
        if(collision_t==MARGINAL)
        {
            return MAXFLOAT;
        }
        if(collision_t==BRICKS||collision_t==BOTTOM)
        {
            break;
        }
        y_located = y;
    }
    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            if(tetris_shape[y][x]>0)
            {
                virtual_field[y_located+y][final_x+x]=1;
            }
        }
    }
    
    //获取该最终域状态的关键参数
    vector<int> height(grid_x, 0);
    int empty_holes=0, dev_lines=0;
    double avg=0.0,second_moment=0.0;
    GetHeightAndEmptyHoles(height, empty_holes, dev_lines);
    for(int x=0;x<grid_x;x++)
    {
        avg+=height[x];
    }
    avg=avg/double(grid_x);
    for(int x=0;x<grid_x;x++)
    {
        second_moment += (height[x]-avg)*(height[x]-avg);
    }
    
    //打分并返回
    double score=0.0;
    score = 0.2*second_moment + 1.0*empty_holes - 3.0*dev_lines;
    
    //维护virtual field
    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            if(tetris_shape[y][x]>0)
            {
                virtual_field[y_located+y][final_x+x]=-1;
            }
        }
    }
    
    return score;
}

//获取各个x坐标处的高度, 空洞个数以及可以消除的行数
void TetrisAI::GetHeightAndEmptyHoles(vector<int>&height, int& empty_holes, int& dev_lines)
{
    empty_holes = 0;
    dev_lines = 0;
    for(int x=0;x<grid_x;x++)
    {
        height[x] = 0;
        for(int y=grid_y-1;y>=0;y--)
        {
            if(virtual_field[y][x]!=-1)
            {
                height[x] = grid_y -y;
            }
        }
    }
    for(int x=0;x<grid_x;x++)
    {
        for(int y=grid_y-1;y>=0;y--)
        {
            if((grid_y-y)>=height[x])break;
            if(virtual_field[y][x]==-1)
            {
                empty_holes++;
            }
        }
    }
    bool flag=true;
    for(int y=grid_y-1;y>=0;y--)
    {
        flag=true;
        for(int x=0;x<grid_x;x++)
        {
            if(virtual_field[y][x]==-1)
            {
                flag=false;
                break;
            }
        }
        if(flag)
        {
            dev_lines++;
        }
    }
}
