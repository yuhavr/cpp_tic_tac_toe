#include <iostream>
#include "tic_tac_toe.h"

int main()
{
    game_board_t game_board;
    init_game_board(game_board);
    int turn_counter = 1;
    print_game_board(game_board);
    pair<size_t, size_t> mark_position;
    char mark;
    bool x_turn = true;
    while (true)
    {
        mark_position = get_user_input(game_board);
        if (x_turn) mark = 'X';
        else mark = '0';
        place_mark(game_board, mark_position.first, mark_position.second, mark);
        if (turn_counter >= static_cast<int>(2*board_size - 1))
        {
            if (check_for_victory(game_board, mark_position, mark) == 'X' || check_for_victory(game_board, mark_position, mark) == '0')
            {
                print_game_board(game_board);
                cout << mark << " wins!";
                break;
            }
        }
        print_game_board(game_board);
        x_turn = !x_turn;
        if (turn_counter == board_size * board_size)
        {
            cout << "It's a draw!";
            break;
        }
        ++turn_counter;
    }

    return 0;
}
