module;

#include <SFML/Window.hpp>
#include<iostream>

export module mouse;

export class Mouse{
    public:
        void handle_click(){
            bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

            if(isPressed && !wasPressed){
                position = sf::Mouse::getPosition();
                std::cout<<position.x <<" "<<position.y<<"\n";
            }

            wasPressed = isPressed;
        }
        
    private:
        sf::Vector2i position;
        bool wasPressed = false;
};