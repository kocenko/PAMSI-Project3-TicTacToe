#include <iostream>
#include <algorithm>

#include "board.hh"
#include "move_struct.hh"

#define IMPOSSIBLE_SITUATION 0
#define INF_SUBSTITUTE 10000


int evaluate(Board board, int depth){
    bool max_won = false, min_won = false;

    // Checking if maximizer won
    if(board.x_won(true)) max_won = true;

    // Checking if minimizer won
    if(board.x_won(false)) min_won = true;

    if(min_won && max_won) return IMPOSSIBLE_SITUATION;
    if(min_won) return -100 - depth;
    if(max_won) return +100 + depth;
    return 0;
}

int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    int eval=0, max_eval=0, min_eval=0, row_idx=0, col_idx=0;
    int board_size = board.get_size();
    
    // std::cout << "====================" << std::endl;
    // board.display();
    // board.display_available_moves();
    // std::cout << "Evaluation: " << evaluate(board, depth);
    // std::cout << std::endl;
    // std::cout << "Termination condition: " << (depth == 0 || board.game_over()) << std::endl;

    if(depth == 0 || board.game_over()){
        // board.display();
        // std::cout << "Evaluated: " << evaluate(board, depth) << std::endl;
        return evaluate(board, depth);
    }

    // std::cout << "Is it maximizer's turn: " << maximizers_turn << std::endl;

    if(maximizers_turn){
        max_eval = -INF_SUBSTITUTE;
        for (int i=0; i<board_size*board_size; i++){
            row_idx = i/board_size;
            col_idx = i%board_size;

            if(board.is_move_available(row_idx, col_idx)){
                // std::cout << "Maximizer's available move: [" << row_idx << "; " << col_idx << "]" << std::endl;
                board.make_move(row_idx, col_idx, maximizers_turn);
                eval = minimax_alpha_beta(board, depth-1, alpha, beta, !maximizers_turn);
                max_eval = std::max(max_eval, eval);
                alpha = std::max(alpha, eval);
                // std::cout << "Alpha: " << alpha << std::endl;
                board.clear_move(row_idx, col_idx);
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
                // std::cout << "Minimizer's available move: [" << row_idx << "; " << col_idx << "]" << std::endl;
                board.make_move(row_idx, col_idx, maximizers_turn);
                eval = minimax_alpha_beta(board, depth-1, alpha, beta, !maximizers_turn);
                min_eval = std::min(min_eval, eval);
                beta = std::min(beta, eval);
                // std::cout << "Beta: " << beta << std::endl;
                board.clear_move(row_idx, col_idx);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return min_eval;
    }
}

Move choose_move(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    Move best_move = {0, 0, 0};
    int best_move_value = 0;
    int move_value = 0;
    int board_size = board.get_size();
    
    best_move_value = (maximizers_turn) ? -INF_SUBSTITUTE : INF_SUBSTITUTE;

    for (int i=0; i<board_size; i++){
        for(int j=0; j<board_size; j++){
            if(board.is_move_available(i, j)){
                board.make_move(i, j, maximizers_turn);
                move_value = minimax_alpha_beta(board, depth, alpha, beta, !maximizers_turn);
                board.clear_move(i, j);

                if(maximizers_turn){
                    if(best_move_value < move_value){
                        best_move_value = move_value;
                        best_move.row = i;
                        best_move.column = j;
                        best_move.value = move_value;
                    }
                }
                else{
                    if(best_move_value > move_value){
                        best_move_value = move_value;
                        best_move.row = i;
                        best_move.column = j;
                        best_move.value = move_value;
                    }
                }
            }
        }
    }
    return best_move;
}
