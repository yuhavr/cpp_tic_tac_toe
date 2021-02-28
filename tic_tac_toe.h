#ifndef TIC_TAC_TOE_H_INCLUDED
#define TIC_TAC_TOE_H_INCLUDED

#include <array>
#include <utility>

using namespace std;

constexpr size_t board_size = 3;

using game_board_t = array<array<char, board_size>, board_size>;

const string horizontal_line(board_size * 6, '-');

void print_game_board(game_board_t &board);
void init_game_board(game_board_t &board);
void place_mark(game_board_t &board, size_t row, size_t column, char mark);
pair<size_t, size_t> get_user_input(game_board_t &board);
pair<size_t, size_t> convert_tile_index_to_row_and_col(size_t tile_index);
char check_for_victory(const game_board_t &board, pair<size_t, size_t> mark_position, char mark);

#endif // TIC_TAC_TOE_H_INCLUDED
