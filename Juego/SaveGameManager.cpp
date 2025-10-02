#include "SaveGameManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

SaveGameManager::SaveGameManager(const string& filename) : filename(filename) {}

vector<GameState> SaveGameManager::loadAll() {
    vector<GameState> games;
    ifstream file(filename);
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

void SaveGameManager::saveAll(const vector<GameState>& games) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& state : games) {
            file << state.name << "|";
            for (char c : state.board) {
                file << c;
            }
            file << "|" << state.currentPlayer << "|" << state.p1Symbol << "|" 
                 << state.p2Symbol << "|" << state.player1Symbol << "\n";
        }
        file.close();
    }
}

bool SaveGameManager::save(const GameState& state) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << state.name << "|";
        for (char c : state.board) {
            file << c;
        }
        file << "|" << state.currentPlayer << "|" << state.p1Symbol << "|" 
             << state.p2Symbol << "|" << state.player1Symbol << "\n";
        file.close();
        cout << "\n✅ Partida guardada exitosamente!\n";
        return true;
    }
    cout << "\n❌ Error al guardar la partida.\n";
    return false;
}

bool SaveGameManager::update(const GameState& state) {
    vector<GameState> games = loadAll();
    bool found = false;
    
    for (size_t i = 0; i < games.size(); i++) {
        if (games[i].name == state.name) {
            games[i] = state;
            found = true;
            break;
        }
    }
    
    if (found) {
        saveAll(games);
        cout << "\n✅ Partida actualizada exitosamente!\n";
        return true;
    } else {
        return save(state);
    }
}

void SaveGameManager::list() const {
    vector<GameState> games = const_cast<SaveGameManager*>(this)->loadAll();
    
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

bool SaveGameManager::load(int index, GameState& state) {
    vector<GameState> games = loadAll();
    
    if (index >= 0 && index < games.size()) {
        state = games[index];
        return true;
    }
    return false;
}

bool SaveGameManager::deleteGame(int index) {
    vector<GameState> games = loadAll();
    
    if (index >= 0 && index < games.size()) {
        games.erase(games.begin() + index);
        saveAll(games);
        cout << "\n✅ Partida eliminada exitosamente!\n";
        return true;
    }
    return false;
}

bool SaveGameManager::deleteByName(const string& name) {
    vector<GameState> games = loadAll();
    
    for (size_t i = 0; i < games.size(); i++) {
        if (games[i].name == name) {
            games.erase(games.begin() + i);
            saveAll(games);
            return true;
        }
    }
    return false;
}

void SaveGameManager::manage() {
    vector<GameState> games = loadAll();
    
    if (games.empty()) {
        cout << "\n📁 No hay partidas guardadas.\n";
        cout << "Presiona ENTER para continuar...";
        cin.get();
        return;
    }
    
    list();
    
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
            deleteGame(num - 1);
        }
    }
    
    cout << "Presiona ENTER para continuar...";
    cin.get();
}

int SaveGameManager::getGameCount() const {
    return const_cast<SaveGameManager*>(this)->loadAll().size();
}
