module;

#include <SFML/Graphics.hpp>
#include <array>
#include <span>

export module board;

export class Board{
    public:
        static constexpr int WIDTH = 3;
        static constexpr int HEIGHT = 3;
        static constexpr float BLOCK_SIZE = 200.0f;

        Board(){
            grid.fill({});
        }

        std::span<const std::array<int, WIDTH>> get_grid() const{
            return grid;
        }
    
    private:
        std::array<std::array<int, WIDTH>, HEIGHT> grid;
};

