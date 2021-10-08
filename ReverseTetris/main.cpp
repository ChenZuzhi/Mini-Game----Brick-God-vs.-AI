#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "Font.hpp"
#include "TetrisTexture.hpp"
#include "SingleTetris.hpp"
#include "PlayGround.hpp"
#include "PlayerBoard.hpp"
#include "Field.hpp"
#include "Game.hpp"

using namespace std;

const int total_width = 1350+560;
const int total_height = 1520;
const int field_board_position_x = 10+560;
const int field_board_position_y = 10;
const int field_board_size_width = 780;
const int field_board_size_height = 1500;
const int player_board_position_x = 830+560;
const int player_board_position_y = 10;
const int player_board_size_width = 420;
const int player_board_size_height = 710;
const int grid_size = 30;
const int character_size = 25;
const int failed_line = 10;
const int horizon_move_update_rate = 50;
const int falling_update_rate = 40;
const int rotate_update_rate = 50;
//const string texture_path = "/Users/bytedance/Desktop/CV/Games/SFML_CppGames/MyTetris1/MyTetris1/images/tiles.png";
const string texture_path = "./images/tiles.png";
//const string font_path = "/Users/bytedance/Desktop/CV/Games/SFML_CppGames/MyTetris1/MyTetris1/arial.ttf";
const string font_path = "arial.ttf";
    
int main()
{
    sf::RenderWindow window(sf::VideoMode(total_width, total_height), "Reverse Tetris");
    TetrisTexture* texture_instance = TetrisTexture::GetInstance(texture_path);
    Font* font_instance = Font::GetInstance(font_path);
    
    Game game(field_board_position_x, field_board_position_y, field_board_size_width, field_board_size_height, player_board_position_x, player_board_position_y, player_board_size_width, player_board_size_height, grid_size, character_size, failed_line, horizon_move_update_rate, falling_update_rate, rotate_update_rate, total_width, total_height);
    
    sf::Clock clock;
    clock.restart();
    usleep(16*1000);
    while(window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        
        sf::Int32 elapsed_time = min(elapsed.asMilliseconds(), 100);
        
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyPressed :
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Num1:
                        case sf::Keyboard::Num2:
                        case sf::Keyboard::Num3:
                        case sf::Keyboard::Num4:
                        case sf::Keyboard::Num5:
                        case sf::Keyboard::Num6:
                        case sf::Keyboard::Num7:
                            game.ProcessPressNumber(event.key.code);
                            break;
                        case sf::Keyboard::R:
                            game.ProcessPressR();
                            break;
                    }
                    break;
            }
        }
        game.Update(elapsed_time);
        
        //wait and sync
        usleep(16*1000);
        
        window.clear();
        window.draw(game);
        window.display();
    }
    
    texture_instance->DestroyInstance();
    font_instance->DestroyInstance();
    return 0;
}
