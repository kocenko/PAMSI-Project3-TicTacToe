#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "board.hh"
#include "functions.hh"

#define INF_SUBSTITUTE 10000


int main(){
    Board board(3, 3, 'x', 'o', '_');
    std::string tests_path = "../winning_state_tests.txt";
    int label, counter = 0, line = 0;
    std::string buffer, new_board;
    std::ifstream file;

    file.open(tests_path);
    if(file.is_open()){
        while(getline(file, buffer)){
            new_board = buffer.substr(0, 9);
            label = std::stoi(buffer.substr(9, buffer.size()-9));
            board.set_fields(new_board);
            if(evaluate(board, 0) != label){
                counter++;
                std::cerr << line << std::endl;
            }
            line++;
        }
        file.close();
    }
    std::cout << "Found: " << counter << " inaccuraties." << std::endl;
}