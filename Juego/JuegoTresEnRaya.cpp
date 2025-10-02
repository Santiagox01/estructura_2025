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
        else cell = string(1, '1' + i);

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
    fill(board.begin(), board.end(), ' ');
}

void showInstructions() {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      INSTRUCCIONES - TRES EN RAYA     ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << "🎯 OBJETIVO:\n";
    cout << "   Alinea tres símbolos en horizontal, vertical o diagonal\n\n";
    cout << "🎮 CÓMO JUGAR:\n";
    cout << "   1. Elige tu símbolo (X o O)\n";
    cout << "   2. Los jugadores se turnan para elegir casillas\n";
    cout << "   3. Ingresa un número del 1 al 9 según el tablero:\n\n";
    cout << "      1 | 2 | 3\n";
    cout << "      ---------\n";
    cout << "      4 | 5 | 6\n";
    cout << "      ---------\n";
    cout << "      7 | 8 | 9\n\n";
    cout << "🎨 COLORES:\n";
    cout << "   " << Color::rojo("X = Jugador 1 (Rojo)") << "\n";
    cout << "   " << Color::azul("O = Jugador 2 (Azul)") << "\n\n";
    cout << "Presiona ENTER para continuar...";
    cin.get();
}

int showMainMenu() {
    int option;
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║       🎮 TRES EN RAYA - MENÚ 🎮       ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << "  1️⃣  Jugar\n";
    cout << "  2️⃣  Instrucciones\n";
    cout << "  3️⃣  Salir\n\n";
    cout << "Selecciona una opción: ";
    
    while (!(cin >> option) || option < 1 || option > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opción inválida. Por favor elige 1, 2 o 3: ";
    }
    cin.ignore(1000, '\n');
    return option;
}

void playGame() {
    vector<char> board(9, ' ');
    Player p1('X', "Jugador 1");
    Player p2('O', "Jugador 2");

    char userChoice;
    Player* current;

    cout << "\n=== Tres en raya con colores ===\n";
    cout << Color::rojo("X = Jugador 1") << " | " << Color::azul("O = Jugador 2") << "\n";
    
    do {
        cout << "Elige tu símbolo (X o O): ";
        cin >> userChoice;
        cin.ignore(1000, '\n');
        userChoice = toupper(userChoice);

        if (userChoice == 'X') {
            p1.symbol = 'X';
            p2.symbol = 'O';
            p1.name = "Jugador 1";
            p2.name = "Jugador 2";
            current = &p1;
        }
        else if (userChoice == 'O') {
            p1.symbol = 'O';
            p2.symbol = 'X';
            p1.name = "Jugador 2";
            p2.name = "Jugador 1";
            current = &p2;
        }
        else {
            cout << "Opción inválida, por favor elige X o O.\n";
        }
    } while (userChoice != 'X' && userChoice != 'O');

    do {
        while (true) {
            printBoard(board);
            cout << "Turno de " << current->name << " (" << current->symbol << ").\n";

            int move = current->makeMove(board);
            board[move] = current->symbol;

            if (checkWin(board, current->symbol)) {
                printBoard(board);
                cout << current->name << " gana!\n";
                break;
            }
            if (boardFull(board)) {
                printBoard(board);
                cout << "Empate!\n";
                break;
            }

            current = (current == &p1) ? &p2 : &p1;
        }

        char playAgain;
        cout << "¿Quieres jugar otra ronda? (s/n): ";
        cin >> playAgain;
        cin.ignore(1000, '\n');
        if (playAgain == 's' || playAgain == 'S') {
            resetBoard(board);
            current = (current == &p1) ? &p1 : &p2;
            cout << "\nNueva ronda...\n\n";
        } else {
            cout << "¡Gracias por jugar! Adiós.\n";
            break;
        }

    } while (true);
}

int main() {
    while (true) {
        int option = showMainMenu();
        
        if (option == 1) {
            playGame();
        }
        else if (option == 2) {
            showInstructions();
        }
        else if (option == 3) {
            cout << "\n¡Hasta pronto! 👋\n";
            break;
        }
    }
    
    return 0;
}
