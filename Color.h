#ifndef COLOR_H
#define COLOR_H
#include <string>
using std::string;

class Color {
public:
    static string rojo(const string& txt) { return "\033[31m" + txt + "\033[0m"; }
    static string azul(const string& txt) { return "\033[34m" + txt + "\033[0m"; }
    static string reset() { return "\033[0m"; }
};