#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "game.h"

int main(){
    using namespace std;
    Game game;
    int game_mode;

    // verifica o modo de jogo
    while (!game.get_game_mode())
    {
        cout << "Selecione o modo de jogo\n1. Single Player\n2. Multiplayer\n";
        cin >> game_mode;
        
        if(game_mode == 1 || game_mode == 2){
            game.set_game_mode(game_mode);
        }
    }
    
    // inicializacao do jogo
    cout << "Iniciando jogo...\n";
    cout << "PLAYER 1 - [X] \t PLAYER 2 - [O]\n\n";
    cout << "Cada jogada é uma posicao do tabuleiro de 1 a 9\n\n";
    // cout << game.display_empty_board(empty*);
    game.print_board();
    cout << "\nO jogo comecou\n\n";
    cout << game;
    
    int play = 0;
    int move;

    // modo de jogo single player
    if(game.get_game_mode() == 1){
        // enquanto o jogo nao terminou
        while(!game.game_has_finish()){
            // realiza jogada do player 1
            if(play % 2 == 0){
                cout << "\nPlayer 1 joga: \n";
                cin >> move;
                while (game.invalid_play(move))
                {
                    cout << "Jogada invalida, Player 1 jogue novamente um valor inteiro de 1 a 9 que ainda não tenha sido jogado. \n";
                    cin >> move;
                }
                game.game_move(move, 'X');
            }
            // realiza jogada do computador
            else{
                move = game.computer_play(play);
                cout << "\nMovimento computador: " << move << "\n";

                game.game_move(move, 'O');
            }
            cout << game;
            play++;
        }
    }
    // modo de jogo multiplayer
    else if(game.get_game_mode() == 2){
        // enquanto o jogo nao terminou
        while(!game.game_has_finish()){
            // realiza jogada do player 1
            if(play % 2 == 0){
                cout << "\nPlayer 1 joga: \n";
                cin >> move;
                while (game.invalid_play(move))
                {
                    cout << "Jogada invalida, Player 1 jogue novamente um valor inteiro de 1 a 9 que ainda não tenha sido jogado. \n";
                    cin >> move;
                }
                game.game_move(move, 'X');
            }
            // realiza jogada do player 2
            else{
                cout << "\nPlayer 2 joga: \n";
                cin >> move;
                while (game.invalid_play(move))
                {
                    cout << "Jogada invalida, Player 2 jogue novamente um valor inteiro de 1 a 9 que ainda não tenha sido jogado. \n";
                    cin >> move;
                }
                game.game_move(move, 'O');
            }
            cout << game;
            play++;
        }
    }

    // sinaliza fim de jogo e diz o vencedor, ou empate
    cout << "\nGame Over!\n";

    if(game.get_winner() == 0){
        cout << "Empate, nao houve vencedor.\n";
    }
    else{
        cout << "O Jogador" << game.get_winner() << " venceu a partida!\n";
    }
 
    return 0;
}