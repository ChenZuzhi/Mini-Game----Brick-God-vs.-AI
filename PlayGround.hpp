//
//  PlayGround.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#ifndef PlayGround_hpp
#define PlayGround_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TetrisTexture.hpp"
#include "Font.hpp"

class PlayGround: public sf::Drawable, public sf::Transformable{
public:
    PlayGround(int init_x_in=0, int init_y_in=0, int width_in=0, int height_in=0, int grid_size_in=30, int failed_line_in=10);
    void Init(int init_x_in=0, int init_y_in=0, int width_in=0, int height_in=0, int grid_size_in=30, int failed_line_in=10);
    void SetGrid();
private:
    sf::VertexArray grids;
    int init_x;
    int init_y;
    int width;
    int height;
    int grid_size;
    int x_num;
    int y_num;
    int failed_line;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif /* PlayGround_hpp */
