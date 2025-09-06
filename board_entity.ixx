module;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

export module board_entity;

import board;
import mouse;


export class BoardEntity{
    public:
        explicit BoardEntity(Board& board) : board_(board){}

        void draw(sf::RenderWindow& window) const{
            sf::RectangleShape block(sf::Vector2f(Board::BLOCK_SIZE, Board::BLOCK_SIZE));
            block.setOutlineColor(sf::Color::White);
            block.setOutlineThickness(1.0f);

            auto grid = board_.get_grid();

            for(int y=0; y < Board::HEIGHT; ++y){
                for(int x=0; x < Board::WIDTH; ++x){
                    block.setPosition({x*Board::BLOCK_SIZE, y*Board::BLOCK_SIZE});
                    block.setFillColor(sf::Color(44,155,243));
                    window.draw(block);

                    if(grid[y][x] == Symbol::X){
                        sf::Sprite sprite(board_.get_texture_x());
                        sprite.setPosition({x*Board::BLOCK_SIZE, y*Board::BLOCK_SIZE});
                        std::vector<float> scale= board_.get_scale_x();
                        sprite.scale({scale[0], scale[1]});
                        window.draw(sprite);
                    }else if(grid[y][x] == Symbol::O){
                        sf::Sprite sprite(board_.get_texture_o());
                        sprite.setPosition({x*Board::BLOCK_SIZE, y*Board::BLOCK_SIZE});
                        std::vector<float> scale = board_.get_scale_o();
                        sprite.scale({scale[0], scale[1]});
                        window.draw(sprite);
                    }
                }
            }
        }


    private:
        Board& board_;
        //const Mouse& mouse_
       
};