//
//  SingleTetris.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#include "SingleTetris.hpp"


int SingleTetris::GetTextureType()
{
    return texture_type;
}

SingleTetris::SingleTetris(int tetris_type_in, int texture_type_in, int global_x_in, int global_y_in, int grid_size_in, int rotate_index_in, int speed_in, bool active_in)
{
    Init(tetris_type_in, texture_type_in, global_x_in, global_y_in, grid_size_in, rotate_index_in, speed_in, active_in);
}
void SingleTetris::Init(int tetris_type_in, int texture_type_in, int global_x_in, int global_y_in, int grid_size_in, int rotate_index_in, int speed_in, bool active_in){
    global_x = global_x_in;
    global_y = global_y_in;
    grid_size = grid_size_in;
    tetris_type = tetris_type_in;
    texture_type = texture_type_in;
    rotate_index = rotate_index_in;
    vector<int> null_vector(4,0);
    while(!curr_state.empty())curr_state.pop_back();
    for(int i=0;i<4;i++)
        curr_state.push_back(null_vector);

    tetris_vertices.resize(16);
    tetris_vertices.setPrimitiveType(sf::Quads);
    
    TetrisTexture* texture_instance = TetrisTexture::GetInstance();
    tetris_texture = texture_instance->GetTexture();
    texture_size = texture_instance->GetTextureGridSize();
    texture_type_number = texture_instance->GetTextureTypeNum();
    
    speed = speed_in;
    active = active_in;
    LoadShape();
}

void SingleTetris::UpdateMove(int rotate_direc, int horizon_move)
{
    if(!active)return;
    rotate_index = (rotate_index + rotate_direc + 4) % 4;
    global_x += (horizon_move * grid_size);
    LoadShape();
}

void SingleTetris::UpdateFalling(int falling_rate)
{
    if(!active)return;
    global_y += (grid_size * falling_rate);
    LoadShape();
}

void SingleTetris::UpdateShape(int tetris_type_in, int texture_type_in, int global_x_in, int global_y_in)
{
    global_x = global_x_in;
    global_y = global_y_in;
    tetris_type = tetris_type_in;
    texture_type = texture_type_in;
    LoadShape();
}

vector<vector<int>>& SingleTetris::GetTetrisState(int&get_x, int&get_y)
{
    get_x = global_x;
    get_y = global_y;
    return curr_state;
}
vector<vector<int>>& SingleTetris::GetTetrisState()
{
    return curr_state;
}

int SingleTetris::GetRotateIndex()
{
    return rotate_index;
}

void SingleTetris::LoadShape()
{
    int x=0, y=0;
    for(int i=0;i<4;i++)
        for(int k=0;k<4;k++)
            curr_state[i][k] = 0;
    for(int i=0;i<4;i++)
    {
        x=TetrisShape[tetris_type][rotate_index][2*i];
        y=TetrisShape[tetris_type][rotate_index][2*i+1];
        curr_state[y][x] = 1;
        for(int k=0;k<4;k++)
        {
            tetris_vertices[i*4+k].color = sf::Color::White;
            tetris_vertices[i*4+k].position = sf::Vector2f(global_x + (x+(k/2))*grid_size, global_y + (y+((k+1)/2)%2)*grid_size);
            tetris_vertices[i*4+k].texCoords = sf::Vector2f((texture_type + k/2)*texture_size,(((k+1)/2)%2)*texture_size);
        }
    }
}

void SingleTetris::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(tetris_vertices, tetris_texture);
}
