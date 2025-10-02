#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

class Player {
public:
    char symbol;
    string name;

    Player(char s, const string& n);

    int makeMove(const vector<char>& board);
};

#endif 
s