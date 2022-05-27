#include <iostream>
#include <algorithm>

#include "board.hh"

#define IMPOSSIBLE_SITUATION -1000
#define INF_SUBSTITUTE 10000


bool vertical_win(Board board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;
    char sym;

    sym = (maximizer) ? board.get_max_sym() : board.get_min_sym();

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j<board_size; j++){
            if(board(j, i) == sym){
                temp_counter++;   
            }
            else{
                temp_counter = 0;
            }

            if(temp_counter == winning_size){
                return true;
            }
        }
        temp_counter = 0;
    }
    return false;
}

bool horizontal_win(Board board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;
    char sym;

    sym = (maximizer) ? board.get_max_sym() : board.get_min_sym();

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j<board_size; j++){
            if(board(i, j) == sym){
                temp_counter++;   
            }
            else{
                temp_counter = 0;
            }

            if(temp_counter == winning_size){
                return true;
            }
        }
        temp_counter = 0;
    }
    return false;
}

bool top2bot_diagonal_win(Board board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;
    char sym;

    sym = (maximizer) ? board.get_max_sym() : board.get_min_sym();

    // Top to bottom
    /*
    [*][ ][ ]      [ ][ ][ ]      [ ][ ][ ]
    [ ][*][ ] ---> [*][ ][ ] ---> [ ][ ][ ]
    [ ][ ][*]      [ ][*][ ]      [*][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j<board_size-i; j++){
            if(board(i+j, j) == sym){
                temp_counter++;   
            }
            else{
                temp_counter = 0;
            }

            if(temp_counter == winning_size){
                return true;
            }
        }
        temp_counter = 0;
    }
    
    // Top to bottom
    /*
    [*][ ][ ]      [ ][*][ ]      [ ][ ][*]
    [ ][*][ ] ---> [ ][ ][*] ---> [ ][ ][ ]
    [ ][ ][*]      [ ][ ][ ]      [ ][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j<board_size-i; j++){
            if(board(j, i+j) == sym){
                temp_counter++;   
            }
            else{
                temp_counter = 0;
            }

            if(temp_counter == winning_size){
                return true;
            }
        }
        temp_counter = 0;
    }
    return false;
}

bool bot2top_diagonal_win(Board board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;
    char sym;
    
    sym = (maximizer) ? board.get_max_sym() : board.get_min_sym();

    // Bottom to top
    /*
    [ ][ ][*]      [ ][*][ ]      [*][ ][ ]
    [ ][*][ ] ---> [*][ ][ ] ---> [ ][ ][ ]
    [*][ ][ ]      [ ][ ][ ]      [ ][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j<board_size-i; j++){
            if(board(board_size-1-i-j, j) == sym){
                temp_counter++;   
            }
            else{
                temp_counter = 0;
            }

            if(temp_counter == winning_size){
                return true;
            }
        }
        temp_counter = 0;
    }
    
    // Top to bottom
    /*
    [ ][ ][*]      [ ][ ][ ]      [ ][ ][ ]
    [ ][*][ ] ---> [ ][ ][*] ---> [ ][ ][ ]
    [*][ ][ ]      [ ][*][ ]      [ ][ ][*]
    */

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=board_size-1; j>=i; j--){
            if(board(j, board_size-1-j+i) == sym){
                temp_counter++;   
            }
            else{
                temp_counter = 0;
            }

            if(temp_counter == winning_size){
                return true;
            }
        }
        temp_counter = 0;
    }
    return false;
}

bool diagonal_win(Board board, bool maximizer){
    if(top2bot_diagonal_win(board, maximizer)) return true;
    if(bot2top_diagonal_win(board, maximizer)) return true;
    return false;
}

bool x_won(Board board, bool maximizer){
    if(diagonal_win(board, maximizer)) return true;
    if(vertical_win(board, maximizer)) return true;
    if(horizontal_win(board, maximizer)) return true;
    return false;
}

int evaluate(Board board){
    bool max_won = false, min_won = false;
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    // Checking if maximizer won
    if(horizontal_win(board, true)) max_won = true;
    if(vertical_win(board, true)) max_won = true;
    if(diagonal_win(board, true)) max_won = true;

    // Checking if minimizer won
    if(horizontal_win(board, false)) min_won = true;
    if(vertical_win(board, false)) min_won = true;
    if(diagonal_win(board, false)) min_won = true;

    if(min_won && max_won) return IMPOSSIBLE_SITUATION;
    if(min_won) return -10;
    if(max_won) return +10;
    return 0;
}

int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    int eval, max_eval;
    int board_size = board.get_size();
    
    if(depth == 0 || board.is_full()) return evaluate(board);

    if(maximizers_turn){
        max_eval = -INF_SUBSTITUTE;
        for(int i=0; i<board_size; i++){
            for(int j=0; j<board_size; j++){
                if(board.is_move_available(i, j)){
                    board.make_move(i, j, true);
                    eval = minimax_alpha_beta(board, depth-1, alpha, beta, false);
                    max_eval = std::max(max_eval, eval);
                    alpha = std::max(alpha, eval);
                    if(beta <= alpha){
                        return max_eval;
                    }
                }
            }
        }
        return max_eval;
    }
    else{
        max_eval = INF_SUBSTITUTE;
        for(int i=0; i<board_size; i++){
            for(int j=0; j<board_size; j++){
                if(board.is_move_available(i, j)){
                    board.make_move(i, j, false);
                    eval = minimax_alpha_beta(board, depth-1, alpha, beta, true);
                    max_eval = std::min(max_eval, eval);
                    beta = std::max(beta, eval);
                    if(beta <= alpha){
                        return max_eval;
                    }
                }
            }
        }
        return max_eval;
    }
}

