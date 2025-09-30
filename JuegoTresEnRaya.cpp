#include <iostream>
#include <vector>
#include <cstdlib> // Para la opción de reiniciar el juego
using namespace std;

// Clase para manejar colores en consola (ANSI)
class Color {
public:
    static string rojo(const string& txt) { return "\033[31m" + txt + "\033[0m"; }
    static string azul(const string& txt) { return "\033[34m" + txt + "\033[0m"; }
    static string reset() { return "\033[0m"; }
};

// Clase Player
class Player {
public:
    char symbol;
    string name;

    Player(char s, string n) : symbol(s), name(n) {}

    int makeMove(const vector<char>& board) {
        int move;
        while (true) {
            cout << name << " (" << symbol << ") elige una casilla (1-9): ";
            cin >> move;
            if (move >= 1 && move <= 9 && board[move-1] == ' ') {
                return move - 1;
            }
            cout << "Movimiento inválido. Intenta de nuevo.\n";
        }
    }
};

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
    Player* current = &p1;

    cout << "=== Tres en raya con colores ===\n";
    cout << Color::rojo("X = Jugador 1") << " | " << Color::azul("O = Jugador 2") << "\n";

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
        if (playAgain == 's' || playAgain == 'S') {
            resetBoard(board);  // Reinicia el tablero
            current = &p1;  // Reinicia el turno
            cout << "\nNueva ronda...\n\n";
        } else {
            cout << "¡Gracias por jugar! Adiós.\n";
            break;
        }

    } while (true);

    return 0;
}
