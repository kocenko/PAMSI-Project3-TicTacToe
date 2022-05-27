#include <iostream>
#include <chrono>
#include <thread>

#include "board.hh"
#include "functions.hh"

#define INF_SUBSTITUTE 10000

struct Move{
    int row, column;
};

Move choose_move(Board board, int depth, int alpha, int beta, bool maximizers_turn){
    Move best_move;
    int best_move_value = INF_SUBSTITUTE;
    int move_value;
    int board_size = board.get_size();
    
    if(maximizers_turn) best_move_value = best_move_value * (-1);

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

int main(){
    int row, column;
    Board board(5, 3, 'x', 'o', '_');
    Move opponent_move, player_move;
    board.display();

    while(!board.is_full() && !x_won(board, true) && !x_won(board, false)){
        // std::cout << "Podaj gdzie chcesz wykonac ruch [wiersz, kolumna]: ";
        // std::cin >> row;
        // std::cin >> column;
        // std::cout << std::endl;
        player_move = choose_move(board, 4, -INF_SUBSTITUTE, INF_SUBSTITUTE, true);
        board.make_move(player_move.row, player_move.column, true);
        opponent_move = choose_move(board, 4, -INF_SUBSTITUTE, INF_SUBSTITUTE, false);
        board.make_move(opponent_move.row, opponent_move.column, false);
        board.display();

        std::chrono::milliseconds timespan(1000); // or whatever
        std::this_thread::sleep_for(timespan);
    }
    if(x_won(board, true)){
        std::cout << "Wygral gracz rozpoczynajacy" << std::endl;
    }
    else if(x_won(board, false)){
        std::cout << "Wygral gracz drugi" << std::endl;
    }
    else{
        std::cout << "Remis" << std::endl;
    }
}