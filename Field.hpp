//
//  Field.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TetrisTexture.hpp"
#include "Font.hpp"
#include "PlayGround.hpp"
#include "SingleTetris.hpp"

class Field: public sf::Drawable, public sf::Transformable
{
public:
    Field(int grid_x_in = 0, int grid_y_in = 0, int init_x_in = 10, int init_y_in = 10, int grid_size_in = 30);
    
    void Init(int grid_x_in = 0, int grid_y_in = 0, int init_x_in = 10, int init_y_in = 10, int grid_size_in = 30);

    int GetHeight();

    vector<vector<int>>& GetFieldState();

    void JoinTheField(SingleTetris& tetris_in, int field_x, int field_y);
private:
    //俄罗斯方块消除一行连续的序列
    void BubbleOutTheSequence();
    
    void LoadTheFiledByTexture();
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::VertexArray field_draw;
    vector<vector<int>> field_texture;
    
    int init_x;
    int init_y;
    int grid_size;
    int grid_x;
    int grid_y;
    
    sf::Texture* sample_texture;
    int texture_type_number;
    int texture_size;
};

#endif /* Field_hpp */
