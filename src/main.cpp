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
    bool player = !true;
    Board board(5, 4, 'x', 'o', '_');
    Move current_move = {0, 0, 0};

    board.display();

    while(!board.game_over()){
        std::cout << std::endl;
        if(whose_turn && player){
            std::cout << "W jakie miejsce wstawic symbol [wiersz, kolumna]: ";
            std::cin >> current_move.row;
            std::cin >> current_move.column;
        }
        else{
            current_move = choose_move(board, 5, whose_turn);
            std::cout << "Chosen move: [" << current_move.row << ", " << current_move.column << "] with value: " << current_move.value << std::endl; 
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