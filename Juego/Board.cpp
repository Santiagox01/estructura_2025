#include "Board.h"
#include "Color.h"
#include <iostream>

using namespace std;

Board::Board() : cells(9, ' ') {}

void Board::reset() {
    fill(cells.begin(), cells.end(), ' ');
}

bool Board::makeMove(int position, char symbol) {
    if (isValidMove(position)) {
        cells[position] = symbol;
        return true;
    }
    return false;
}

bool Board::isValidMove(int position) const {
    return position >= 0 && position < 9 && cells[position] == ' ';
}

bool Board::checkWin(char symbol) const {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for (auto &w : wins) {
        if (cells[w[0]] == symbol && cells[w[1]] == symbol && cells[w[2]] == symbol)
            return true;
    }
    return false;
}

bool Board::isFull() const {
    for (char c : cells) {
        if (c == ' ') return false;
    }
    return true;
}

void Board::print() const {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        string cell;
        if (cells[i] == 'X') {
            cell = Color::rojo("X");
        } else if (cells[i] == 'O') {
            cell = Color::azul("O");
        } else {
            cell = string(1, '1' + i);
        }

        cout << cell;
        if (i % 3 != 2) cout << " | ";
        if (i % 3 == 2 && i < 8) cout << "\n---------\n";
    }
    cout << "\n\n";
}

vector<char> Board::getState() const {
    return cells;
}

void Board::setState(const vector<char>& state) {
    if (state.size() == 9) {
        cells = state;
    }
}
