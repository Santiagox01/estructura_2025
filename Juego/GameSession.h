#ifndef GAMESESSION_H
#define GAMESESSION_H

#include "Board.h"
#include "Player.h"
#include "ScoreManager.h"
#include "SaveGameManager.h"
#include <string>

using std::string;

class GameSession {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;
    ScoreManager& scoreManager;
    SaveGameManager& saveManager;
    string gameName;
    char player1Symbol;
    
    int chooseStartingPlayer();
    void handleGameEnd(bool isWin, bool isDraw);
    
public:
    GameSession(ScoreManager& sm, SaveGameManager& sgm);
    
    void playNew();
    void playFromSaved(const GameState& savedState);
};

#endif
