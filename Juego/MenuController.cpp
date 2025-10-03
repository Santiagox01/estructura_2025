#include "MenuController.h"
#include "Color.h"
#include <iostream>

using namespace std;

MenuController::MenuController(ScoreManager& sm, SaveGameManager& sgm)
    : scoreManager(sm), saveManager(sgm) {}

int MenuController::showMainMenu() {
    int option;
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║       🎮 TRES EN RAYA - MENÚ 🎮       ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << "  1️⃣  Nueva Partida\n";
    cout << "  2️⃣  Cargar Partida Guardada\n";
    cout << "  3️⃣  Gestionar Partidas Guardadas\n";
    cout << "  4️⃣  Instrucciones\n";
    cout << "  5️⃣  Salir\n\n";
    cout << "Selecciona una opción: ";
    
    while (!(cin >> option) || option < 1 || option > 5) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opción inválida. Por favor elige entre 1 y 5: ";
    }
    cin.ignore(1000, '\n');
    return option;
}

void MenuController::showInstructions() {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      INSTRUCCIONES - TRES EN RAYA     ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << "🎯 OBJETIVO:\n";
    cout << "   Alinea tres símbolos en horizontal, vertical o diagonal\n\n";
    cout << "🎮 CÓMO JUGAR:\n";
    cout << "   1. Elige quién comienza la partida\n";
    cout << "   2. Los jugadores se turnan para elegir casillas\n";
    cout << "   3. Ingresa un número del 1 al 9 según el tablero:\n\n";
    cout << "      1 | 2 | 3\n";
    cout << "      ---------\n";
    cout << "      4 | 5 | 6\n";
    cout << "      ---------\n";
    cout << "      7 | 8 | 9\n\n";
    cout << "   4. Durante el juego puedes escribir 'guardar' para guardar la partida\n\n";
    cout << "🎨 SÍMBOLOS:\n";
    cout << "   " << Color::rojo("X") << " = Jugador 1 (Rojo)\n";
    cout << "   " << Color::azul("O") << " = Jugador 2 (Azul)\n\n";
    cout << "Presiona ENTER para continuar...";
    cin.get();
}

void MenuController::handleNewGame() {
    GameSession session(scoreManager, saveManager);
    session.playNew();
}

void MenuController::handleLoadGame() {
    if (saveManager.getGameCount() == 0) {
        cout << "\n📁 No hay partidas guardadas.\n";
        cout << "Presiona ENTER para continuar...";
        cin.get();
        return;
    }
    
    saveManager.list();
    
    cout << "Ingresa el número de la partida a cargar (0 para cancelar): ";
    int num;
    cin >> num;
    cin.ignore(1000, '\n');
    
    if (num > 0 && num <= saveManager.getGameCount()) {
        GameState state;
        if (saveManager.load(num - 1, state)) {
            GameSession session(scoreManager, saveManager);
            session.playFromSaved(state);
        }
    }
}

void MenuController::run() {
    while (true) {
        int option = showMainMenu();
        
        if (option == 1) {
            handleNewGame();
        }
        else if (option == 2) {
            handleLoadGame();
        }
        else if (option == 3) {
            saveManager.manage();
        }
        else if (option == 4) {
            showInstructions();
        }
        else if (option == 5) {
            cout << "\n¡Hasta pronto! 👋\n";
            break;
        }
    }
}
