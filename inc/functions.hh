#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "board.hh"


struct Move{
    int row, column;
};

int evaluate(Board board, int depth);
int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn);
Move choose_move(Board board, int depth, int alpha, int beta, bool maximizers_turn);

#endif  // FUNCTIONS_HH