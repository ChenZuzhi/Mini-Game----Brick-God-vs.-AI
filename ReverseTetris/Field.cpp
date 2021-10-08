//
//  Field.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#include "Field.hpp"

Field::Field(int grid_x_in, int grid_y_in, int init_x_in, int init_y_in, int grid_size_in)
{
    Init(grid_x_in, grid_y_in, init_x_in, init_y_in, grid_size_in);
}
void Field::Init(int grid_x_in, int grid_y_in, int init_x_in, int init_y_in, int grid_size_in)
{
    init_x = init_x_in;
    init_y = init_y_in;
    grid_size = grid_size_in;
    grid_x = grid_x_in;
    grid_y = grid_y_in;
    vector<int> null_vector(grid_x, -1);
    for(int y=0;y<grid_y;y++)
        field_texture.push_back(null_vector);
    
    TetrisTexture* texture_instance = TetrisTexture::GetInstance();
    sample_texture = texture_instance->GetTexture();
    texture_type_number = texture_instance->GetTextureTypeNum();
    texture_size = texture_instance->GetTextureGridSize();
}
int Field::GetHeight()
{
    int height = 0;
    for(int x=0;x<grid_x;x++)
    {
        for(int y=grid_y-1;y>=0;y--)
        {
            if(field_texture[y][x]!=-1)
            {
                if((grid_y-1-y)>height)height = (grid_y-1-y);
            }
        }
    }
    return height;
}
vector<vector<int>>& Field::GetFieldState(){
    return field_texture;
}
void Field::JoinTheField(SingleTetris& tetris_in, int field_x, int field_y)
{
    int texture_type = tetris_in.GetTextureType();
    vector<vector<int>>&tetris_state=tetris_in.GetTetrisState();
    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            if(tetris_state[y][x]>0 && field_y+y<grid_y && field_x+x<grid_x)
                field_texture[field_y+y][field_x+x] = texture_type;
        }
    }
    BubbleOutTheSequence();
    LoadTheFiledByTexture();
}
void Field::BubbleOutTheSequence()
{
    //判断哪些行需要消除
    vector<bool> flag(grid_y, false);
    for(int y=0;y<grid_y;y++)
    {
        flag[y]=true;
        for(int x=0;x<grid_x;x++)
        {
            if(field_texture[y][x]==-1)
            {
                flag[y]=false;
                break;
            }
        }
    }
    //消除掉需要消除的行
    int copy_y=grid_y-1;
    for(int y=grid_y-1;y>=0;y--)
    {
        while(copy_y>=0&&flag[copy_y])copy_y--;
        if(copy_y<0)
        {
            for(int x=0;x<grid_x;x++)
            {
                field_texture[y][x] = -1;
            }
        }else if(copy_y!=y)
        {
            for(int x=0;x<grid_x;x++)
            {
                field_texture[y][x] = field_texture[copy_y][x];
            }
        }
        copy_y--;
    }
}
void Field::LoadTheFiledByTexture()
{
    field_draw.clear();
    int count = 0;
    for(int x=0;x<grid_x;x++)
        for(int y=0;y<grid_y;y++)
            if(field_texture[y][x]!=-1)count++;
    
    field_draw.resize(count * 4);
    field_draw.setPrimitiveType(sf::Quads);
    int init_index = 0;
    for(int x=0;x<grid_x;x++)
    {
        for(int y=0;y<grid_y;y++)
        {
            if(field_texture[y][x]==-1)continue;
            int pos_init_x = init_x + x*grid_size;
            int pos_init_y = init_y + y*grid_size;
            int texture_type = field_texture[y][x];
            for(int k=0;k<4;k++)
            {
                field_draw[4*init_index + k].color = sf::Color::White;
                field_draw[4*init_index + k].position = sf::Vector2f(pos_init_x+(k/2)*grid_size, pos_init_y+((k+1)/2)%2*grid_size);
                field_draw[4*init_index + k].texCoords = sf::Vector2f((texture_type + k/2)*texture_size,(((k+1)/2)%2)*texture_size);
            }
            init_index++;
        }
    }
}
void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(field_draw, sample_texture);
}
