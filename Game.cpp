//
//  Game.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#include "Game.hpp"

void Game::Update(sf::Int32 elapsed_time)
{
    if(game_state == GAMEOVER)return;
    
    //先对当前下降的tetris进行操作
    DoTetrisHorizonMove(elapsed_time);
    DoTetrisRotate(elapsed_time);
    bool hit_to_bottom = DoTetrisFalling(elapsed_time);
    
    //判断是否到底
    if(hit_to_bottom)
    {
        //将现在正在进行的tetris处理好, 消除连续序列也会完成
        field.JoinTheField(curr_falling_tetris, falling_tetris_grid_x, falling_tetris_grid_y);
        
        //更新下一个tetris
        SetUpNextFalling();
        
        if(field.GetHeight()>grid_y-failed_line)
        {
            game_state = GAMEOVER;
            printf("游戏结束, 电脑输了");
        }
    }
}
void Game::ProcessPressNumber(sf::Keyboard::Key key_in)
{
    int next_tetris_type = 0;
    switch(key_in)
    {
        case sf::Keyboard::Num1:
            next_tetris_type = 0;
            break;
        case sf::Keyboard::Num2:
            next_tetris_type = 1;
            break;
        case sf::Keyboard::Num3:
            next_tetris_type = 2;
            break;
        case sf::Keyboard::Num4:
            next_tetris_type = 3;
            break;
        case sf::Keyboard::Num5:
            next_tetris_type = 4;
            break;
        case sf::Keyboard::Num6:
            next_tetris_type = 5;
            break;
        case sf::Keyboard::Num7:
            next_tetris_type = 6;
            break;
    }
    player_board.UpdatePlayerBoard(next_tetris_type);
}
void Game::ProcessPressR()
{
    player_board.UpdateNextRotate(1);
}
void Game::SetUpNextFalling()
{
    falling_tetris_grid_x = grid_x-4;
    falling_tetris_grid_y = 0;
    int falling_tetris_global_x = field_init_x + falling_tetris_grid_x * grid_size;
    int falling_tetris_global_y = field_init_y + falling_tetris_grid_y * grid_size;
    
    int next_tetris_type = player_board.GetNextTetrisType();
    int next_tetris_texture = player_board.GetNextTetrisTexture();
//    next_tetris_type = rand()%TetrisNumber;
    curr_falling_tetris.Init(next_tetris_type, next_tetris_texture, falling_tetris_global_x, falling_tetris_global_y, grid_size, 0, 1, true);
    
    player_board.LoadNextTetris();
    
    tetris_AI.DetermineFinalState(field.GetFieldState(), falling_tetris_grid_x, falling_tetris_grid_y, curr_falling_tetris, final_x, final_rotate);
    falling_update_rate = init_falling_update_rate;
}
void Game::DoTetrisHorizonMove(sf::Int32 elapsed_time)
{
    total_horizon_move_time += elapsed_time;
    int move_direction = 0;
    if(total_horizon_move_time > horizon_move_update_rate)
    {
        if(final_x != falling_tetris_grid_x)
        {
            //确定水平移动的方向
            if(final_x > falling_tetris_grid_x)
                move_direction = 1;
            else move_direction = -1;
            
            //确定是否要加速移动
            int speed_up_rate = 1;
            if(abs(final_x - falling_tetris_grid_x)==1)
            {
                speed_up_rate = 2;
            }
            
            //操作移动
            curr_falling_tetris.UpdateMove(0, move_direction);
            falling_tetris_grid_x += move_direction;
            falling_update_rate /= speed_up_rate;
            
            if(tetris_AI.CollisionDetect(field.GetFieldState(), falling_tetris_grid_x, falling_tetris_grid_y, curr_falling_tetris.GetTetrisState())!=NOCOLLISION)
            {
                //撤回之前的有效操作
                curr_falling_tetris.UpdateMove(0, -move_direction);
                falling_tetris_grid_x += (-move_direction);
                falling_update_rate *= speed_up_rate;
            }
        }
        total_horizon_move_time = 0;
    }
}
bool Game::DoTetrisFalling(sf::Int32 elapsed_time)
{
    bool hit_to_bottom = false;
    total_falling_time += elapsed_time;
    if(total_falling_time > falling_update_rate)
    {
        //操作向下移动
        curr_falling_tetris.UpdateFalling(1);
        falling_tetris_grid_y += 1;
        
        if(tetris_AI.CollisionDetect(field.GetFieldState(), falling_tetris_grid_x, falling_tetris_grid_y, curr_falling_tetris.GetTetrisState())!=NOCOLLISION)
        {
            hit_to_bottom = true;
            //撤回之前的有效操作
            
            curr_falling_tetris.UpdateFalling(-1);
            falling_tetris_grid_y += (-1);
        }
        
        total_falling_time = 0;
    }
    return hit_to_bottom;
}
void Game::DoTetrisRotate(sf::Int32 elapsed_time)
{
    total_rotate_time += elapsed_time;
    if(total_rotate_time > rotate_update_rate)
    {
        if(curr_falling_tetris.GetRotateIndex()!=final_rotate)
        {
            //操作旋转
            curr_falling_tetris.UpdateMove(1, 0);
            
            if(tetris_AI.CollisionDetect(field.GetFieldState(), falling_tetris_grid_x, falling_tetris_grid_y, curr_falling_tetris.GetTetrisState())!=NOCOLLISION)
            {
                //撤回之前的有效操作
                curr_falling_tetris.UpdateMove(-1, 0);
            }
        }
        total_rotate_time = 0;
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(player_board);
    target.draw(field);
    target.draw(curr_falling_tetris);
    if(game_state == GAMEOVER)
        target.draw(text_game_over);
}
