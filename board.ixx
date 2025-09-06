module;

#include <SFML/Graphics.hpp>
#include <array>
#include <span>
#include <vector>
#include <iostream>
#include <utility>



export module board;

import mouse;

export enum class Symbol { None, X, O , Tie };


export class Board{
    public:
        static constexpr int WIDTH = 3;
        static constexpr int HEIGHT = 3;
        static constexpr float BLOCK_SIZE = 200.0f;
        float o_scaleX , o_scaleY, x_scaleX, x_scaleY;

        Board() : o_texture("assets/o.png"), x_texture("assets/x.png"){\

            grid.fill({Symbol::None});
            last_set_grid = {-1, -1};

            sf::Vector2u x_textureSize = x_texture.getSize();  // original size of the image
            x_scaleX = BLOCK_SIZE / x_textureSize.x;
            x_scaleY = BLOCK_SIZE / x_textureSize.y;

            sf::Vector2u o_textureSize = o_texture.getSize();  // original size of the image
            o_scaleX = BLOCK_SIZE / o_textureSize.x;
            o_scaleY = BLOCK_SIZE / o_textureSize.y;
        }

        void reset(){
            grid.fill({Symbol::None});
            last_set_grid = {-1, -1};
        }

        std::span<const std::array<Symbol, WIDTH>> get_grid() const{
            return grid;
        }


        const sf::Texture& get_texture_o() const{
            return o_texture;
        }

        const sf::Texture& get_texture_x() const{
            return x_texture;
        }

        std::vector<float> get_scale_o(){
            return std::vector<float>({o_scaleX, o_scaleY});
        }

        std::vector<float> get_scale_x(){
            return std::vector<float>({x_scaleX, x_scaleY});
        }

        void undo_grid(){
            int x = last_set_grid[0];
            int y = last_set_grid[1];

            if(x>=0 && y>=0){
                current_palyer = grid[x][y];
                grid[x][y] = Symbol::None;
                isUndo = true;
            }
        }

        bool isUndoDone(){
            return isUndo;
        }

        Symbol get_current_player(){
            isUndo = false;
            return current_palyer;
        }

        bool update_board_ai(Symbol player_turn, std::vector<int> move){
            int y = move[0];
            int x = move[1];

            if(x>=0 && y>=0 && grid[y][x] == Symbol::None){
                grid[y][x] = player_turn; 
                return true;
            }

            return false;
        }
        bool update_board(sf::Vector2i position, Symbol player_turn) {

            for(int y=0; y < Board::HEIGHT; ++y){
                for(int x=0; x < Board::WIDTH; ++x){
                    
                    int left   = x * Board::BLOCK_SIZE;
                    int right  = (x + 1) * Board::BLOCK_SIZE;
                    int top    = y * Board::BLOCK_SIZE;
                    int bottom = (y + 1) * Board::BLOCK_SIZE;

                    if (position.x >= left && position.x < right &&
                        position.y >= top  && position.y < bottom) {
                            
                            if(!isUndo && grid[y][x] == Symbol::None){
                                std::cout << "reachable\n";
                                grid[y][x] = player_turn;
                                last_set_grid = {y, x};
                                return true;
                            }
                    }
                }
            }
            

            return false;
        }
    
    private:
        std::array<std::array<Symbol, WIDTH>, HEIGHT> grid;
        //std::array<std::array<sf::Sprite, WIDTH>, HEIGHT> sprite_arr;
        //std::vector<std::vector<sf::Sprite>> sprite_arr;//(HEIGHT, vector<sf::Sprite>(WIDTH, sf::Sprite()));
        const sf::Texture o_texture;
        const sf::Texture x_texture;
        const sf::Texture empty_texture;

        std::vector<int> last_set_grid;
        bool wasUpdated = false;
        bool isUndo = false;

        Symbol current_palyer = Symbol::X;
};

