#include "MenuController.h"
#include "ScoreManager.h"
#include "SaveGameManager.h"

int main() {
    ScoreManager scoreManager;
    SaveGameManager saveManager;
    MenuController menu(scoreManager, saveManager);
    
    menu.run();
    
    return 0;
}
