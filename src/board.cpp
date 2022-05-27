#include <iostream>

#include "board.hh"


Board::Board(int p_size, int p_win, char p_max, char p_min, char p_empty){
    if(p_win > p_size){
        throw std::range_error("Winning number cannot be bigger than size of the board.");
    }
    if(p_win < 1){
        throw std::range_error("Winning number cannot be less than one.");
    }
    if(p_size < 1){
        throw std::range_error("Size of a board cannot be less than one.");
    }

    size = p_size;
    win_num = p_win;
    maximizer_sym = p_max;
    minimizer_sym = p_min;
    empty_sym = p_empty;

    fields = new char*[p_size];

    for(int i=0; i<p_size; i++){
        fields[i] = new char[p_size];
    }

    for(int i=0; i<p_size; i++){
        for(int j=0; j<p_size; j++){
            fields[i][j] = empty_sym;
        }
    }

    available_moves = new bool[p_size*p_size];

    for(int i=0; i<p_size*p_size; i++){
        available_moves[i] = true;
    }
}

Board::Board(const Board& to_copy){
    size = to_copy.size;
    win_num = to_copy.win_num;
    maximizer_sym = to_copy.maximizer_sym;
    minimizer_sym = to_copy.minimizer_sym;
    empty_sym = to_copy.empty_sym;

    fields = new char*[to_copy.size];

    for(int i=0; i<to_copy.size; i++){
        fields[i] = new char[to_copy.size];
    }

    for(int i=0; i<to_copy.size; i++){
        for(int j=0; j<to_copy.size; j++){
            fields[i][j] = to_copy(i, j);
        }
    }

    available_moves = new bool[to_copy.size*to_copy.size];

    for(int i=0; i<to_copy.size*to_copy.size; i++){
        available_moves[i] = to_copy.available_moves[i];
    }
}

Board::~Board(){
    for(int i=0; i<size; i++){
        delete[] fields[i];
    }
    delete[] fields;
    delete[] available_moves;
}

void Board::display(){
    for(int i=-1; i<size; i++){
        if(i == -1){
            std::cout << "  ";
            for(int j=0; j<size; j++){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << i << " ";
            for(int j=0; j<size; j++){
                std::cout << fields[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void Board::make_move(int i, int j, bool maximizer){
    char sym;
    sym = (maximizer) ? maximizer_sym : minimizer_sym;

    if(is_move_available(i,j)){
        fields[i][j] = sym;
        available_moves[i*size+j] = false;
    }
}

void Board::clear_move(int i, int j){
    fields[i][j] = empty_sym;
    available_moves[i*size+j] = true;
}

bool Board::is_move_available(int i, int j){
    if(i > size-1 || j > size-1 || i < 0 || j < 0){
        std::cerr << "Cannot move to given position because it is out of range." << std::endl;
        std::cerr << "i: " << i << " j: " << j << " size-1: " << size << std::endl;
        return false;
    }
    if(is_full()){
        // std::cerr << "Cannot move to given position because the board is full." << std::endl;
        return false;
    }
    if(!available_moves[i*size+j]){
        // std::cerr << "Cannot move to given position because it is not free." << std::endl;
        return false;
    }
    return true; 
}

bool Board::is_full(){
    for(int i=0; i<size*size; i++){
        if(available_moves[i]) return false;
    }
    return true;
}

void Board::display_available_moves(){
    std::cout << std::endl << "Available moves: ";
    for(int i=0; i<size*size; i++){
        if(available_moves[i]) std::cout << i << " ";
    }
    std::cout << std::endl;
}

bool Board::vertical_win(bool maximizer){
    int temp_counter;
    char sym;

    sym = (maximizer) ? maximizer_sym : minimizer_sym;

    temp_counter = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            temp_counter = (fields[j][i] == sym) ? temp_counter+1 : 0;
            if(temp_counter == win_num) return true;
        }
        temp_counter = 0;
    }
    return false;
}

bool Board::horizontal_win(bool maximizer){
    int temp_counter;
    char sym;

    sym = (maximizer) ? maximizer_sym : minimizer_sym;

    temp_counter = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            temp_counter = (fields[i][j] == sym) ? temp_counter + 1 : 0;
            if(temp_counter == win_num) return true;
        }
        temp_counter = 0;
    }
    return false;
}

bool Board::top2bot_diagonal_win(bool maximizer){
    int temp_counter;
    char sym;

    sym = (maximizer) ? maximizer_sym : minimizer_sym;

    // Top to bottom
    /*
    [*][ ][ ]      [ ][ ][ ]      [ ][ ][ ]
    [ ][*][ ] ---> [*][ ][ ] ---> [ ][ ][ ]
    [ ][ ][*]      [ ][*][ ]      [*][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size-i; j++){
            temp_counter = (fields[i+j][j] == sym) ? temp_counter + 1 : 0;
            if(temp_counter == win_num) return true;
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
    for(int i=0; i<size; i++){
        for(int j=0; j<size-i; j++){
            temp_counter = (fields[j][i+j] == sym) ? temp_counter + 1 : 0;
            if(temp_counter == win_num) return true;
        }
        temp_counter = 0;
    }
    return false;
}

bool Board::bot2top_diagonal_win(bool maximizer){
    int temp_counter;
    char sym;
    
    sym = (maximizer) ? maximizer_sym : minimizer_sym;

    // Bottom to top
    /*
    [ ][ ][*]      [ ][*][ ]      [*][ ][ ]
    [ ][*][ ] ---> [*][ ][ ] ---> [ ][ ][ ]
    [*][ ][ ]      [ ][ ][ ]      [ ][ ][ ]
    */

    temp_counter = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size-i; j++){
            temp_counter = (fields[size-1-i-j][j] == sym) ? temp_counter + 1 : 0;
            if(temp_counter == win_num) return true;
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
    for(int i=0; i<size; i++){
        for(int j=size-1; j>=i; j--){
            temp_counter = (fields[j][size-1-j+i] == sym) ? temp_counter + 1 : 0;
            if(temp_counter == size) return true;
        }
        temp_counter = 0;
    }
    return false;
}

bool Board::diagonal_win(bool maximizer){
    if(top2bot_diagonal_win(maximizer)) return true;
    if(bot2top_diagonal_win(maximizer)) return true;
    return false;
}

bool Board::x_won(bool maximizer){
    if(diagonal_win(maximizer)) return true;
    if(vertical_win(maximizer)) return true;
    if(horizontal_win(maximizer)) return true;
    return false;
}

bool Board::game_over(){
    if(is_full() || x_won(true) || x_won(false)){
        return true;
    }
    return false;
}

void Board::set_fields(std::string tab){
    for(int i=0; i<size*size; i++){
        fields[i/size][i%size] = tab[i];
        if(tab[i] != empty_sym) available_moves[i] = false;
    }
}

int Board::get_size() const{
    return size;
}

int Board::get_win_num() const{
    return win_num;
}

char Board::get_max_sym() const{
    return maximizer_sym;
}

char Board::get_min_sym() const{
    return minimizer_sym;
}

char Board::get_empty_sym() const{
    return empty_sym;
}

const char & Board::operator() (int row, int column){
    return fields[row][column];
}

char Board::operator() (int row, int column) const{
    return fields[row][column];
}