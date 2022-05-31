#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "board.hh"
#include "move_struct.hh"


int evaluate(Board board, int depth);
int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn);
Move choose_move(Board board, int depth, bool maximizers_turn);
void gameHandler(int board_size, int win_size, int depth, bool who_starts, bool human, bool info);

#endif  // FUNCTIONS_HH