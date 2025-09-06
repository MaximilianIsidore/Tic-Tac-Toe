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
import ai;

export class Game{
    public:
        Game() : window(sf::VideoMode({static_cast<unsigned int>((Board::WIDTH + 1) * Board::BLOCK_SIZE)
                    , static_cast<unsigned int>((Board::HEIGHT + 1) * Board::BLOCK_SIZE)}), "Tic Tac Toe", 
                    sf::Style::Titlebar | sf::Style::Close),
                    font("arial.ttf"),
                    board(),
                    ai(board, Symbol::None),
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
                            ui.reset();
                            //isGameOver = false;

                            start_game = true;
                            aiHasMoved = false;
                            current_turn = Symbol::X;
                            aiPlayer = Symbol::None;
                            ui.set_stats(std::string("Let's play again! \n click start"));
                        }
                    }
                }
            }
        }

        void update(){
            //float delta_time = clock.restart().asSeconds();
           
            if(!isGameOver && current_turn != Symbol::None){
                
                 ui.update_ui_state();
                sf::Vector2i position = mouse.get_position();
                std::vector<int> move = {-1, -1};

                bool isAIEnabledThisTurn = isAIEnabled && current_turn == aiPlayer;

                if(isAIEnabledThisTurn && !aiHasMoved){
                    move = ai.findBestMove();
                    sf::sleep(sf::milliseconds(300));
                    if(board.update_board_ai(current_turn, move)){
                        sound.play_click_sound();
                        current_turn = (current_turn == Symbol::X) ? Symbol::O : Symbol::X;
                    }
                    aiHasMoved = true;
                }
                
                else if(!isAIEnabledThisTurn && current_turn != aiPlayer){
                    if(board.update_board(position, current_turn)){

                        sound.play_click_sound();
                        if(current_turn != aiPlayer) aiHasMoved = false;

                        if(current_turn ==  Symbol::X){
                            current_turn = Symbol::O;
                        }else{
                            current_turn = Symbol::X;
                        }
                    
                    }
                }

                if(board.isUndoDone()) current_turn = board.get_current_player();
            

                winner =  gamestate.checkWinner();
                if( winner != Symbol::None || winner == Symbol::Tie){
                    isGameOver = true;
                    isAIEnabled = false;
                    start_game = false;
                    //aiHasMoved = false;
                    current_turn = Symbol::None;
                    std::cout<<"GameOver "<<((isGameOver)?"true\n": "false\n");
                    while(const std::optional event = window.pollEvent()) {}//empty remaining events

                    mouse.reset_position();
                    ui.lock_undo();

                    if(winner == Symbol::Tie) {
                        //std::cout<<"Its a tie\n";
                        sound.play_tie_sound();
                        sf::sleep(sf::milliseconds(300));
                        ui.set_stats(std::string("Its a tie"));
                    }
                    else {
                        //std::cout<<"The winner is "<<((winner == Symbol::X)?"X":"O")<<"\n";
                        sound.play_victory_sound();
                        sf::sleep(sf::milliseconds(100));
                        ((winner == Symbol::X)?ui.set_stats(std::string("The winner is X \n press R to reset")):ui.set_stats(std::string("The winner is O \n press R to reset")));
                    }
                    //sf::sleep(sf::milliseconds(500));
                }
            }else{

                ui.update_ui_state();
                if(start_game && ui.isStartEnabled()){
                    isGameOver = false;
                    sound.play_click_sound();
                    std::vector<bool> state= ui.get_options_state();

                    isAIEnabled = state[0];

                    if(isAIEnabled){
                        ui.lock_undo();
                        if(state[1]){
                            aiPlayer = Symbol::X;
                            ai.set_paly_as(Symbol::X);
                        }else{
                            aiPlayer = Symbol::O;
                            ai.set_paly_as(Symbol::O);
                        }
                    }
                }
                
            }
        }

        void render(){
            window.clear(sf::Color(207,147,217));
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
        AI ai;

        Symbol current_turn = Symbol::X;
        Symbol winner = Symbol::None;
        bool isGameOver = true;
        bool start_game = true;

        bool isAIEnabled = false;
        Symbol aiPlayer = Symbol::None;
        bool aiHasMoved = false;

        sf::Clock clock;
        sf::Clock movement_clock;
        const float move_delay = 0.1f;
};