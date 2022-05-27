#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "board.hh"
#include "functions.hh"
#include "move_struct.hh"

#define INF_SUBSTITUTE 10000


int main(){
    bool whose_turn = true;
    bool player = true;
    // std::string tab = {'o', '_', '_', '_','_','_', 'x', '_', '_','_','_','_','x','_','_','_','_','_','o','_','_','_','_','_','_'};
    // std::string tab = "xoxoox___";
    // std::string tab = "xo_______________________";
    Board board(3, 3, 'x', 'o', '_');
    Move current_move = {0, 0, 0};
    // board.set_fields(tab);
    board.display();
    // current_move = choose_move(board, 4, -INF_SUBSTITUTE, INF_SUBSTITUTE, whose_turn);
    // std::cout << "Best move value: " << current_move.value << std::endl;
    // std::cout << "Best move: " << current_move.row << " " << current_move.column << std::endl;
    // board.make_move(current_move.row, current_move.column, whose_turn);
    // board.display();
    
    
    while(!board.game_over()){
        std::cout << std::endl;
        // if(whose_turn && !player){
        //     std::cout << "W jakie miejsce wstawic symbol [wiersz, kolumna]: ";
        //     std::cin >> current_move.row;
        //     std::cin >> current_move.column;
        // }
        // else{
        //     current_move = choose_move(board, 5, -INF_SUBSTITUTE, INF_SUBSTITUTE, whose_turn);
        // }
        current_move = choose_move(board, 4, -INF_SUBSTITUTE, INF_SUBSTITUTE, whose_turn);
        std::cout << "Best move value: " << current_move.value << std::endl;
        std::cout << "Best move: " << current_move.row << " " << current_move.column << std::endl;
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