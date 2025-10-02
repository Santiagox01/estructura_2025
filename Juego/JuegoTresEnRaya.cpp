#include <iostream>
#include <vector>
#include <algorithm>
#include "Color.h"
#include "Player.h"

using namespace std;

void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        string cell;
        if (board[i] == 'X') cell = Color::rojo("X");
        else if (board[i] == 'O') cell = Color::azul("O");
        else cell = string(1, '1' + i);  // Mostrar números en casillas vacías

        cout << cell;
        if (i % 3 != 2) cout << " | ";
        if (i % 3 == 2 && i < 8) cout << "\n---------\n";
    }
    cout << "\n\n";
}

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

void resetBoard(vector<char>& board) {
    fill(board.begin(), board.end(), ' ');  // Reinicia el tablero
}

int main() {
    vector<char> board(9, ' ');
    Player p1('X', "Jugador 1");
    Player p2('O', "Jugador 2");

    char userChoice;
    Player* current;

    cout << "=== Tres en raya con colores ===\n";
    cout << Color::rojo("X = Jugador 1") << " | " << Color::azul("O = Jugador 2") << "\n";
    
    // Menú para que el usuario elija su símbolo
    do {
        cout << "Elige tu símbolo (X o O): ";
        cin >> userChoice;
        cin.ignore(1000, '\n');  // Limpiar buffer
        userChoice = toupper(userChoice);  // Convertir a mayúscula para evitar errores de entrada

        if (userChoice == 'X') {
            p1.symbol = 'X';
            p2.symbol = 'O';
            p1.name = "Jugador 1";
            p2.name = "Jugador 2";
            current = &p1;  // El jugador 1 comienza
        }
        else if (userChoice == 'O') {
            p1.symbol = 'O';
            p2.symbol = 'X';
            p1.name = "Jugador 2";
            p2.name = "Jugador 1";
            current = &p2;  // El jugador 2 comienza
        }
        else {
            cout << "Opción inválida, por favor elige X o O.\n";
        }
    } while (userChoice != 'X' && userChoice != 'O');

    do {
        while (true) {
            printBoard(board);  // Imprime el tablero
            cout << "Turno de " << current->name << " (" << current->symbol << ").\n";

            int move = current->makeMove(board);  // El jugador elige su movimiento
            board[move] = current->symbol;  // Marca la casilla

            if (checkWin(board, current->symbol)) {  // Verifica si el jugador ha ganado
                printBoard(board);
                cout << current->name << " gana!\n";
                break;
            }
            if (boardFull(board)) {  // Verifica si el tablero está lleno (empate)
                printBoard(board);
                cout << "Empate!\n";
                break;
            }

            // Cambia el turno
            current = (current == &p1) ? &p2 : &p1;
        }

        // Preguntar si se quiere jugar otra ronda
        char playAgain;
        cout << "¿Quieres jugar otra ronda? (s/n): ";
        cin >> playAgain;
        cin.ignore(1000, '\n'); // Limpiar buffer
        if (playAgain == 's' || playAgain == 'S') {
            resetBoard(board);  // Reinicia el tablero
            current = (current == &p1) ? &p1 : &p2;  // Cambia el jugador que comienza
            cout << "\nNueva ronda...\n\n";
        } else {
            cout << "¡Gracias por jugar! Adiós.\n";
            break;
        }

    } while (true);

    return 0;
}