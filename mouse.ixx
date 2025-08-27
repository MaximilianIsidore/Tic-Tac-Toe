module;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

export module mouse;

export class Mouse{
    public:
        Mouse(sf::RenderWindow& window) : window(window){}

        void handle_click(){
            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

            if(isPressed && !wasPressed){
                position = sf::Mouse::getPosition(window);
                std::cout<<position.x <<" "<<position.y<<"\n";
            }

            wasPressed = isPressed;
        }

        void reset_position(){
            position={-1,-1};
        }
        
        sf::Vector2i get_position(){
            handle_click();
            return position;
        }
        
    private:
        sf::Vector2i position{-1,-1};
        sf::RenderWindow& window;
        bool wasPressed = false;
};