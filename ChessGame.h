#pragma once

#include <iostream>
#include <string>

enum Color {
    Black,
    White
};

void displayBoard(char[][8], int, int);
Color selectColor();
Color promptForColor();