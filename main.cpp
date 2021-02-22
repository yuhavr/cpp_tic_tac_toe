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
char check_for_victory(const game_board_t &board, pair<size_t, size_t> mark_position, char mark);

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
        if (turn_counter > 2*board_size - 1)
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

char check_for_victory(const game_board_t &board, pair<size_t, size_t> mark_position, char mark)
{
    char result;   //  'N' stands for "no winner" or "next move", whatever you like more

    for (auto col_index = 0; col_index < board_size; ++col_index)   // check horizontal rows
    {
        if (board[mark_position.first][col_index] != mark)
        {
            result = 'N';
            break;
        }
        else { result = mark; }
    }

    for (auto row_index = 0; row_index < board_size; ++row_index)   // check horizontal rows
    {
        if (board[row_index][mark_position.second] != mark)
        {
            result = 'N';
            break;
        }
        else { result = mark; }
    }

    if (mark_position.first == mark_position.second)  //check main diagonal
    {
        for (auto row_index = 0; row_index < board_size; ++row_index)
        {
            for (auto col_index = 0; col_index < board_size; ++col_index)
            {
                if (row_index == col_index)
                {
                    if (board[row_index][col_index] != mark)
                    {
                        result = 'N';
                        break;
                    }
                    else { result = mark; }
                }
            }
        }
    }

    if (mark_position.first + mark_position.second == board_size - 1)   // check anti-diagonal
    {
        for (auto row_index = 0; row_index < board_size; ++row_index)
        {
            for (auto col_index = 0; col_index < board_size; ++col_index)
            {
                if (row_index + col_index == board_size - 1)
                {
                    if (board[row_index][col_index] != mark)
                    {
                        result = 'N';
                        break;
                    }
                    else { result = mark; }
                }
            }
        }
    }

    return result;
}
