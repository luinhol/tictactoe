#include <iostream>
#include <string>
#include <vector>
#include "board.h"

// construtor tabuleiro
Board::Board(){
    char k = '1';
    int i = 0, j = 0;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++)
        {
            this->board[i][j] = k;
            k++;
        }
    }
    this->board_full = false;
}

// retorna elemento da posicao i, j "X, O OU - "
char Board::get_element(int posi_i, int posi_j){
    if(board[posi_i][posi_j] <= '9' && board[posi_i][posi_j] >= '1'){
        return '-';
    }
    else{
        return board[posi_i][posi_j];
    }
}

// retorna elemetno da posicao i, j "X, O OU 1-9 "
char Board::get_element_value(int posi_i, int posi_j){
    return board[posi_i][posi_j];
}

// realiza o movimento no tabuleiro e verifica se houve vencedor na rodada em questao, ou se o jogo empatou
int Board::board_move(int move, char play){
    // traduz a jogada de 1-9 para i, j
    int move_i = (move-1)/SIZE;
    int move_j = (move-1)%SIZE;

    // realiza a jogada 'X' ou 'O' na posicao i, j
    board[move_i][move_j] = play;

    // retorna vencedor
    if(game_over()){
        if(play == 'X'){
            return 1;
        }
        else if (play == 'O')
        {
            return 2;
        }
    }
    // retorna empate
    else if(board_is_full()){
        this->board_full = true;
        return 0;
    }
    return 0;
}

// verifica se o tabuleiro esta cheio
bool Board::board_is_full(){
    int i, j;

    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++)
        if(board[i][j] <= '9' && board[i][j] >= '1'){
            return false;
        }
    }
    return true;
}

// verifica se o jogo tem algum vencedor
bool Board::game_over(){
    int i, j;

    for(i = 0; i < SIZE; i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] || board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            return true;
        }
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] || board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }
    return false;
}

// verifica se a posicao i, j está vazia
bool Board::empty_slot(char board[SIZE][SIZE], int move_i, int move_j){
    if(board[move_i][move_j] == 'X' || board[move_i][move_j] == 'O'){
        return false;
    }
    return true;
}

// operator overloading para cout
ostream& operator<<(ostream& os, Board& b){
    os << " "<<b.get_element(0,0)<<" | "<<b.get_element(0,1)<<" | "<<b.get_element(0,2)<<" \n";
    os << "-----------\n";
    os << " "<<b.get_element(1,0)<<" | "<<b.get_element(1,1)<<" | "<<b.get_element(1,2)<<" \n";
    os << "-----------\n";
    os << " "<<b.get_element(2,0)<<" | "<<b.get_element(2,1)<<" | "<<b.get_element(2,2)<<" \n";
    return os;
}

// funcao minimax, responsavel por encontrar a melhor jogada
int Board::minimax(char board[SIZE][SIZE], int depth, bool isCOM){
    int score = 0;
    int best_score = 0;
    int i, j;
    int x, y;
    
    // retorna -1 quando encontra um fim de jogo e o computador perdeu,
    // e +1 quando encontra um fim de jogo que o computador ganhou
    if (minmax_game_over(board)){
        if(isCOM){
            return -1;
        }
        else if(!isCOM){
            return +1;
        }
        return 0;
    }
    // quando o jogo ainda nao tem vencedores
    else{
        // verifica se a profundidade limite foi atingida
        if(depth < 9){
            // verifica se é a vez do computador de jogar
            if(isCOM){
                // caso seja a vez do computador ele deve encontrar o maior pontuacao possível de jogada
                best_score = -999;

                // para isso ele vai simular jogadas possiveis dentro do tabuleiro
                for(i = 0; i < SIZE; i++){
                    for(j = 0; j < SIZE; j++){
                        // quando encontrar um espaco vazio no tabuleiro, ele tenta uma jogada na posicao
                        // e verifica a pontuacao obtida
                        if(empty_slot(board, i, j)){
                            board[i][j] = 'O';
                            // ele realiza uma recursao entao, para encontrar a pontuacao da jogada
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '1' + i*SIZE+j;

                            // minimax entao encontra a maior pontuacao
                            if(score > best_score){
                                best_score = score;
                            }
                        }
                    }
                }
                // retorna o valor da maior pontuacao
                return best_score;
            }
            // ou se é a vez do adversário de jogar
            else{
                // caso seja a vez do adversario ele deve encontrar o menor pontuacao possível de jogada
                best_score = 999;

                // para isso ele vai simular jogadas possiveis dentro do tabuleiro
                for(i = 0; i < SIZE; i++){
                    for(j = 0; j < SIZE; j++){
                        // quando encontrar um espaco vazio no tabuleiro, ele tenta uma jogada na posicao
                        // e verifica a pontuacao obtida
                        if(empty_slot(board, i, j)){
                            board[i][j] = 'X';
                            // ele realiza uma recursao entao, para encontrar a pontuacao da jogada
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '1' + i*SIZE+j;

                            // minimax entao encontra a menor pontuacao
                            if(score < best_score){
                                best_score = score;
                            }
                        }
                    }
                }
                // retorna o valor da menor pontuacao
                return best_score;
            }
        }
        else{
            // caso a profundidade max tenha sido atingida, minimax retorna 0
            return 0;
        }
    }
}

// funcao responsavel por receber o tabuleiro apos a jogada do adversario, e retornar a jogada que minimax fez
int Board::best_move(char board[SIZE][SIZE], int moveIndex){
    int i, j, bm = -1, score = 0, best_score = -999;

    int x, y;

    // varre o tabuleiro
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            // procurando espacos vazios
            if(empty_slot(board, i, j)){
                board[i][j] = 'O';
                // realiza entao minimax para encontrar a pontuacao da jogada
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '1' + i*SIZE+j;

                // armazena entao a maior pontuacao e a melhor jogada
                if(score > best_score){
                    best_score = score;
                    bm = 1 + i*SIZE+j;
                }
            }
        }
    }
    // retorna entao a melhor jogada a ser realizada
    return bm;
}

// copia o tabuleiro para uma variavel
void Board::copy_board(char board[SIZE][SIZE]){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            board[i][j] = get_element_value(i, j);
        }
    }
}

// verifica se o tabuleiro que minimax esta analizando possui um vencedor
bool Board::minmax_game_over(char board[SIZE][SIZE]){
    int i, j;

    for(i = 0; i < SIZE; i++){
        // row / column cross
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] || board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            return true;
        }
    }
    // diagonal cross
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] || board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }
    return false;
}