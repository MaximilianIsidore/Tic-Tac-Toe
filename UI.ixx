module;

#include <SFML/Graphics.hpp>
#include <string>

export module ui;


import board;

export class UI{
    public:
        UI(Board& board, sf::RenderWindow& window, sf::Font& font) : board(board), window(window), undo_texture("assets/undo.png"),
            undo_sprite(undo_texture), font(font),
            stats_text(font,"Let's play!", 21),
            stats_box(sf::Vector2f(180, 100)){

            sf::Vector2u undo_textureSize = undo_texture.getSize();  // original size of the image
            float undo_scaleX = 55.0f / undo_textureSize.x;
            float undo_scaleY = 50.0f / undo_textureSize.y;

            undo_sprite.scale({undo_scaleX, undo_scaleY});
            undo_sprite.setPosition({25.0f, 670.0f});

            stats_box.setFillColor(sf::Color(234,4,126));
            stats_box.setPosition({610, 200});

            // Create text
            
            stats_text.setFillColor(sf::Color::White);

            // Center text inside rectangle
            sf::FloatRect textBounds = stats_text.getLocalBounds();
            stats_text.setOrigin({textBounds.position.x + textBounds.size.x / 1.3f,
                                    textBounds.position.y + textBounds.size.y / 1.3f});
            stats_text.setPosition({stats_box.getPosition().x + stats_box.getSize().x / 2.0f,
                            stats_box.getPosition().y + stats_box.getSize().y / 2.0f});
        }

        void update_ui_state(sf::Vector2i position){
            sf::Vector2f mousePosF(static_cast<float>(position.x), static_cast<float>(position.y));

            if (undo_sprite.getGlobalBounds().contains(mousePosF))
            {
                board.undo_grid();
            }
        }

        void set_stats(const std::string& txt){
            stats_text.setString(txt);
        }

        void render(){
            window.draw(undo_sprite);
            window.draw(stats_box);
            window.draw(stats_text);
        }
    
    private:
        Board& board;
        sf::RenderWindow& window;
        sf::Font& font;
        sf::Texture undo_texture;
        sf::Sprite undo_sprite;
        sf::Text stats_text;
        sf::RectangleShape stats_box;
};