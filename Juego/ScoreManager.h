#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>
using std::string;

struct Score {
    int player1Wins = 0;
    int player2Wins = 0;
    int draws = 0;
};

class ScoreManager {
private:
    string filename;
    Score currentScore;
    
public:
    ScoreManager(const string& filename = "scores.txt");
    
    void load();
    void save();
    void display() const;
    
    void incrementPlayer1Wins();
    void incrementPlayer2Wins();
    void incrementDraws();
    
    Score getScore() const;
};

#endif
