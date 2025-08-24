module;

#include <SFML/Graphics.hpp>
#include <iostream>

export module game;

import board;
import board_entity;
import mouse;

export class Game{
    public:
        Game() : window(sf::VideoMode({static_cast<unsigned int>((Board::WIDTH + 1) * Board::BLOCK_SIZE)
                    , static_cast<unsigned int>((Board::HEIGHT + 1) * Board::BLOCK_SIZE)}), "Tic Tac Toe", 
                    sf::Style::Titlebar | sf::Style::Close),
                    font("arial.ttf"),
                    entity(Board()),
                    mouse(Mouse()){
        
            window.setFramerateLimit(60);

        }

        void run() {
            while(window.isOpen()){
                handle_events();
                update();
                render();
            }
        }
    
    private:
        
        void handle_events(){

            while(const std::optional event = window.pollEvent()){
                if(event->is<sf::Event::Closed>()){
                    window.close();
                }
                
            }
            mouse.handle_click();
        }

        void update(){

        }

        void render(){
            window.clear(sf::Color::Black);
            entity.draw(window);
            window.display();
        }
    
    private:
        sf::RenderWindow window;
        sf::Font font;
        BoardEntity entity;
        Mouse mouse;
};