#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(char s, const string& n) : symbol(s), name(n) {}

int Player::makeMove(const vector<char>& board) {
    int move;
    while (true) {
        cout << name << " (" << symbol << ") elige una casilla (1-9): ";
        cin >> move;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Por favor ingresa un número del 1 al 9.\n";
            continue;
        }

        if (move >= 1 && move <= 9 && board[move - 1] == ' ') {
            return move - 1;
        }
        cout << "Movimiento inválido. Intenta de nuevo.\n";
    }
}
