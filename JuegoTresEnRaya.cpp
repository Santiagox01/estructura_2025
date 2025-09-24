#include <iostream>
#include <vector>
using namespace std;

// Tres en raya sencillo en C++

void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << (board[i] == ' ' ? char('1' + i) : board[i]);
        if (i % 3 != 2) cout << " | ";
        if (i % 3 == 2 && i < 8) cout << "\n---------\n";
    }
    cout << "\n\n";
}

//

bool checkWin(const vector<char>& b, char p) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for (auto &w : wins) {
        if (b[w[0]] == p && b[w[1]] == p && b[w[2]] == p)
            return true;
    }
    return false;
}

bool boardFull(const vector<char>& b) {
    for (char c : b) if (c == ' ') return false;
    return true;
}

int main() {
    vector<char> board(9, ' ');
    char turn = 'X';

    cout << "=== Tres en raya sencillo ===\n";

    while (true) {
        printBoard(board);
        cout << "Turno de " << turn << ". Elige una casilla (1-9): ";
        int move; cin >> move;
        if (move < 1 || move > 9 || board[move-1] != ' ') {
            cout << "Movimiento inválido. Intenta de nuevo.\n";
            continue;
        }
        board[move-1] = turn;

        if (checkWin(board, turn)) {
            printBoard(board);
            cout << "Jugador " << turn << " gana!\n";
            break;
        }
        if (boardFull(board)) {
            printBoard(board);
            cout << "Empate!\n";
            break;
        }
        turn = (turn == 'X') ? 'O' : 'X';
    }
    return 0;
}

