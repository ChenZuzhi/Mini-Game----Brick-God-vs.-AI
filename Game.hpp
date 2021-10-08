//
//  Game.hpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/6.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "TetrisTexture.hpp"
#include "Font.hpp"
#include "PlayGround.hpp"
#include "SingleTetris.hpp"
#include "PlayerBoard.hpp"
#include "TetrisAI.hpp"
#include "Field.hpp"

using namespace std;

enum GameState{PROCESSING, GAMEOVER};

class Game : public sf::Drawable, public sf::Transformable
{
public:
    Game(int field_board_position_x_in = 10, int field_board_position_y_in = 10, int field_board_size_width_in = 750, int field_board_size_height_in = 1800, int player_board_position_x_in = 800, int player_board_position_y_in = 10, int player_board_size_width_in = 420, int player_board_size_height_in = 710, int grid_size_in = 30, int character_size_in = 25, int failed_line_in = 10, int horizon_move_update_rate_in = 200, int falling_update_rate_in = 400, int rotate_update_rate_in = 300, int total_width_in = 1500, int total_height_in = 1800):player_board(player_board_position_x_in, player_board_position_y_in, player_board_size_width_in, player_board_size_height_in, character_size_in, grid_size_in, field_board_position_x_in, field_board_position_y_in, field_board_size_width_in, field_board_size_height_in,failed_line_in, total_width_in, total_height_in), field(field_board_size_width_in/grid_size_in, field_board_size_height_in/grid_size_in, field_board_position_x_in, field_board_position_y_in, grid_size_in), tetris_AI(field_board_size_width_in/grid_size_in, field_board_size_height_in/grid_size_in)
    {
        srand(time(NULL));
        horizon_move_update_rate = horizon_move_update_rate_in;
        falling_update_rate = falling_update_rate_in;
        rotate_update_rate = rotate_update_rate_in;
        init_falling_update_rate = falling_update_rate;

        grid_x =field_board_size_width_in/grid_size_in;
        grid_y = field_board_size_height_in/grid_size_in;
        field_init_x = field_board_position_x_in;
        field_init_y = field_board_position_y_in;
        grid_size = grid_size_in;
        failed_line = failed_line_in;
        total_width = total_width_in;
        total_height = total_height_in;
        character_size = character_size_in;
        
        total_horizon_move_time = 0;
        total_falling_time = 0;
        total_rotate_time = 0;
        
        game_state = PROCESSING;
        
        //加载纹理
        TetrisTexture* texture_instance = TetrisTexture::GetInstance();
        sample_texture = texture_instance->GetTexture();
        texture_type_number = texture_instance->GetTextureTypeNum();
        texture_size = texture_instance->GetTextureGridSize();
        //加载字体
        Font* tmp_font_instance = Font::GetInstance();
        font = tmp_font_instance->GetFont();
        text_game_over.setFont(*font);
        text_game_over.setString("Game over,\n you win!");
        text_game_over.setCharacterSize(6*character_size);
        text_game_over.setFillColor(sf::Color::Black);
        text_game_over.setPosition(total_width_in/4, total_height/2);

        SetUpNextFalling();
    }
    
    void Update(sf::Int32 elapsed_time);

    void ProcessPressNumber(sf::Keyboard::Key key_in);
    
    void ProcessPressR();
    
private:
    void SetUpNextFalling();
    
    void DoTetrisHorizonMove(sf::Int32 elapsed_time);
    
    bool DoTetrisFalling(sf::Int32 elapsed_time);

    void DoTetrisRotate(sf::Int32 elapsed_time);
    
    TetrisAI tetris_AI;
    PlayerBoard player_board;
    Field field;
    
    int falling_tetris_grid_x;
    int falling_tetris_grid_y;
    SingleTetris curr_falling_tetris;
    int final_rotate;
    int final_x;
    
    int grid_x;
    int grid_y;
    int field_init_x;
    int field_init_y;
    int grid_size;
    int failed_line;
    int total_width;
    int total_height;
    int character_size;
    
    //以mill-second为单位
    sf::Int32 total_horizon_move_time;
    sf::Int32 total_falling_time;
    sf::Int32 total_rotate_time;
    GameState game_state;
    int horizon_move_update_rate;
    int init_falling_update_rate;
    int falling_update_rate;
    int rotate_update_rate;
    
    sf::Texture* sample_texture;
    sf::Text text_game_over;
    int texture_type_number;
    int texture_size;
    sf::Font* font;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* Game_hpp */
