#ifndef PAWN_H
#define PAWN_H
#include <stdbool.h>
#include "board.h"

bool can_move_pawn(int y1, int x1, int y2, int x2, bool is_black, char promotion_piece);
bool en_passant(int y1, int x1, int y2, int x2, bool is_black);
bool pawn_has_legal_move(int y1, int x1, bool is_black);
#endif