#include <iostream>

#include "board.hh"
#include "functions.hh"


int main(){
    int row, column;
    Board board(2, 2, 'x', 'o', '_');
    board.display();

    while(!board.is_full()){
        std::cout << "Podaj gdzie chcesz wykonac ruch [wiersz, kolumna]: ";
        std::cin >> row;
        std::cin >> column;
        std::cout << std::endl;
        board.make_move(row, column, true);
        board.display();
        std::cout << "Evaluated: " << evaluate(board) << std::endl;
    }
}