//
//  TetrisTexture.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#ifndef TetrisTexture_hpp
#define TetrisTexture_hpp

#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class TetrisTexture{
public:
    static void DestroyInstance(){
        if(tetris_texture_instance!=NULL){
            delete tetris_texture_instance;
            tetris_texture_instance = NULL;
        }
    }
    static TetrisTexture* GetInstance(string texture_path_in="")
    {
        if(texture_path=="")
            texture_path = texture_path_in;
        if (tetris_texture_instance == NULL){
            tetris_texture_instance = new TetrisTexture();
            tetris_texture_instance->LoadTexture();
        }
        return tetris_texture_instance;
    }
    int GetTextureGridSize();
    int GetTextureTypeNum();
    sf::Texture* GetTexture();
private:
    void LoadTexture();
    sf::Texture texture;
    static string texture_path;
    static TetrisTexture* tetris_texture_instance;
    static int texture_grid_size;
    static int texture_grid_num;
};


#endif /* TetrisTexture_hpp */
