#ifndef SAVEGAMEMANAGER_H
#define SAVEGAMEMANAGER_H

#include <vector>
#include <string>
using std::vector;
using std::string;

struct GameState {
    vector<char> board;
    char currentPlayer;
    char p1Symbol;
    char p2Symbol;
    char player1Symbol;
    string name;
};

class SaveGameManager {
private:
    string filename;
    
    vector<GameState> loadAll();
    void saveAll(const vector<GameState>& games);
    
public:
    SaveGameManager(const string& filename = "partidas_guardadas.txt");
    
    bool save(const GameState& state);
    bool update(const GameState& state);
    void list() const;
    bool load(int index, GameState& state);
    bool deleteGame(int index);
    bool deleteByName(const string& name);
    void manage();
    int getGameCount() const;
};

#endif
