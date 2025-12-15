#ifndef BISHOP_H
#define BISHOP_H

#include "board.h"
#include <stdbool.h>

bool can_move_bishop(int y1, int x1, int y2, int x2);
bool bishop_has_legal_move(int y1, int x1, bool is_black);
#endif