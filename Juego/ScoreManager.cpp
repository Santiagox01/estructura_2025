#include "ScoreManager.h"
#include "Color.h"
#include <iostream>
#include <fstream>

using namespace std;

ScoreManager::ScoreManager(const string& filename) : filename(filename) {
    load();
}

void ScoreManager::load() {
    ifstream file(filename);
    if (file.is_open()) {
        file >> currentScore.player1Wins >> currentScore.player2Wins >> currentScore.draws;
        file.close();
    }
}

void ScoreManager::save() {
    ofstream file(filename);
    if (file.is_open()) {
        file << currentScore.player1Wins << " " << currentScore.player2Wins << " " << currentScore.draws;
        file.close();
    }
}

void ScoreManager::display() const {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║         📊 TABLA DE PUNTUACIONES       ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << Color::rojo("  Jugador 1 (X)") << ": " << currentScore.player1Wins << " victorias\n";
    cout << Color::azul("  Jugador 2 (O)") << ": " << currentScore.player2Wins << " victorias\n";
    cout << "  Empates: " << currentScore.draws << "\n\n";
    cout << "Presiona ENTER para continuar...";
    cin.get();
}

void ScoreManager::incrementPlayer1Wins() {
    currentScore.player1Wins++;
    save();
}

void ScoreManager::incrementPlayer2Wins() {
    currentScore.player2Wins++;
    save();
}

void ScoreManager::incrementDraws() {
    currentScore.draws++;
    save();
}

Score ScoreManager::getScore() const {
    return currentScore;
}
