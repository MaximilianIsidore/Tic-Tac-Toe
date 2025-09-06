module;

#include <vector>
#include <algorithm>
#include <limits>


export module ai;

import board;

enum Player { NONE = 0, X, O };

struct Move { int row, col; };

export class AI{
    public:
        AI(Board& board, Symbol playAs) : board_(board) {

            // if(playAs == Symbol::X) AiMove = 'x';
            // else if(playAs == Symbol::O) AiMove = 'o';
        }

        void set_paly_as(Symbol playAs){
            if(playAs == Symbol::X){
                AiMove = Player::X;
                opponent = Player::O;
            } 
            else if(playAs == Symbol::O) {
                AiMove = Player::O;
                opponent = Player::X;
            }

            //if(playAs == Symbol::X) isMaxPlayer = true;
        }

        std::vector<int> findBestMove() {
            int bestVal = std::numeric_limits<int>::min();
            Move bestMove{-1, -1};

            auto grid = board_.get_grid();
            std::vector<std::vector<Player>> board(3, std::vector<Player>(3, Player::NONE));

            for (int i = 0; i < 3; ++i){
                for (int j = 0; j < 3; ++j){
                    
                    if(grid[i][j] == Symbol::X){
                        board[i][j] = Player::X;
                    }else if(grid[i][j] == Symbol::O){
                        board[i][j] = Player::O;
                    }
                }
            }


            for (int i = 0; i < 3; ++i){
                for (int j = 0; j < 3; ++j){
                    if (board[i][j] == Player::NONE) {
                        board[i][j] = AiMove;
                        
                        
                        //if(AiMove == Player::X)
                        int moveVal =   moveVal = minimax(board, 0, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                        //else moveVal = minimax(board, 0, isMaxPlayer, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
                        board[i][j] = Player::NONE;
                        if (moveVal > bestVal) {
                            bestMove = {i, j};
                            bestVal = moveVal;
                        }
                    }
                }
            }
            return {bestMove.row, bestMove.col};
        }

    private:

        int evaluate(const std::vector<std::vector<Player>>& board) {
            // Check rows & columns
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                    if (board[i][0] == AiMove) return +10;
                    if (board[i][0] == opponent) return -10;
                }
                if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                    if (board[0][i] == AiMove) return +10;
                    if (board[0][i] == opponent) return -10;
                }
            }
            // Check diagonals
            if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
                if (board[0][0] == AiMove) return +10;
                if (board[0][0] == opponent) return -10;
            }
            if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
                if (board[0][2] == AiMove) return +10;
                if (board[0][2] == opponent) return -10;
            }
            return 0;
        }

        bool isMovesLeft(const std::vector<std::vector<Player>>& board) {
            for (auto& row : board)
                for (auto cell : row)
                    if (cell == Player::NONE) return true;
            return false;
        }

        int minimax(std::vector<std::vector<Player>>& board, int depth, bool isMax, int alpha, int beta) {
            int score = evaluate(board);
            if (score == 10 || score == -10) return score;
            if (!isMovesLeft(board)) return 0;

            Player currentPlayer = isMax ? AiMove : (AiMove == Player::X ? Player::O : Player::X);

            if (isMax) {
                int best = std::numeric_limits<int>::min();
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        if (board[i][j] == Player::NONE) {
                            board[i][j] = currentPlayer;
                            best = std::max(best, minimax(board, depth + 1, false, alpha, beta));
                            board[i][j] = Player::NONE;
                            alpha = std::max(alpha, best);
                            if (beta <= alpha) return best;
                        }
                return best;
            } else {
                int best = std::numeric_limits<int>::max();
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        if (board[i][j] == Player::NONE) {
                            board[i][j] = currentPlayer;
                            best = std::min(best, minimax(board, depth + 1, true, alpha, beta));
                            board[i][j] = Player::NONE;
                            beta = std::min(beta, best);
                            if (beta <= alpha) return best;
                        }
                return best;
            }
        }





    private:
        Board& board_;
        Player AiMove;
        Player opponent;
        //char player = 'x', opponent = 'o';
        bool isMaxPlayer = false;

        //std::vector<std::vector<char>> boardGrid_;
};