//
//  PlayerBoard.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#ifndef PlayerBoard_hpp
#define PlayerBoard_hpp

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

using namespace std;

class PlayerBoard: public sf::Drawable, public sf::Transformable{
public:
    PlayerBoard(int init_x_in, int init_y_in, int width_in, int height_in, int character_size_in, int grid_size_in, int playground_x_in, int playground_y_in, int playground_width_in, int playground_height_in, int failed_line_in, int total_width_in, int total_height_in);
    
    void UpdatePlayerBoard(int tetris_assign);
    void UpdateNextRotate(int rotate_direc);
    int GetNextTetrisType();
    int GetNextTetrisRotate();
    int GetNextTetrisTexture();
    void LoadNextTetris();

private:
    int next_tetris_type;
    int next_tetris_texture;
    int rotate_index;
    
    int init_x;
    int init_y;
    int width;
    int height;
    int total_width;
    int total_height;
    int playground_x;
    int playground_y;
    int playground_width;
    int playground_height;
    int failed_line;
    int y_failed_line;
    int y_next_falling_text;
    int y_next_falling;
    int y_rotate_instruction_text;
    int y_tetris_choice_text;
    vector<int> y_tetris_sample_text;
    vector<int> y_tetris_sample;
    
    int character_size;
    int grid_size;
    int sample_texture_size;
    int sample_texture_type_num;
    
    sf::Text text_failed_line;
    sf::Text text_next_falling;
    sf::Text text_rotate_instruction;
    sf::Text text_tetris_choice_instruction;
    vector<sf::Text> text_tetris_index;
    
    SingleTetris next_falling_tetris;
    vector<SingleTetris> sample_tetris;
    PlayGround playground;
    sf::VertexArray back_ground;
    
    sf::Texture* sample_texture;
    sf::Font* font;
    
    sf::VertexArray god_image;
    sf::VertexArray cui_image;
    sf::VertexArray rules_image;
    sf::VertexArray author_image;
    sf::Texture god_texture;
    sf::Texture cui_texture;
    sf::Texture rules_texture;
    sf::Texture author_texture;
    void LoadGodAndCui();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* PlayerBoard_hpp */
