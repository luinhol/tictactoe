#include <iostream>
#include <string>
#include <vector>
#include "game.h"

// construtor game
Game::Game(){
    Board board;
    this->board = board;
    this->winner = 0;
    this->game_mode = 0;
}

// essa funcao de display nao esta funcionando, queria imprimir o tabuleiro no inicio do jogo,
// para melhor visualizacao do jogador, mas nao consegui fazer isso utilizando cout na main
ostream& Game::display_empty_board(ostream& os){
    os << " "<<'1'<<" | "<<'2'<<" | "<<'3'<<" \n";
    os << "-----------\n";
    os << " "<<'4'<<" | "<<'5'<<" | "<<'6'<<" \n";
    os << "-----------\n";
    os << " "<<'7'<<" | "<<'8'<<" | "<<'9'<<" \n";
    return os;
}

// retorna o vencedor
int Game::get_winner(){
    return this->winner;
}

// seta o modo de jogo (1 ou 2 jogadores)
void Game::set_game_mode(int game_mode){
    this->game_mode = game_mode;
}

// retorna o modo de jogo (1 ou 2 jogadores)
int Game::get_game_mode(){
    return this->game_mode;
}

// retorna se o jogo terminou ou nao
bool Game::game_has_finish(){
    if(winner > 0 || board.board_is_full()){
        return true;
    }
    else{
        return false;
    }
}

// realiza uma jogada
void Game::game_move(int move, char play){
    this->winner = board.board_move(move, play);
}

// verifica se é uma jogada valida
bool Game::invalid_play(int move){
    int move_i = (move-1)/3;
    int move_j = (move-1)%3;
    char board[SIZE][SIZE];
    this->board.copy_board(board);

    // verifica se a jogada excede o intervalo entre 1 e 9
    if(move < 1 || move > 9)
    {
        return true;
    }
    // verifica se a jogada é uma posicao ja ocupada
    if(!this->board.empty_slot(board, move_i, move_j)){
        return true;
    }
    return false;
}

// printa o jogo vazio
void Game::print_board(){
    cout << " "<<'1'<<" | "<<'2'<<" | "<<'3'<<" \n";
    cout << "-----------\n";
    cout << " "<<'4'<<" | "<<'5'<<" | "<<'6'<<" \n";
    cout << "-----------\n";
    cout << " "<<'7'<<" | "<<'8'<<" | "<<'9'<<" \n";
}

// realiza jogada do jogador
int Game::computer_play(int play){
    char board[3][3];
    this->board.copy_board(board);

    return this->board.best_move(board, play);
}

// overloading operator para print do jogo
ostream& operator<<(ostream& os, Game& g){
    os << g.board;
    return os;
}