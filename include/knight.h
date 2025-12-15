#ifndef KNIGHT_H
#define KNIGHT_H
#include <stdbool.h>

#include "board.h"

bool can_move_knight(int y1, int x1, int y2, int x2);
bool knight_has_legal_move(int y1, int x1, bool is_black);
#endif