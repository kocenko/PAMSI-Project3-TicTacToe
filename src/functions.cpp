#include <iostream>
#include <algorithm>

#include "board.hh"

#define IMPOSSIBLE_SITUATION 0
#define INF_SUBSTITUTE 10000


struct Move{
    int row, column;
};

int evaluate(Board board, int depth){
    bool max_won = false, min_won = false;

    // Checking if maximizer won
    if(board.x_won(true)) max_won = true;

    // Checking if minimizer won
    if(board.x_won(false)) min_won = true;

    if(min_won && max_won) return IMPOSSIBLE_SITUATION;
    if(min_won) return -10 + depth;
    if(max_won) return +10 - depth;
    return 0;
}

int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    int eval, max_eval, min_eval, row_idx, col_idx;
    int board_size = board.get_size();
    
    if(depth == 0 || board.game_over()){
        board.display();
        std::cout << "Evaluated: " << evaluate(board, depth) << std::endl;
        return evaluate(board, depth);
    }

    if(maximizers_turn){
        max_eval = -INF_SUBSTITUTE;
        for (int i=0; i<board_size*board_size; i++){
            row_idx = i/board_size;
            col_idx = i%board_size;

            if(board.is_move_available(row_idx, col_idx)){
                board.make_move(row_idx, col_idx, true);
                eval = minimax_alpha_beta(board, depth-1, alpha, beta, false);
                max_eval = std::max(max_eval, eval);
                alpha = std::max(alpha, eval);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return max_eval;
    }
    else{
        max_eval = INF_SUBSTITUTE;
        for (int i=0; i<board_size*board_size; i++){
            row_idx = i/board_size;
            col_idx = i%board_size;

            if(board.is_move_available(row_idx, col_idx)){
                board.make_move(row_idx, col_idx, false);
                eval = minimax_alpha_beta(board, depth-1, alpha, beta, true);
                min_eval = std::min(min_eval, eval);
                beta = std::min(beta, eval);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return min_eval;
    }
}

Move choose_move(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    Move best_move;
    int best_move_value;
    int move_value;
    int board_size = board.get_size();
    
    best_move_value = (maximizers_turn) ? -INF_SUBSTITUTE : INF_SUBSTITUTE;

    for (int i=0; i<board_size; i++){
        for(int j=0; j<board_size; j++){
            if(board.is_move_available(i, j)){
                board.make_move(i, j, maximizers_turn);
                move_value = minimax_alpha_beta(board, depth, alpha, beta, maximizers_turn);
                board.clear_move(i, j);

                if(maximizers_turn){
                    if(best_move_value < move_value){
                        best_move_value = move_value;
                        best_move.row = i;
                        best_move.column = j;
                    }
                }
                else{
                    if(best_move_value > move_value){
                        best_move_value = move_value;
                        best_move.row = i;
                        best_move.column = j;
                    }
                }
            }
        }
    }
    return best_move;
}
