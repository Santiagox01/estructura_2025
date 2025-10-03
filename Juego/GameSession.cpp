#include "GameSession.h"
#include "Color.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

GameSession::GameSession(ScoreManager& sm, SaveGameManager& sgm)
    : player1('X', "Jugador 1"), 
      player2('O', "Jugador 2"),
      currentPlayer(&player1),
      scoreManager(sm),
      saveManager(sgm),
      player1Symbol('X') {}

int GameSession::chooseStartingPlayer() {
    cout << "\n¿Quién debe comenzar?\n";
    cout << "  1. Jugador 1\n";
    cout << "  2. Jugador 2\n";
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
            cout << "Jugador 1 comienza!\n";
        } else {
            cout << "Jugador 2 comienza!\n";
        }
        cout << "Presiona ENTER para continuar...";
        cin.get();
    }
    
    return choice;
}

void GameSession::handleGameEnd(bool isWin, bool isDraw) {
    if (isWin) {
        cout << "🎉 " << currentPlayer->name << " gana!\n";
        if (currentPlayer->symbol == player1Symbol) {
            scoreManager.incrementPlayer1Wins();
        } else {
            scoreManager.incrementPlayer2Wins();
        }
    } else if (isDraw) {
        cout << "🤝 Empate!\n";
        scoreManager.incrementDraws();
    }
}

void GameSession::playNew() {
    cout << "\n=== Tres en raya ===\n";
    cout << "Jugador 1 | Jugador 2\n\n";
    
    cout << "Ingresa un nombre para esta partida: ";
    getline(cin, gameName);
    
    int starter = chooseStartingPlayer();
    
    if (starter == 1) {
        player1.symbol = 'X';
        player2.symbol = 'O';
        player1Symbol = 'X';
    } else {
        player1.symbol = 'O';
        player2.symbol = 'X';
        player1Symbol = 'O';
    }
    
    bool continuePlaying = true;
    
    while (continuePlaying) {
        board.reset();
        
        if (starter == 1) {
            currentPlayer = &player1;
        } else {
            currentPlayer = &player2;
        }
        
        bool gameInProgress = true;
        while (gameInProgress) {
            board.print();
            cout << "Turno de " << currentPlayer->name << ".\n";
            cout << "(Escribe 'guardar' para guardar la partida)\n";

            string input;
            cout << currentPlayer->name << " elige una casilla (1-9): ";
            cin >> input;

            if (input == "guardar" || input == "GUARDAR") {
                GameState state;
                state.board = board.getState();
                state.currentPlayer = currentPlayer->symbol;
                state.p1Symbol = player1.symbol;
                state.p2Symbol = player2.symbol;
                state.player1Symbol = player1Symbol;
                state.name = gameName;
                saveManager.update(state);
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

            if (board.makeMove(move - 1, currentPlayer->symbol)) {
                if (board.checkWin(currentPlayer->symbol)) {
                    board.print();
                    handleGameEnd(true, false);
                    gameInProgress = false;
                } else if (board.isFull()) {
                    board.print();
                    handleGameEnd(false, true);
                    gameInProgress = false;
                } else {
                    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
                }
            } else {
                cout << "Movimiento inválido. Intenta de nuevo.\n";
            }
        }
        
        Score currentScore = scoreManager.getScore();
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║         📊 PUNTUACIONES ACTUALES       ║\n";
        cout << "╚════════════════════════════════════════╝\n\n";
        cout << "  Jugador 1: " << currentScore.player1Wins << " victorias\n";
        cout << "  Jugador 2: " << currentScore.player2Wins << " victorias\n";
        cout << "  Empates: " << currentScore.draws << "\n\n";
        
        cout << "¿Deseas continuar jugando? (s/n): ";
        char response;
        cin >> response;
        cin.ignore(1000, '\n');
        
        if (response == 'n' || response == 'N') {
            continuePlaying = false;
            
            cout << "¿Deseas guardar la partida? (s/n): ";
            char saveResponse;
            cin >> saveResponse;
            cin.ignore(1000, '\n');
            
            if (saveResponse == 's' || saveResponse == 'S') {
                GameState state;
                state.board = board.getState();
                state.currentPlayer = currentPlayer->symbol;
                state.p1Symbol = player1.symbol;
                state.p2Symbol = player2.symbol;
                state.player1Symbol = player1Symbol;
                state.name = gameName;
                saveManager.update(state);
            }
        }
    }
    
    cout << "\nPresiona ENTER para volver al menú...";
    cin.get();
}

void GameSession::playFromSaved(const GameState& savedState) {
    board.setState(savedState.board);
    player1.symbol = savedState.p1Symbol;
    player2.symbol = savedState.p2Symbol;
    currentPlayer = (savedState.currentPlayer == player1.symbol) ? &player1 : &player2;
    gameName = savedState.name;
    player1Symbol = savedState.player1Symbol;
    
    cout << "\n✅ Partida cargada: " << gameName << "\n";
    
    bool gameInProgress = true;
    while (gameInProgress) {
        board.print();
        cout << "Turno de " << currentPlayer->name << ".\n";
        cout << "(Escribe 'guardar' para guardar la partida)\n";

        string input;
        cout << currentPlayer->name << " elige una casilla (1-9): ";
        cin >> input;

        if (input == "guardar" || input == "GUARDAR") {
            GameState state;
            state.board = board.getState();
            state.currentPlayer = currentPlayer->symbol;
            state.p1Symbol = player1.symbol;
            state.p2Symbol = player2.symbol;
            state.player1Symbol = player1Symbol;
            state.name = gameName;
            saveManager.update(state);
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

        if (board.makeMove(move - 1, currentPlayer->symbol)) {
            if (board.checkWin(currentPlayer->symbol)) {
                board.print();
                handleGameEnd(true, false);
                gameInProgress = false;
            } else if (board.isFull()) {
                board.print();
                handleGameEnd(false, true);
                gameInProgress = false;
            } else {
                currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            }
        } else {
            cout << "Movimiento inválido. Intenta de nuevo.\n";
        }
    }

    cout << "\nPresiona ENTER para volver al menú...";
    cin.ignore(1000, '\n');
    cin.get();
}
