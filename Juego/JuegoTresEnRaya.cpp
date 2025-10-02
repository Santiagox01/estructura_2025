#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "Color.h"
#include "Player.h"

using namespace std;

struct GameState {
    vector<char> board;
    char currentPlayer;
    char p1Symbol;
    char p2Symbol;
    char player1Symbol;
    string name;
};

struct Score {
    int player1Wins = 0;
    int player2Wins = 0;
    int draws = 0;
};

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

Score loadScores() {
    Score score;
    ifstream file("scores.txt");
    if (file.is_open()) {
        file >> score.player1Wins >> score.player2Wins >> score.draws;
        file.close();
    }
    return score;
}

void saveScores(const Score& score) {
    ofstream file("scores.txt");
    if (file.is_open()) {
        file << score.player1Wins << " " << score.player2Wins << " " << score.draws;
        file.close();
    }
}

void showScores() {
    Score score = loadScores();
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║         📊 TABLA DE PUNTUACIONES       ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << Color::rojo("  Jugador 1 (X)") << ": " << score.player1Wins << " victorias\n";
    cout << Color::azul("  Jugador 2 (O)") << ": " << score.player2Wins << " victorias\n";
    cout << "  Empates: " << score.draws << "\n\n";
    cout << "Presiona ENTER para continuar...";
    cin.get();
}

void saveGame(const GameState& state) {
    ofstream file("partidas_guardadas.txt", ios::app);
    if (file.is_open()) {
        file << state.name << "|";
        for (char c : state.board) {
            file << c;
        }
        file << "|" << state.currentPlayer << "|" << state.p1Symbol << "|" << state.p2Symbol << "|" << state.player1Symbol << "\n";
        file.close();
        cout << "\n✅ Partida guardada exitosamente!\n";
    } else {
        cout << "\n❌ Error al guardar la partida.\n";
    }
}

vector<GameState> loadSavedGames() {
    vector<GameState> games;
    ifstream file("partidas_guardadas.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            GameState state;
            string boardStr;
            
            getline(ss, state.name, '|');
            getline(ss, boardStr, '|');
            
            state.board.resize(9);
            for (int i = 0; i < 9; i++) {
                state.board[i] = boardStr[i];
            }
            
            string temp;
            getline(ss, temp, '|');
            state.currentPlayer = temp[0];
            getline(ss, temp, '|');
            state.p1Symbol = temp[0];
            getline(ss, temp, '|');
            state.p2Symbol = temp[0];
            getline(ss, temp, '|');
            if (!temp.empty()) {
                state.player1Symbol = temp[0];
            } else {
                state.player1Symbol = 'X';
            }
            
            games.push_back(state);
        }
        file.close();
    }
    return games;
}

void deleteSavedGame(int index) {
    vector<GameState> games = loadSavedGames();
    if (index >= 0 && index < games.size()) {
        games.erase(games.begin() + index);
        
        ofstream file("partidas_guardadas.txt");
        if (file.is_open()) {
            for (const auto& state : games) {
                file << state.name << "|";
                for (char c : state.board) {
                    file << c;
                }
                file << "|" << state.currentPlayer << "|" << state.p1Symbol << "|" << state.p2Symbol << "|" << state.player1Symbol << "\n";
            }
            file.close();
            cout << "\n✅ Partida eliminada exitosamente!\n";
        }
    }
}

void showSavedGames() {
    vector<GameState> games = loadSavedGames();
    
    if (games.empty()) {
        cout << "\n📁 No hay partidas guardadas.\n";
        return;
    }
    
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║        💾 PARTIDAS GUARDADAS          ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    
    for (size_t i = 0; i < games.size(); i++) {
        cout << "  " << (i + 1) << ". " << games[i].name << "\n";
    }
    cout << "\n";
}

void manageSavedGames() {
    vector<GameState> games = loadSavedGames();
    
    if (games.empty()) {
        cout << "\n📁 No hay partidas guardadas.\n";
        cout << "Presiona ENTER para continuar...";
        cin.get();
        return;
    }
    
    showSavedGames();
    
    cout << "¿Deseas eliminar alguna partida? (s/n): ";
    char choice;
    cin >> choice;
    cin.ignore(1000, '\n');
    
    if (choice == 's' || choice == 'S') {
        cout << "Ingresa el número de la partida a eliminar (0 para cancelar): ";
        int num;
        cin >> num;
        cin.ignore(1000, '\n');
        
        if (num > 0 && num <= games.size()) {
            deleteSavedGame(num - 1);
        }
    }
    
    cout << "Presiona ENTER para continuar...";
    cin.get();
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
    cout << "   4. Durante el juego puedes escribir 'guardar' para guardar la partida\n\n";
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
    cout << "  1️⃣  Nueva Partida\n";
    cout << "  2️⃣  Cargar Partida Guardada\n";
    cout << "  3️⃣  Gestionar Partidas Guardadas\n";
    cout << "  4️⃣  Ver Puntuaciones\n";
    cout << "  5️⃣  Instrucciones\n";
    cout << "  6️⃣  Salir\n\n";
    cout << "Selecciona una opción: ";
    
    while (!(cin >> option) || option < 1 || option > 6) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opción inválida. Por favor elige entre 1 y 6: ";
    }
    cin.ignore(1000, '\n');
    return option;
}

int chooseWhoStarts() {
    cout << "\n¿Quién debe comenzar?\n";
    cout << "  1. Jugador 1 (X)\n";
    cout << "  2. Jugador 2 (O)\n";
    cout << "  3. Aleatorio\n";
    cout << "Selecciona una opción: ";
    
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opción inválida. Elige 1, 2 o 3: ";
    }
    cin.ignore(1000, '\n');
    
    if (choice == 3) {
        srand(time(0));
        choice = (rand() % 2) + 1;
        cout << "\n🎲 Inicio aleatorio: ";
        if (choice == 1) {
            cout << Color::rojo("Jugador 1 (X)") << " comienza!\n";
        } else {
            cout << Color::azul("Jugador 2 (O)") << " comienza!\n";
        }
        cout << "Presiona ENTER para continuar...";
        cin.get();
    }
    
    return choice;
}

void playGame(GameState* loadedState = nullptr) {
    vector<char> board(9, ' ');
    Player p1('X', "Jugador 1");
    Player p2('O', "Jugador 2");
    Player* current;
    Score score = loadScores();
    string gameName;
    char player1Symbol;
    
    if (loadedState) {
        board = loadedState->board;
        p1.symbol = loadedState->p1Symbol;
        p2.symbol = loadedState->p2Symbol;
        current = (loadedState->currentPlayer == p1.symbol) ? &p1 : &p2;
        gameName = loadedState->name;
        player1Symbol = loadedState->player1Symbol;
        cout << "\n✅ Partida cargada: " << gameName << "\n";
    } else {
        cout << "\n=== Tres en raya con colores ===\n";
        cout << Color::rojo("X = Jugador 1") << " | " << Color::azul("O = Jugador 2") << "\n\n";
        
        cout << "Ingresa un nombre para esta partida: ";
        getline(cin, gameName);
        
        int starter = chooseWhoStarts();
        
        if (starter == 1) {
            p1.symbol = 'X';
            p2.symbol = 'O';
            current = &p1;
            player1Symbol = 'X';
        } else {
            p1.symbol = 'O';
            p2.symbol = 'X';
            current = &p2;
            player1Symbol = 'O';
        }
    }

    bool gameInProgress = true;
    while (gameInProgress) {
        printBoard(board);
        cout << "Turno de " << current->name << " (" << current->symbol << ").\n";
        cout << "(Escribe 'guardar' para guardar la partida)\n";

        string input;
        cout << current->name << " (" << current->symbol << ") elige una casilla (1-9): ";
        cin >> input;

        if (input == "guardar" || input == "GUARDAR") {
            GameState state;
            state.board = board;
            state.currentPlayer = current->symbol;
            state.p1Symbol = p1.symbol;
            state.p2Symbol = p2.symbol;
            state.player1Symbol = player1Symbol;
            state.name = gameName;
            saveGame(state);
            cin.ignore(1000, '\n');
            cout << "Presiona ENTER para volver al menú...";
            cin.get();
            return;
        }

        int move;
        try {
            move = stoi(input);
        } catch (...) {
            cout << "Entrada inválida. Por favor ingresa un número del 1 al 9.\n";
            continue;
        }

        if (move >= 1 && move <= 9 && board[move - 1] == ' ') {
            board[move - 1] = current->symbol;

            if (checkWin(board, current->symbol)) {
                printBoard(board);
                cout << "🎉 " << current->name << " gana!\n";
                
                if (current->symbol == player1Symbol) {
                    score.player1Wins++;
                } else {
                    score.player2Wins++;
                }
                saveScores(score);
                gameInProgress = false;
            }
            else if (boardFull(board)) {
                printBoard(board);
                cout << "🤝 Empate!\n";
                score.draws++;
                saveScores(score);
                gameInProgress = false;
            }
            else {
                current = (current == &p1) ? &p2 : &p1;
            }
        } else {
            cout << "Movimiento inválido. Intenta de nuevo.\n";
        }
    }

    cout << "\nPresiona ENTER para volver al menú...";
    cin.ignore(1000, '\n');
    cin.get();
}

void loadGame() {
    vector<GameState> games = loadSavedGames();
    
    if (games.empty()) {
        cout << "\n📁 No hay partidas guardadas.\n";
        cout << "Presiona ENTER para continuar...";
        cin.get();
        return;
    }
    
    showSavedGames();
    
    cout << "Ingresa el número de la partida a cargar (0 para cancelar): ";
    int num;
    cin >> num;
    cin.ignore(1000, '\n');
    
    if (num > 0 && num <= games.size()) {
        GameState state = games[num - 1];
        deleteSavedGame(num - 1);
        playGame(&state);
    }
}

int main() {
    while (true) {
        int option = showMainMenu();
        
        if (option == 1) {
            playGame();
        }
        else if (option == 2) {
            loadGame();
        }
        else if (option == 3) {
            manageSavedGames();
        }
        else if (option == 4) {
            showScores();
        }
        else if (option == 5) {
            showInstructions();
        }
        else if (option == 6) {
            cout << "\n¡Hasta pronto! 👋\n";
            break;
        }
    }
    
    return 0;
}
