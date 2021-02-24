#include <iostream>
#include <array>
#include <utility>
#include <string>

#define HORIZONTAL_LINE " -----------------"

using namespace std;

constexpr size_t board_size = 5;

const string horizontal_line(board_size * 6, '-');

using game_board_t = array<array<char, board_size>, board_size>;

void print_game_board(game_board_t &board);
void init_game_board(game_board_t &board);
void place_mark(game_board_t &board, size_t row, size_t column, char mark);
pair<size_t, size_t> get_user_input(game_board_t &board);
pair<size_t, size_t> convert_tile_index_to_row_and_col(size_t tile_index);
char check_for_victory(const game_board_t &board, pair<size_t, size_t> mark_position, char mark);

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
        if (turn_counter >= 2*board_size - 1)
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

pair<size_t, size_t> get_user_input(game_board_t &board)
{
    //size_t row, col;
    pair<size_t, size_t> mark_position;
    size_t tile_index;
    while (true)
    {
        cout << "Enter mark position: ";
        cin >> tile_index;
        if (tile_index > board_size * board_size)  cout << "Invalid input. Tile position is greater than field size. Try again." << endl;
        //cin >> row >> col;
        //if (row > board_size || col > board_size) cout << "Invalid input. Column or row value are greater than field size. Try again." << endl;
        mark_position = convert_tile_index_to_row_and_col(tile_index - 1);
        if (board.at(mark_position.first).at(mark_position.second) != ' ') cout << "Tile already occupied!" << endl;
        else break;
    }
    return mark_position;
}

pair<size_t, size_t> convert_tile_index_to_row_and_col(size_t tile_index)
{
    size_t row, col;

    col = tile_index % board_size;
    row = (tile_index - col)/board_size;

    return make_pair(row, col);
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
    cout << " " << horizontal_line;
    cout << endl;
    for (auto &row : board)
    {
        for (auto &tile : row)
        {
            cout << " | " << tile << " |";
        }
        cout << endl;
        //cout << HORIZONTAL_LINE;
        cout << " " << horizontal_line;
        cout << endl;
    }
}

void place_mark(game_board_t &board, size_t row, size_t column, char mark)
{
    board.at(row).at(column) = mark;
}

char check_for_victory(const game_board_t &board, pair<size_t, size_t> mark_position, char mark)
{
    bool horizontal_win {true}, vertical_win {true}, diagonal_win {true}, antidiagonal_win {true};

    for (auto col_index = 0; col_index < board_size; ++col_index)   // check horizontal rows
    {
        if (board[mark_position.first][col_index] != mark)
        {
            horizontal_win = false;
            break;
        }
    }

    for (auto row_index = 0; row_index < board_size; ++row_index)   // check horizontal rows
    {
        if (board[row_index][mark_position.second] != mark)
        {
            vertical_win = false;
            break;
        }
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
                        diagonal_win = false;
                        goto antidiagonal_check;            // using goto to break out of nested loops
                    }
                }
            }
        }
    }
    else diagonal_win = false;

    antidiagonal_check:
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
                        antidiagonal_win = false;
                        goto final_result_calculation;     // using goto to break out of nested loops
                    }
                }
            }
        }
    }
    else antidiagonal_win = false;

    final_result_calculation:
    if (horizontal_win || vertical_win || diagonal_win || antidiagonal_win)
        return mark;
    else return 'N';  //  'N' stands for "no winner" or "next move", whatever you like more
}
