#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "board.hh"
#include "functions.hh"

#define INF_SUBSTITUTE 10000


int main(){
    int row, column;
    bool whose_turn = true;
    bool player = true;
    // std::string tab = {'x', 'o', 'x', 'o', 'o', 'x', '_', '_', '_'};
    Board board(5, 3, 'x', 'o', '_');
    Move current_move;
    // board.set_fields(tab);
    board.display();
    while(!board.game_over()){
        std::cout << std::endl;
        if(whose_turn & player){
            std::cout << "W jakie miejsce wstawic symbol [wiersz, kolumna]: ";
            std::cin >> current_move.row;
            std::cin >> current_move.column;
        }
        else{
            current_move = choose_move(board, 3, -INF_SUBSTITUTE, INF_SUBSTITUTE, whose_turn);
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