module;

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

export module ui;


import board;

export class UI{
    public:
        UI(Board& board, sf::RenderWindow& window, sf::Font& font) : board(board), window(window), undo_texture("assets/undo.png"),
            undo_sprite(undo_texture), font(font),
            stats_text(font,"Click start .....\n \t to play", 21),
            //stats_box(sf::Vector2f(180, 100)),
            ai_texture("assets/ai.png"),
            ai_sprite(ai_texture),
            ai_check_box(sf::Vector2f(25, 25)),
            check_texture("assets/checked.png"),
            ai_check(check_texture),
            o_check(check_texture),
            x_check(check_texture),
            lines1(sf::PrimitiveType::LineStrip, 2),
            lines2(sf::PrimitiveType::LineStrip, 2),
            o_texture("assets/choose_o.png"),
            x_texture("assets/choose_x.png"),
            o_sprite(o_texture),
            x_sprite(x_texture),
            o_check_box(sf::Vector2f(25, 25)),
            x_check_box(sf::Vector2f(25, 25)),
            lines3(sf::PrimitiveType::LineStrip, 2),
            start_texture("assets/start-button.png"),
            start_sprite(start_texture),
            monitor_texture("assets/monitor.png"),
            monitor_sprite(monitor_texture){

            sf::Vector2u undo_textureSize = undo_texture.getSize();  // original size of the image
            float undo_scaleX = 55.0f / undo_textureSize.x;
            float undo_scaleY = 50.0f / undo_textureSize.y;

            undo_sprite.scale({undo_scaleX, undo_scaleY});
            undo_sprite.setPosition({25.0f, 670.0f});

            // stats_box.setFillColor(sf::Color(234,4,126));
            // stats_box.setPosition({610, 200});

            // Create text
            
            stats_text.setFillColor(sf::Color::White);

            sf::Vector2u monitor_textureSize = monitor_texture.getSize();  // original size of the image
            float monitor_scaleX = 200.0f / monitor_textureSize.x;
            float monitor_scaleY = 160.0f / monitor_textureSize.y;

            monitor_sprite.scale({monitor_scaleX, monitor_scaleY});
            monitor_sprite.setPosition({605, 200});
            sf::FloatRect mointorBounds = monitor_sprite.getLocalBounds();

            // Center text inside rectangle
            sf::FloatRect textBounds = stats_text.getLocalBounds();
            // stats_text.setOrigin({textBounds.position.x + textBounds.size.x / 1.3f,
            //                         textBounds.position.y + textBounds.size.y / 1.3f});
            stats_text.setPosition({625,225});


            //for ai-ui
            sf::Vector2u ai_textureSize = undo_texture.getSize();  // original size of the image
            float ai_scaleX = 100.0f / ai_textureSize.x;
            float ai_scaleY = 100.0f / ai_textureSize.y;

            ai_sprite.scale({ai_scaleX, ai_scaleY});
            ai_sprite.setPosition({130.0f, 650.0f});

            ai_check_box.setOutlineColor(sf::Color::Black);
            ai_check_box.setOutlineThickness(1.0f);
            ai_check_box.setPosition({270.0f, 680.0f});
            ai_check_box.setFillColor(sf::Color::White);
            
            lines1[0].position = sf::Vector2f(110, 600);
            lines1[1].position = sf::Vector2f(110, 800);

            lines2[0].position = sf::Vector2f(310, 650);
            lines2[1].position = sf::Vector2f(310, 750);
                        
            sf::Vector2u x_textureSize = x_texture.getSize();  // original size of the image
            float x_scaleX = 50.0f / x_textureSize.x;
            float x_scaleY = 45.0f / x_textureSize.y;

            x_sprite.scale({x_scaleX, x_scaleY});
            x_sprite.setPosition({330.0f, 670.0f});

            x_check_box.setOutlineColor(sf::Color::Black);
            x_check_box.setOutlineThickness(1.0f);
            x_check_box.setPosition({400.0f, 680.0f});
            x_check_box.setFillColor(sf::Color::White);

            sf::Vector2u o_textureSize = o_texture.getSize();  // original size of the image
            float o_scaleX = 50.0f / o_textureSize.x;
            float o_scaleY = 50.0f / o_textureSize.y;

            o_sprite.scale({o_scaleX, o_scaleY});
            o_sprite.setPosition({440.0f, 670.0f});

            o_check_box.setOutlineColor(sf::Color::Black);
            o_check_box.setOutlineThickness(1.0f);
            o_check_box.setPosition({510.0f, 680.0f});
            o_check_box.setFillColor(sf::Color::White);

            sf::Vector2u textureSize = check_texture.getSize();  // original size of the image
            float scaleX = 25.0f / textureSize.x;
            float scaleY = 25.0f / textureSize.y;

            
            ai_check.setScale({scaleX, scaleY});
            ai_check.setPosition({270.0f, 680.0f});

            x_check.setScale({scaleX, scaleY});
            x_check.setPosition({400.0f, 680.0f});

            o_check.setScale({scaleX, scaleY});
            o_check.setPosition({510.0f, 680.0f});

            lines3[0].position = sf::Vector2f(545, 650);
            lines3[1].position = sf::Vector2f(545, 750);

            sf::Vector2u start_textureSize = start_texture.getSize();  // original size of the image
            float start_scaleX = 75.0f / start_textureSize.x;
            float start_scaleY = 75.0f / start_textureSize.y;

            start_sprite.setScale({start_scaleX, start_scaleY});
            start_sprite.setPosition({600, 650});
            
        }


        void update_ui_state(){

            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

            if(isPressed && !wasPressed){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(position.x), static_cast<float>(position.y));

                if (undo_sprite.getGlobalBounds().contains(mousePosF) && is_undo_avialable){   
                    //std::cout<<"in undo\n";
                    board.undo_grid();
                }

                if(ai_check_box.getGlobalBounds().contains(mousePosF) && !freeze){
                    //std::cout<<"in ai check box\n";
                    isAIChecked = !isAIChecked;
                }

                if(o_check_box.getGlobalBounds().contains(mousePosF) && !freeze){
                    //std::cout<<"in o check box\n";
                    isOChecked = !isOChecked;
                    if(isXChecked) isXChecked = false;
                }
                
                if(x_check_box.getGlobalBounds().contains(mousePosF) && !freeze){
                    //std::cout<<"in x check box\n";
                    isXChecked = !isXChecked;
                    if(isOChecked) isOChecked = false;
                }

                if(start_sprite.getGlobalBounds().contains(mousePosF) && !freeze){
                    freeze = true;

                    if(!isAIChecked) {
                        isXChecked = false;
                        isOChecked = false;
                    }
                    set_stats(std::string("Game started!"));
                }
            }
             wasPressed = isPressed;
            
        }

        void lock_undo(){
            is_undo_avialable = false;
        }

        bool isStartEnabled(){
            return freeze;
        }

        void set_stats(const std::string& txt){
            stats_text.setString(txt);
        }

        void  render_check_box(){
            //sf::Texture texture("assets/checked.png");

            if(isAIChecked){
                window.draw(ai_check);
            }

            if(isXChecked){
                window.draw(x_check);
            }

            if(isOChecked){
                window.draw(o_check);
            }
        }

        std::vector<bool> get_options_state(){
            return {isAIChecked, isXChecked, isOChecked};
        }

        void render(){
            window.draw(undo_sprite);
            //window.draw(stats_box);
            window.draw(monitor_sprite);
            window.draw(stats_text);
            window.draw(ai_sprite);
            window.draw(ai_check_box);
            window.draw(lines1);
            window.draw(lines2);

            window.draw(o_sprite);
            window.draw(o_check_box);
            window.draw(x_sprite);
            window.draw(x_check_box);

            window.draw(lines3);
            window.draw(start_sprite);

            render_check_box();
        }

        void reset(){
            isAIChecked = false;
            isXChecked = false;
            freeze = false;
            isOChecked = false;
            is_undo_avialable = true;
        }
    
    private:
        Board& board;
        sf::RenderWindow& window;
        sf::Font& font;
        sf::Texture undo_texture;
        sf::Sprite undo_sprite;
        sf::Text stats_text;
        sf::RectangleShape stats_box;

        sf::Texture monitor_texture;
        sf::Sprite monitor_sprite;

        sf::Texture ai_texture;
        sf::Sprite ai_sprite;
        sf::RectangleShape ai_check_box;

        sf::Texture check_texture;
        sf::Texture o_texture;
        sf::Texture x_texture;
        sf::Sprite o_sprite;
        sf::Sprite x_sprite;
        sf::RectangleShape o_check_box;
        sf::RectangleShape x_check_box;

        sf::Sprite ai_check;
        sf::Sprite x_check;
        sf::Sprite o_check;

        sf::VertexArray lines1;
        sf::VertexArray lines2;
        sf::VertexArray lines3;

        sf::Texture start_texture;
        sf::Sprite start_sprite;

        bool isAIChecked = false;
        bool wasPressed = false;
        bool isOChecked = false;
        bool isXChecked = false;
        bool is_undo_avialable = true;
        bool freeze = false;
    };