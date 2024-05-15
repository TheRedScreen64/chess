#pragma once
#include <string>
#include <iostream>

using namespace std;

struct Vector2D {
    int x;
    int y;
};

struct Move {
    Vector2D from;
    Vector2D to;
};

enum class Color {
    Black = 0,
    White = 1
};

void displayBoard(char[][8], int, int, Color, string);
bool ownsPiece(char board[][8], Vector2D pos, Color color);
Color selectColor();
Color promptForColor();
Move promptForMove(int);
string doMove(char board[][8], Color color, int sizeX, Move move);
string isMoveValid(char board[][8], Color color, Move move);

bool isStraight(Move move);
bool isDiagonal(Move move);
bool isLShape(Move move);
bool isStraightDirectional(Move move, Color color);