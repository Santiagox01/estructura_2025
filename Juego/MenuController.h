#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "ScoreManager.h"
#include "SaveGameManager.h"
#include "GameSession.h"

class MenuController {
private:
    ScoreManager& scoreManager;
    SaveGameManager& saveManager;
    
    int showMainMenu();
    void showInstructions();
    void handleNewGame();
    void handleLoadGame();
    
public:
    MenuController(ScoreManager& sm, SaveGameManager& sgm);
    
    void run();
};

#endif
