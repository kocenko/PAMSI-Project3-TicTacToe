#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "board.hh"


int evaluate(Board &board);
bool horizontal_win(Board &board, bool maximizer);
bool vertical_win(Board &board, bool maximizer);
bool diagonal_win(Board &board, bool maximizer);
bool top2bot_diagonal_win(Board &board, bool maximizer);
bool bot2top_diagonal_win(Board &board, bool maximizer);

#endif  // FUNCTIONS_HH