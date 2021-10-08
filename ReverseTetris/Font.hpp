//
//  Font.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#ifndef Font_hpp
#define Font_hpp

#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Font{
public:
    static void DestroyInstance(){
        if(font_instance!=NULL){
            delete font_instance;
            font_instance = NULL;
        }
    }
    static Font* GetInstance(string font_path_in="")
    {
        if(font_path=="")
            font_path = font_path_in;
        if (font_instance == NULL){
            font_instance = new Font();
            font_instance->LoadFont();
        }
        return font_instance;
    }
    sf::Font* GetFont();
private:
    void LoadFont();
    sf::Font font;
    static string font_path;
    static Font* font_instance;
};


#endif /* Font_hpp */
