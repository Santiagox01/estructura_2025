#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class Board {
private:
    vector<char> cells;
    
public:
    Board();
    
    void reset();
    bool makeMove(int position, char symbol);
    bool isValidMove(int position) const;
    bool checkWin(char symbol) const;
    bool isFull() const;
    void print() const;
    
    vector<char> getState() const;
    void setState(const vector<char>& state);
};

#endif
