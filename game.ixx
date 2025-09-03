module;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

export module game;

import board;
import board_entity;
import mouse;
import ui;
import gamestate;
import sound;

export class Game{
    public:
        Game() : window(sf::VideoMode({static_cast<unsigned int>((Board::WIDTH + 1) * Board::BLOCK_SIZE)
                    , static_cast<unsigned int>((Board::HEIGHT + 1) * Board::BLOCK_SIZE)}), "Tic Tac Toe", 
                    sf::Style::Titlebar | sf::Style::Close),
                    font("arial.ttf"),
                    board(),
                    entity(board),
                    gamestate(board),
                    mouse(window),
                    ui(board, window, font),
                    sound(){
        
            window.setFramerateLimit(60);

            auto image = sf::Image{};
            if (!image.loadFromFile("assets/icon.png"))
            {
                std::cout<<"Cant load the icon\n";
            }

            window.setIcon(image.getSize(), image.getPixelsPtr());

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

                if(isGameOver){
                    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() ) {
                        if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                            board.reset();
                            isGameOver = false;
                            ui.set_stats(std::string("Let's play again!"));
                        }
                    }
                }
            }
        }

        void update(){
        
            if(!isGameOver){
                
                sf::Vector2i position = mouse.get_position();
                if(board.update_board(position, current_turn)){

                    sound.play_click_sound();
                    if(current_turn ==  Symbol::X){
                        current_turn = Symbol::O;
                    }else{
                        current_turn = Symbol::X;
                    }
                }

                ui.update_ui_state(position);
            
            

                winner =  gamestate.checkWinner();
                if( winner != Symbol::None || winner == Symbol::Tie){
                    isGameOver = true;
                    current_turn = Symbol::X;
                    mouse.reset_position();

                    if(winner == Symbol::Tie) {
                        //std::cout<<"Its a tie\n";
                        sound.play_tie_sound();
                        ui.set_stats(std::string("Its a tie"));
                    }
                    else {
                        //std::cout<<"The winner is "<<((winner == Symbol::X)?"X":"O")<<"\n";
                        sound.play_victory_sound();
                        ((winner == Symbol::X)?ui.set_stats(std::string("The winner is X")):ui.set_stats(std::string("The winner is O")));
                    }
                }
            }
        }

        void render(){
            window.clear(sf::Color(1,245,255));
            entity.draw(window);
            ui.render();
            window.display();
        }
    
    private:
        sf::RenderWindow window;
        sf::Font font;
        Board board;
        BoardEntity entity;
        GameState gamestate;
        Mouse mouse;
        UI ui;
        Sound sound;
        Symbol current_turn = Symbol::X;
        Symbol winner = Symbol::None;
        bool isGameOver = false;
};