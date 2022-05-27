#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "board.hh"

int evaluate(Board board);
bool horizontal_win(Board board, bool maximizer);
bool vertical_win(Board board, bool maximizer);
bool diagonal_win(Board board, bool maximizer);
bool x_won(Board board, bool maximizer);
bool top2bot_diagonal_win(Board board, bool maximizer);
bool bot2top_diagonal_win(Board board, bool maximizer);
int minimax_alpha_beta(Board board, int depth, int alpha, int beta, bool maximizers_turn);

#endif  // FUNCTIONS_HH