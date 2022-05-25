#include <iostream>

#include "board.hh"

#define IMPOSSIBLE_SITUATION -1000


bool horizontal_win(Board &board){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j<board_size; j++){
            if(board(i, j) == board.get_max_sym()){
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

int evaluate(Board &board){
    bool max_won, min_won;
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    // Checking if maximizer won
    
    // Horizontally
    if(horizontal_win(board)) return 5;
    return 0;
}