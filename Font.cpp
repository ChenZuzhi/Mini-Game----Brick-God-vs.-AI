//
//  Font.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#include "Font.hpp"

Font* Font::font_instance = NULL;
string Font::font_path = "";

sf::Font* Font::GetFont()
{
    return &font;
}
void Font::LoadFont()
{
    //加载纹理
    if (!font.loadFromFile(font_path))
    {
        printf("Font file load failed.\n");
    }
}
