#pragma once

#include <iostream>
#include <string>

enum Color {
    Black,
    White
};

void displayBoard();

Color promptForColor();