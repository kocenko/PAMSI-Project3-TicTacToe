#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "board.hh"
#include "functions.hh"
#include "move_struct.hh"

#define INF_SUBSTITUTE 10000


int main(){
    int board_size;
    int win_num;
    int depth;
    bool who_starts = false;
    bool player = false;
    bool info = false;
    char buf;


    std::cout << "Witaj w grze: kolko i krzyzyk" << std::endl;
    std::cout << "Podaj rozmiar pola: ";
    std::cin >> board_size;

    while(board_size < 1 || board_size > 10){
        std::cout << "Podana zla wartosc rozmiaru pola. Podaj rozmiar pola: ";
        std::cin >> board_size;
    }
    
    std::cout << "Podaj ile figur wygrywa: ";
    std::cin >> win_num;

    while(win_num < 1 || win_num > board_size){
        std::cout << "Podana zla wartosc. Podaj ile figur wygrywa: ";
        std::cin >> win_num;
    }

    std::cout << "Podaj glebokosc algorytmu minimax: ";
    std::cin >> depth;

    while(depth < 1 || depth > 10){
        std::cout << "Podana zla wartosc. Podaj glebokosc algorytmu minimax: ";
        std::cin >> depth;
    }

    std::cout << "Czy chcesz sie zmierzyc z komputerem? [t/n]: ";
    std::cin >> buf;

    while(buf != 't' && buf != 'n'){
        std::cout << "Podana zla wartosc. Czy chcesz sie zmierzyc z komputerem? [t/n]: ";
        std::cin >> buf;
    }

    if(buf == 't') player = true;

    std::cout << "Kto rozpoczyna? [x/o]: ";
    std::cin >> buf;

    while(buf != 'x' && buf != 'o'){
        std::cout << "Podana zla wartosc. Kto rozpoczyna? [x/o]: ";
        std::cin >> buf;
    }

    if(buf == 'x') who_starts = true;

    std::cout << "Czy chcesz, zeby wyswietlane byly dodatkowe informacje o ruchach komputera? [t/n]: ";
    std::cin >> buf;

    while(buf != 't' && buf != 'n'){
        std::cout << "Podana zla wartosc. Czy chcesz, zeby wyswietlane byly dodatkowe informacje o ruchach komputera? [t/n]: ";
        std::cin >> buf;
    }

    if(buf == 't') info = true;

    gameHandler(board_size, win_num, depth, who_starts, player, info);
}