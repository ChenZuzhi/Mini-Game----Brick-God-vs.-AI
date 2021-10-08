//
//  PlayerBoard.cpp
//  MyTetris1
//
//  Created by bytedance on 2021/10/5.
//

#include "PlayerBoard.hpp"

int PlayerBoard::GetNextTetrisType()
{
    return next_tetris_type;
}

int PlayerBoard::GetNextTetrisTexture()
{
    return next_tetris_texture;
}

int PlayerBoard::GetNextTetrisRotate()
{
    return rotate_index;
}

void PlayerBoard::UpdateNextRotate(int rotate_direc)
{
    rotate_index = (rotate_index + rotate_direc + 4)%4;
    LoadNextTetris();
}

void PlayerBoard::UpdatePlayerBoard(int tetris_assign){
    next_tetris_type = tetris_assign;
    next_tetris_texture = rand()%sample_texture_type_num;
    LoadNextTetris();
}


void PlayerBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(back_ground);
    target.draw(text_failed_line);
    target.draw(text_next_falling);
    target.draw(text_rotate_instruction);
    target.draw(text_tetris_choice_instruction);
    for(int i=0;i<TetrisNumber;i++)
    {
        target.draw(sample_tetris[i], sample_texture);
        target.draw(text_tetris_index[i]);
    }
    target.draw(next_falling_tetris, sample_texture);
    target.draw(playground);
    
    target.draw(god_image, &god_texture);
    target.draw(cui_image, &cui_texture);
    target.draw(rules_image, &rules_texture);
    target.draw(author_image, &author_texture);
}

PlayerBoard::PlayerBoard(int init_x_in, int init_y_in, int width_in, int height_in, int character_size_in, int grid_size_in, int playground_x_in, int playground_y_in, int playground_width_in, int playground_height_in, int failed_line_in, int total_width_in, int total_height_in)
{
    srand(time(NULL));
    //加载字体
    Font* tmp_font_instance = Font::GetInstance();
    font = tmp_font_instance->GetFont();
    
    //加载纹理
    TetrisTexture* tmp_texture_instance = TetrisTexture::GetInstance();
    sample_texture = tmp_texture_instance->GetTexture();
    sample_texture_size = tmp_texture_instance->GetTextureGridSize();
    sample_texture_type_num = tmp_texture_instance->GetTextureTypeNum();
    
    // 设置UI位置
    init_x = init_x_in;
    init_y = init_y_in;
    grid_size = grid_size_in;
    character_size = character_size_in;
    total_width = total_width_in;
    total_height = total_height_in;
    width = width_in;
    height = height_in;
    failed_line = failed_line_in;
    playground_x = playground_x_in;
    playground_y = playground_y_in;
    playground_width = playground_width_in;
    playground_height = playground_height_in;
    int margin = 5;
    y_next_falling_text = margin*2;
    y_next_falling = y_next_falling_text + character_size + margin;
    y_failed_line = init_y + failed_line * grid_size;
//    y_next_falling_text = y_failed_line + character_size + margin * 20;
//    y_next_falling = y_next_falling_text + character_size + margin;
//    y_rotate_instruction_text = y_next_falling + 4 * grid_size + margin*10;
    y_rotate_instruction_text = y_failed_line + character_size + margin*30;
    y_tetris_choice_text = y_rotate_instruction_text + character_size + margin;
    int y_next_text = y_tetris_choice_text + character_size + margin, tmp_y_sample;
    for(int i=0;i<TetrisNumber/3;i++)
    {
        tmp_y_sample = y_next_text + character_size + margin;
        for(int j=0;j<3;j++)
        {
            y_tetris_sample_text.push_back(y_next_text);
            y_tetris_sample.push_back(tmp_y_sample);
        }
        y_next_text = tmp_y_sample + 4 * grid_size + margin;
    }
    tmp_y_sample = y_next_text + character_size + margin;
    for(int i=(TetrisNumber/3)*3;i<TetrisNumber;i++)
    {
        y_tetris_sample_text.push_back(y_next_text);
        y_tetris_sample.push_back(tmp_y_sample);
    }
    
    //设置纯白背景
    back_ground.resize(4);
    back_ground.setPrimitiveType(sf::Quads);
    for(int k=0;k<4;k++)
    {
        back_ground[k].color = sf::Color::White;
        back_ground[k].position = sf::Vector2f((k/2)*total_width, (((k+1)/2)%2)*total_height);
    }
    
    //加载网格
    playground.Init(playground_x, playground_y, playground_width, playground_height, grid_size, failed_line);
    text_failed_line.setFont(*font);
    text_failed_line.setString("Exceed this line then the computer is failed.");
    text_failed_line.setCharacterSize(character_size);
    text_failed_line.setFillColor(sf::Color::Red);
    text_failed_line.setPosition(init_x, y_failed_line);
    
    //设置文字信息
    text_next_falling.setFont(*font);
    text_next_falling.setString("Next one:");
    text_next_falling.setCharacterSize(character_size);
    text_next_falling.setFillColor(sf::Color::Black);
    text_next_falling.setPosition(init_x, y_next_falling_text);
    
    text_rotate_instruction.setFont(*font);
    text_rotate_instruction.setString("Press R to rotate the next one.");
    text_rotate_instruction.setCharacterSize(character_size);
    text_rotate_instruction.setFillColor(sf::Color::Black);
    text_rotate_instruction.setPosition(init_x, y_rotate_instruction_text);
    
    text_tetris_choice_instruction.setFont(*font);
    text_tetris_choice_instruction.setString("Type the number to change the next one:");
    text_tetris_choice_instruction.setCharacterSize(character_size);
    text_tetris_choice_instruction.setFillColor(sf::Color::Black);
    text_tetris_choice_instruction.setPosition(init_x, y_tetris_choice_text);
    
    sf::Text tmp_text;
    tmp_text.setFont(*font);
    for(int i=0;i<sample_texture_type_num;i++)
    {
        tmp_text.setString(to_string(i+1));
        tmp_text.setCharacterSize(character_size);
        tmp_text.setFillColor(sf::Color::Black);
        tmp_text.setPosition(init_x + (i%3)*(width/3), y_tetris_sample_text[i]);
        text_tetris_index.push_back(tmp_text);
    }
    
    //设置初始的tetris
    next_tetris_type = 0;
    next_tetris_texture = sample_texture_type_num-1;
    rotate_index = 0;
    
    //处理样例方块的信息
    LoadNextTetris();
    SingleTetris tmp_sample;
    for(int i=0;i<TetrisNumber;i++)
    {
        tmp_sample.Init(i, i%sample_texture_type_num,
                        //rand()%sample_texture_type_num,
                        init_x + (i%3)*(width/3), y_tetris_sample[i], grid_size, 0, 0, false);
        sample_tetris.push_back(tmp_sample);
    }
    
    //处理小翠和方块神的图像
    LoadGodAndCui();
}

void PlayerBoard::LoadNextTetris()
{
//    next_tetris_type = rand()%TetrisNumber;
    next_tetris_texture = rand()%sample_texture_type_num;
    next_falling_tetris.Init(next_tetris_type, next_tetris_texture, init_x, y_next_falling, grid_size, rotate_index, 0, false);
}

void PlayerBoard::LoadGodAndCui()
{
    //加载纹理
    //高1050，宽716
//    if (!god_texture.loadFromFile("/Users/bytedance/Desktop/CV/Games/SFML_CppGames/MyTetris1/MyTetris1/images/fangkuaiGod.jpeg"))
//    {
//        printf("God texture file load failed.\n");
//    }
//    //260*260
//    if (!cui_texture.loadFromFile("/Users/bytedance/Desktop/CV/Games/SFML_CppGames/MyTetris1/MyTetris1/images/cui_on_cliff.jpeg"))
//    {
//        printf("Cui texture file load failed.\n");
//    }
//    //1228*560
//    if (!rules_texture.loadFromFile("/Users/bytedance/Desktop/CV/Games/SFML_CppGames/MyTetris1/MyTetris1/images/rules.png"))
//    {
//        printf("Cui texture file load failed.\n");
//    }
//    if (!author_texture.loadFromFile("/Users/bytedance/Desktop/CV/Games/SFML_CppGames/MyTetris1/MyTetris1/images/author.png"))
//    {
//        printf("Cui texture file load failed.\n");
//    }
    if (!god_texture.loadFromFile("./images/fangkuaiGod.jpeg"))
    {
        printf("God texture file load failed.\n");
    }
    //260*260
    if (!cui_texture.loadFromFile("./images/cui_on_cliff.jpeg"))
    {
        printf("Cui texture file load failed.\n");
    }
    //1228*560
    if (!rules_texture.loadFromFile("./images/rules.png"))
    {
        printf("Cui texture file load failed.\n");
    }
    if (!author_texture.loadFromFile("./images/author.png"))
    {
        printf("Cui texture file load failed.\n");
    }
    god_image.resize(4);
    god_image.setPrimitiveType(sf::Quads);
    cui_image.resize(4);
    cui_image.setPrimitiveType(sf::Quads);
    rules_image.resize(4);
    rules_image.setPrimitiveType(sf::Quads);
    author_image.resize(4);
    author_image.setPrimitiveType(sf::Quads);

    for(int k=0;k<4;k++)
    {
        god_image[k].color = sf::Color::White;
        god_image[k].position = sf::Vector2f((k/2)*324 + init_x + 4*30, (((k+1)/2)%2)*250 + init_y + 1*30);
        god_image[k].texCoords = sf::Vector2f((k/2)*2394, (((k+1)/2)%2)*1852);
        
        cui_image[k].color = sf::Color::White;
        cui_image[k].position = sf::Vector2f(10+(k/2)*260+300, (((k+1)/2)%2)*260+10);
        cui_image[k].texCoords = sf::Vector2f((k/2)*260, (((k+1)/2)%2)*260);
        
        rules_image[k].color = sf::Color::White;
        rules_image[k].position = sf::Vector2f(10+(k/2)*560, (((k+1)/2)%2)*1228+260+10);
        rules_image[k].texCoords = sf::Vector2f((k/2)*570, (((k+1)/2)%2)*1228);
        
        //216*102
        int times=1;
        author_image[k].color = sf::Color::White;
        author_image[k].position = sf::Vector2f(init_x+(k/2)*216*times, (((k+1)/2)%2)*102*times+1400);
        author_image[k].texCoords = sf::Vector2f((k/2)*216, (((k+1)/2)%2)*102);

    }
}
