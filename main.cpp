#include <iostream>
#include <array>

using namespace std;

constexpr int board_size = 3;

using game_board_t = array<array<char, board_size>, board_size>;

void print_game_board(game_board_t &board);
void init_game_board(game_board_t &board);

int main()
{
    game_board_t game_board;
    init_game_board(game_board);


    print_game_board(game_board);

    return 0;
}


void init_game_board(game_board_t &board)
{
    for (auto& row : board)
    {
        for (auto& tile : row)
        {
            tile = ' ';
        }
    }
}

void print_game_board(game_board_t &board)
{
    for (auto &row : board)
    {
        for (auto &tile : row)
        {
            cout << " | " << tile << " | ";
        }
        cout << endl << endl;
    }
}
