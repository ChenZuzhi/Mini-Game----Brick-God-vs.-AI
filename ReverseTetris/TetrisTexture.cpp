//
//  TetrisTexture.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#include "TetrisTexture.hpp"

TetrisTexture* TetrisTexture::tetris_texture_instance = NULL;
string TetrisTexture::texture_path = "";
int TetrisTexture::texture_grid_size = 18;
int TetrisTexture::texture_grid_num = 8;

sf::Texture* TetrisTexture::GetTexture()
{
    return &texture;
}
void TetrisTexture::LoadTexture()
{
    //加载纹理
    if (!texture.loadFromFile(texture_path))
    {
        printf("Texture file load failed.\n");
    }
}

int TetrisTexture::GetTextureGridSize()
{
    return texture_grid_size;
}
int TetrisTexture::GetTextureTypeNum()
{
    return texture_grid_num;
}
