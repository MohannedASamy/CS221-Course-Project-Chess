#include "queen.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool can_move_queen(y1, x1, y2, x2)
{
    if ((can_move_bishop(y1, x1, y2, x2)) || (can_move_rook(y1, x1, y2, x2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}