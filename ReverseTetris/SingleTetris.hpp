//
//  SingleTetris.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#ifndef SingleTetris_hpp
#define SingleTetris_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "TetrisTexture.hpp"

using namespace std;

const int TetrisNumber = 7;
const int TetrisShape[TetrisNumber][4][8]={
    {{0,0,0,1,0,2,0,3},{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},{0,0,1,0,2,0,3,0}},
    {{0,0,0,1,0,2,1,0},{0,0,0,1,1,1,2,1},{1,0,1,1,1,2,0,2},{0,0,1,0,2,0,2,1}},
    {{0,1,1,1,2,1,1,0},{0,1,1,1,1,0,1,2},{0,0,1,0,2,0,1,1},{0,0,0,1,1,1,0,2}},
    {{0,0,0,1,1,0,1,1},{0,0,0,1,1,0,1,1},{0,0,0,1,1,0,1,1},{0,0,0,1,1,0,1,1}},
    {{0,0,1,0,1,1,1,2},{0,0,0,1,1,0,2,0},{0,0,0,1,0,2,1,2},{0,1,1,1,2,0,2,1}},
    {{0,0,1,0,1,1,2,1},{1,0,1,1,0,1,0,2},{0,0,1,0,1,1,2,1},{1,0,1,1,0,1,0,2}},
    {{0,1,1,1,1,0,2,0},{0,0,0,1,1,1,1,2},{0,1,1,1,1,0,2,0},{0,0,0,1,1,1,1,2}}
};

class SingleTetris: public sf::Drawable, public sf::Transformable
{
public:
    SingleTetris(int tetris_type_in=0, int texture_type_in=0, int global_x_in=0, int global_y_in=0, int grid_size_in=30, int rotate_index_in=0, int speed_in=0, bool active_in=false);
    void Init(int tetris_type_in, int texture_type_in, int global_x_in, int global_y_in, int grid_size_in, int rotate_index_in, int speed_in, bool active_in);
    
    void UpdateMove(int rotate_direc=0, int horizon_move = 0);
    
    void UpdateShape(int tetris_type_in, int texture_type_in, int global_x_in, int global_y_in);
    
    vector<vector<int>>& GetTetrisState(int&get_x, int&get_y);
    vector<vector<int>>& GetTetrisState();
    int GetRotateIndex();
    void UpdateFalling(int falling_rate);
    int GetTextureType();
private:
    bool active;
    int global_x;
    int global_y;
    int grid_size;
    int tetris_type;
    int rotate_index;
    int texture_type;
    vector<vector<int>> curr_state;
    sf::VertexArray tetris_vertices;
    sf::Texture*tetris_texture;
    int speed;
    
    int texture_size;
    int texture_type_number;
    
    void LoadShape();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* SingleTetris_hpp */
