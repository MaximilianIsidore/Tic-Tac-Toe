module;

#include <SFML/Graphics.hpp>

export module ui;


import board;

export class UI{
    public:
        UI(Board& board, sf::RenderWindow& window) : board(board), window(window), undo_texture("assets/undo.png"),
            undo_sprite(undo_texture){

            sf::Vector2u undo_textureSize = undo_texture.getSize();  // original size of the image
            float undo_scaleX = 25.0f / undo_textureSize.x;
            float undo_scaleY = 20.0f / undo_textureSize.y;

            undo_sprite.scale({undo_scaleX, undo_scaleY});
            undo_sprite.setPosition({20.0f, 650.0f});
        }

        void update_ui_state(sf::Vector2i position){
            sf::Vector2f mousePosF(static_cast<float>(position.x), static_cast<float>(position.y));

            if (undo_sprite.getGlobalBounds().contains(mousePosF))
            {
                board.undo_grid();
            }
        }

        void render(){
            window.draw(undo_sprite);
        }
    
    private:
        Board& board;
        sf::RenderWindow& window;
        sf::Texture undo_texture;
        sf::Sprite undo_sprite;
};