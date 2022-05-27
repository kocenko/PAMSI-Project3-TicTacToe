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









    // int row, column;
    // std::string tab = {'x', 'o', 'x', 'o', 'o', 'x', '_', '_', '_'};
    // Board board(3, 3, 'x', 'o', '_');
    // Move opponent_move, player_move;
    // board.set_fields(tab);
    // // board.display();
    // player_move = choose_move(board, 5, -INF_SUBSTITUTE, INF_SUBSTITUTE, true);
    // board.make_move(player_move.row, player_move.column, true);
    // while(!board.game_over()){
    //     // std::cout << "Podaj gdzie chcesz wykonac ruch [wiersz, kolumna]: ";
    //     // std::cin >> row;
    //     // std::cin >> column;
    //     // std::cout << std::endl;
    //     player_move = choose_move(board, 5, -INF_SUBSTITUTE, INF_SUBSTITUTE, true);
    //     board.make_move(player_move.row, player_move.column, true);
    //     opponent_move = choose_move(board, 5, -INF_SUBSTITUTE, INF_SUBSTITUTE, false);
    //     board.make_move(opponent_move.row, opponent_move.column, false);
    //     // board.display();

    //     std::chrono::milliseconds timespan(1000); // or whatever
    //     std::this_thread::sleep_for(timespan);
    // }
    // if(board.x_won(true)){
    //     std::cout << "Wygral gracz rozpoczynajacy" << std::endl;
    // }
    // else if(board.x_won(false)){
    //     std::cout << "Wygral gracz drugi" << std::endl;
    // }
    // else{
    //     std::cout << "Remis" << std::endl;
    // }
}