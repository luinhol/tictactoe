#ifndef GAME_H
#define GAME_H

#include <string>
#include "board.h"
#include <sstream>

using namespace std;

class Game
{
    Board board;
    int winner;
    int game_mode;
public:
    Game();
    int get_game_mode();
    void set_game_mode(int game_mode);
    bool game_has_finish();
    void game_move(int move, char play);
    void print_board();
    int get_winner();
    bool invalid_play(int move);
    int computer_play(int play);
    friend ostream& operator<<(ostream& os, Game& g);
    ostream& display_empty_board(ostream& os);
};

#endif // !GAME_H