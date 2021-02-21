#include <iostream>
#include <array>
#include <utility>

#define HORIZONTAL_LINE " -----------------"

using namespace std;

constexpr size_t board_size = 3;

using game_board_t = array<array<char, board_size>, board_size>;

void print_game_board(game_board_t &board);
void init_game_board(game_board_t &board);
void place_mark(game_board_t &board, size_t row, size_t column, char mark);
pair<size_t, size_t> get_user_input(game_board_t &board);
char check_for_victory(const game_board_t &board);

int main()
{
    game_board_t game_board;
    init_game_board(game_board);
    int turn_counter = 0;
    print_game_board(game_board);
    char mark;
    bool x_turn = true;
    while (true)
    {
        pair<size_t, size_t> mark_position = get_user_input(game_board);
        if (x_turn) mark = 'X';
        else mark = '0';
        place_mark(game_board, mark_position.first, mark_position.second, mark);
        if (turn_counter > 3)
        {

            if (check_for_victory(game_board) == 'X' || check_for_victory(game_board) == '0')
            {
                print_game_board(game_board);
                break;
            }
        }
        print_game_board(game_board);
        x_turn = !x_turn;
        ++turn_counter;
    }

    return 0;
}

pair<size_t, size_t> get_user_input(game_board_t &board)
{
    size_t row, col;
    while (true)
    {
        cout << "Enter mark position(row and column): ";
        cin >> row >> col;
        if (row > 3 || col > 3) cout << "Invalid input. Column or row value are greater than field size. Try again." << endl;
        if (board.at(row - 1).at(col - 1) != ' ') cout << "Tile already occupied!" << endl;
        else break;
    }
    return make_pair(row - 1, col - 1);   // subtracting one to convert row and column number to correct array index
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
    cout << HORIZONTAL_LINE;
    cout << endl;
    for (auto &row : board)
    {
        for (auto &tile : row)
        {
            cout << " | " << tile << " |";
        }
        cout << endl;
        cout << HORIZONTAL_LINE;
        cout << endl;
    }
}

void place_mark(game_board_t &board, size_t row, size_t column, char mark)
{
    board.at(row).at(column) = mark;
}

char check_for_victory(const game_board_t &board)
{
    for (auto& row : board)   // check horizontal rows
    {
        if (row[0] != ' ' && row[0] == row[1] && row[1] == row[2])
        {
            cout << row[0] << " wins!";
            return row[0];
        }
    }

    if ((board[0][0] == board[1][1] && board[1][1] == [2][2]) && (board[0][2] == board[1][1] && board[1][1] == [2][0]))  //check diagonals
    {
            cout << board[0][0] << " wins!";
            return row[0];
    }

    return 'N';
}
