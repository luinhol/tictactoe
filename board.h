#ifndef BOARD_H
#define BOARD_H

#define SIZE 3

#include <string>

using namespace std;

class Board
{
    char board[SIZE][SIZE];
    bool board_full;
public:
    Board();
    char get_element(int posi_i, int posi_j);
    char get_element_value(int posi_i, int posi_j);
    int board_move(int move, char play);
    bool board_is_full();
    bool game_over();
    void copy_board(char board[SIZE][SIZE]);
    bool empty_slot(char board[SIZE][SIZE], int move_i, int move_j);
    friend ostream& operator<<(ostream& os, Board& b);
    int minimax(char board[SIZE][SIZE], int depth, bool isCOM);
    int best_move(char board[SIZE][SIZE], int moveIndex);
    bool minmax_game_over(char board[SIZE][SIZE]);
};

#endif // !BOARD_H