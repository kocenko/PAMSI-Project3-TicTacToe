#include <iostream>
#include <algorithm>

#include "board.hh"
#include "move_struct.hh"

#define INF_SUBSTITUTE 100000000


int evaluate(Board board, int depth){
    // Checking if maximizer won
    if(board.x_won(true)) return 100 + depth;

    // Checking if minimizer won
    if(board.x_won(false)) return (-100 - depth);

    return 0;
}

int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    int eval=0, max_eval=0, min_eval=0, row_idx=0, col_idx=0;
    int board_size = board.get_size();

    if(depth == 0 || board.game_over()){
        return evaluate(board, depth);
    }

    if(maximizers_turn){
        max_eval = -INF_SUBSTITUTE;
        for (int i=0; i<board_size*board_size; i++){
            row_idx = i/board_size;
            col_idx = i%board_size;

            if(board.is_move_available(row_idx, col_idx)){
                board.make_move(row_idx, col_idx, maximizers_turn);
                eval = minimax_alpha_beta(board, depth-1, alpha, beta, !maximizers_turn);
                board.clear_move(row_idx, col_idx);
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
        min_eval = INF_SUBSTITUTE;
        for (int i=0; i<board_size*board_size; i++){
            row_idx = i/board_size;
            col_idx = i%board_size;

            if(board.is_move_available(row_idx, col_idx)){
                board.make_move(row_idx, col_idx, maximizers_turn);
                eval = minimax_alpha_beta(board, depth-1, alpha, beta, !maximizers_turn);
                board.clear_move(row_idx, col_idx);
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

Move choose_move(Board board, int depth, bool maximizers_turn){
    Move best_move = {0, 0, 0};
    int best_move_value = 0;
    int move_value = 0;
    int board_size = board.get_size();
    
    best_move_value = (maximizers_turn) ? -INF_SUBSTITUTE : INF_SUBSTITUTE;

    for (int i=0; i<board_size; i++){
        for(int j=0; j<board_size; j++){
            if(board.is_move_available(i, j)){
                board.make_move(i, j, maximizers_turn);
                move_value = minimax_alpha_beta(board, depth, -INF_SUBSTITUTE, INF_SUBSTITUTE, !maximizers_turn);
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

void gameHandler(int board_size, int win_size, int depth, bool who_starts, bool human, bool info){
    bool whose_turn = who_starts;
    bool player = human;
    Board board(board_size, win_size, 'x', 'o', '_');
    Move current_move = {0, 0, 0};

    board.display();

    while(!board.game_over()){
        std::cout << std::endl;
        if(whose_turn && player){
            do{
                std::cout << "W jakie miejsce wstawic symbol [wiersz, kolumna]: ";
                std::cin >> current_move.row;
                std::cin >> current_move.column;
            }
            while(!board.is_move_available(current_move.row, current_move.column));
        }
        else{
            current_move = choose_move(board, depth, whose_turn);
            if(info){
                std::cout << "Chosen move: ["
                        << current_move.row << ", " << current_move.column 
                        << "] with value: " << current_move.value << std::endl;
            }
        }
        board.make_move(current_move.row, current_move.column, whose_turn);
        board.display();
        whose_turn = !whose_turn;
    }
    if(board.x_won(true)){
        std::cout << "Wygral gracz rozpoczynajacy" << std::endl;
    }
    else if(board.x_won(false)){
        std::cout << "Wygral gracz drugi" << std::endl;
    }
    else{
        std::cout << "Remis" << std::endl;
    }
}
