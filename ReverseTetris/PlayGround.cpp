//
//  PlayGround.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#include "PlayGround.hpp"

void PlayGround::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(grids);
}
PlayGround::PlayGround(int init_x_in, int init_y_in, int width_in, int height_in, int grid_size_in, int failed_line_in)
{
    Init(init_x_in, init_y_in, width_in, height_in, grid_size_in, failed_line_in);
}
void PlayGround::Init(int init_x_in, int init_y_in, int width_in, int height_in, int grid_size_in, int failed_line_in)
{
    init_x = init_x_in;
    init_y = init_y_in;
    width = width_in;
    height = height_in;
    grid_size = grid_size_in;
    failed_line = failed_line_in;
    x_num = round(width/grid_size)+1;
    y_num = round(height/grid_size)+1;
    grids.resize(2*(x_num+y_num));
    grids.setPrimitiveType(sf::Lines);
    SetGrid();
}
void PlayGround::SetGrid()
{
    for(int x=0;x<x_num;x++)
    {
        grids[2*x].color = sf::Color::Black;
        grids[2*x+1].color = sf::Color::Black;
        grids[2*x].position = sf::Vector2f(init_x+x*grid_size, init_y);
        grids[2*x+1].position = sf::Vector2f(init_x+x*grid_size, init_y+height);
    }
    for(int y=0;y<y_num;y++)
    {
        if(y==failed_line)
        {
            grids[2*y+2*(x_num)].color = sf::Color::Red;
            grids[2*y+1+2*(x_num)].color = sf::Color::Red;
            grids[2*y+2*(x_num)].position = sf::Vector2f(init_x, init_y+y*grid_size);
            grids[2*y+1+2*(x_num)].position = sf::Vector2f(init_x+width+50, init_y+y*grid_size);
        }else
        {
            grids[2*y+2*(x_num)].color = sf::Color::Black;
            grids[2*y+1+2*(x_num)].color = sf::Color::Black;
            grids[2*y+2*(x_num)].position = sf::Vector2f(init_x, init_y+y*grid_size);
            grids[2*y+1+2*(x_num)].position = sf::Vector2f(init_x+width, init_y+y*grid_size);
        }
    }
}
