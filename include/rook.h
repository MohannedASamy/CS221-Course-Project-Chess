#ifndef ROOK_H
#define ROOK_H

#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
bool can_move_rook(int y1, int x1, int y2, int x2);
bool rook_has_legal_move(int y1, int x1, bool is_black);
#endif