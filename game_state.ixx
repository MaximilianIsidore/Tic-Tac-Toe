module;

export module gamestate;

import board;

export class GameState{
    public:
        GameState(Board& board) : board(board){

        }

        Symbol checkWinner() {

            auto grid = board.get_grid();
            // Check rows and columns
            for (int i = 0; i < 3; i++) {
                // Check row
                if (grid[i][0] != Symbol::None && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                    return grid[i][0];
                // Check column
                if (grid[0][i] != Symbol::None && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
                    return grid[0][i];
            }

            // Check diagonals
            if (grid[0][0] != Symbol::None && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
                return grid[0][0];
            if (grid[0][2] != Symbol::None && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
                return grid[0][2];

            
            for(int i = 0; i<3; i++){
                for(int j = 0; j<3; j++){
                    if(grid[i][j] == Symbol::None) return Symbol::None;
                }
            }

            return Symbol::Tie; // No winner yet
        }
    
    private:
        Board& board;
};