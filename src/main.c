#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#define size 10
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool move(int y1, int x1, int y2, int x2, bool is_black, char promotion_piece);
// Note: Parameters are ordered as (y, x) because the board is accessed as board[y][x].
// We should keep this ordering consistent throughout the code.
char *read_input(void);
bool has_legal_move(bool is_black);
int main()
{
    char *players[] = {"White", "Black"};
    commit_position();
    for (;;)
    {
        turn = half_turn / 2 + 1;
        player_number = half_turn % 2;
        display_board();
        bool in_check = is_in_check(player_number);
        if (in_check)
            printf("Check!\n");
        printf("%d-%s: ", turn, players[player_number]);
        char *input = read_input();
        int len = strlen(input);
        if (len > 5 || len < 4)
        {
            printf("invalid input\nplease : enter your move again\n");
            continue;
        }
        int x1 = toupper(input[0]) - 'A', y1 = input[1] - '1', x2 = toupper(input[2]) - 'A', y2 = input[3] - '1';
        if (!move(y1, x1, y2, x2, player_number, input[4]))
            continue;

        half_turn++;
    }
    return 0;
}

bool move(int y1, int x1, int y2, int x2, bool is_black, char promotion_piece)
{
    if (x1 > 7 || x1 < 0 || x2 > 7 || x2 < 0 || y1 > 7 || y1 < 0 || y2 > 7 || y2 < 0)
    {
        printf("Invalid input!\n");
        return false;
    }
    if ((!islower(board[y1][x1]) && !is_black) || (!isupper(board[y1][x1]) && is_black))
    {
        printf("You don't have a piece on this square.\n");
        return false;
    }
    if ((islower(board[y2][x2]) && !is_black) || (isupper(board[y2][x2]) && is_black))
    {
        printf("You cannot capture one of your own pieces.\n");
        return false;
    }
    if (promotion_piece != '\0' && tolower(board[y1][x1]) != 'p')
    {
        printf("Illegal move!\n");
        return false;
    }
    bool can_move = true;
    switch (board[y1][x1])
    {
    case 'k':
    case 'K':
        if (castle(y1, x1, y2, x2, is_black))
        {
            // Unlike other move functions, castle() and en_passant() implicitly perform
            // the move on the board and verify that the king is not left in check
            // and if the king is in check, they reset the position.
            // That is why, if they return true, the function can return true directly.
            commit_position();
            return true;
        }
        can_move = can_move_king(y1, x1, y2, x2);
        if (can_move)
        {
            king_location[is_black][0] = y2;
            king_location[is_black][1] = x2;
            king_moved[is_black] = true;
        }
        break;
    case 'q':
    case 'Q':
        can_move = can_move_queen(y1, x1, y2, x2);
        break;
    case 'r':
    case 'R':
        can_move = can_move_rook(y1, x1, y2, x2);
        if (can_move && y1 == 0 + is_black * 7)
        {
            if (x1 == 0)
                a_rook_moved[is_black] = true;
            else if (x1 == 7)
                h_rook_moved[is_black] = true;
        }
        break;
    case 'b':
    case 'B':
        can_move = can_move_bishop(y1, x1, y2, x2);
        break;
    case 'n':
    case 'N':
        can_move = can_move_knight(y1, x1, y2, x2);
        break;
    case 'p':
    case 'P':
        if (en_passant(y1, x1, y2, x2, is_black))
        {
            // Unlike other move functions, castle() and en_passant() implicitly perform
            // the move on the board and verify that the king is not left in check
            // and if the king is in check, they reset the position.
            // That is why, if they return true, the function can return true directly.
            commit_position();
            return true;
        }
        can_move = can_move_pawn(y1, x1, y2, x2, is_black, promotion_piece);
        break;
    }
    if (!can_move)
    {
        printf("Illegal move!\n");
        return false;
    }
    if (isalpha(board[y2][x2]))
        capture[!is_black][num_capture[!is_black]++] = board[y2][x2];
    board[y2][x2] = board[y1][x1];
    set_square_color(y1, x1);

    if (is_in_check(is_black))
    {
        printf("Illegal move: you cannot move your king into check or leave him in check.\n");
        reset_position();
        return false;
    }
    commit_position();
    return true;
}
char *read_input(void)
{
    char buffer[10];
    char *full_input = NULL;
    int full_size = 0;
    while (1)
    {
        if (fgets(buffer, size, stdin) == NULL)
        { // read input and if no thing reading break the loop
            break;
        }
        int current_input = strlen(buffer);
        char *temp = (char *)realloc(full_input, full_size + current_input + 1);
        if (temp == NULL)
        {
            printf("failed realloc");
            free(full_input);
        }
        full_input = temp;
        if (full_size == 0)
        {
            strcpy(full_input, buffer);
        }
        else
        {
            strcat(full_input, buffer);
        }
        full_size += current_input;
        if (current_input < size - 1 || buffer[current_input - 1] == '\n')
        {
            break;
        }
    }
    if (full_input[full_size - 1] = '\n' && full_size > 0)
    {
        full_input[full_size - 1] = '\0';
    }
    return full_input;
}

bool has_legal_move(bool is_black)
{
    bool has_legal_move = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((islower(board[i][j]) && !is_black) || (isupper(board[i][j]) && is_black))
            {
                switch (board[i][j])
                {
                case 'k':
                case 'K':
                    has_legal_move = king_has_legal_move(i, j, is_black);
                    break;
                case 'q':
                case 'Q':
                    has_legal_move = queen_has_legal_move(i, j, is_black);
                    break;
                case 'r':
                case 'R':
                    has_legal_move = rook_has_legal_move(i, j, is_black);

                    break;
                case 'b':
                case 'B':
                    has_legal_move = bishop_has_legal_move(i, j, is_black);
                    break;
                case 'n':
                case 'N':
                    has_legal_move = knight_has_legal_move(i, j, is_black);
                    break;
                case 'p':
                case 'P':
                    has_legal_move = pawn_has_legal_move(i, j, is_black);
                    break;
                }
            }
            if (has_legal_move)
            {
                return true;
            }
        }
    }
    return false;
}