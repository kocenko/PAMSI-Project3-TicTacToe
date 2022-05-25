#include <iostream>

#include "board.hh"

#define IMPOSSIBLE_SITUATION -1000


bool vertical_win(Board &board, bool maximizer){
   int board_size = board.get_size();
   int winning_size = board.get_win_num();
   int temp_counter;
   
   char sym;
    if(maximizer){
        sym = board.get_max_sym();
    }
    else{
        sym = board.get_min_sym();
    }

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

bool horizontal_win(Board &board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    char sym;
    if(maximizer){
        sym = board.get_max_sym();
    }
    else{
        sym = board.get_min_sym();
    }

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

bool top2bot_diagonal_win(Board &board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    char sym;
    if(maximizer){
        sym = board.get_max_sym();
    }
    else{
        sym = board.get_min_sym();
    }

    // Top to bottom
    /*
    [*][ ][ ]      [ ][ ][ ]      [ ][ ][ ]
    [ ][*][ ] ---> [*][ ][ ] ---> [ ][ ][ ]
    [ ][ ][*]      [ ][*][ ]      [*][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=i; j+i<board_size; j++){
            if(board(j+i, j) == sym){
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
        for(int j=i; j+i<board_size; j++){
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

bool bot2top_diagonal_win(Board &board, bool maximizer){
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    char sym;
    if(maximizer){
        sym = board.get_max_sym();
    }
    else{
        sym = board.get_min_sym();
    }

    // Bottom to top
    /*
    [ ][ ][*]      [ ][*][ ]      [*][ ][ ]
    [ ][*][ ] ---> [*][ ][ ] ---> [ ][ ][ ]
    [*][ ][ ]      [ ][ ][ ]      [ ][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<board_size; i++){
        for(int j=0; j+i<board_size; j++){ // Wrong indexes
            if(board(board_size-1-j, j) == sym){
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
        for(int j=i; j+i<board_size; j++){
            if(board(board_size-1-j, i+j) == sym){
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

bool diagonal_win(Board &board, bool maximizer){
    if(top2bot_diagonal_win(board, maximizer)) return true;
    if(bot2top_diagonal_win(board, maximizer)) return true;
    return false;
}

int evaluate(Board &board){
    bool max_won, min_won;
    int board_size = board.get_size();
    int winning_size = board.get_win_num();
    int temp_counter;

    // Checking if maximizer won
    
    // Horizontally
    if(horizontal_win(board, true)) return 5;
    if(vertical_win(board, true)) return 7;
    if(diagonal_win(board, true)) return 100;
    return 0;
}