#pragma once
#include <string>
#include <iostream>

using namespace std;

struct Status {
    bool status;
    string msg;
};

struct Vector2D {
    int x;
    int y;
};

struct Move {
    Vector2D from;
    Vector2D to;
};

enum class Direction {
    Undefined = 0,
    Up = 1,
    Down = 2,
    Left = 3,
    Right = 4
};

struct Direction2D {
    int x;
    int y;
};

enum class Color {
    Black = 0,
    White = 1
};

void displayStats(char beatenPiecesBlack[16], char beatenPiecesWhite[16]);
void displayBoard(char[][8], int, int, Color, string);
bool ownsPiece(char board[][8], Vector2D pos, Color color);
Color selectColor();
Color promptForColor();
Move promptForMove(int);
string doMove(char board[][8], Color color, int sizeX, Move move);
string isMoveValid(char board[][8], Color color, Move move);
Status checkBeatPiece(char board[][8], Move move, Color color);

bool isPieceOnSquare(char board[][8], Vector2D square);

Direction2D getDirection2D(Move move);
Direction getDirection(Move move);

bool isStraight(Move move);
bool isDiagonal(Move move);
bool isDiagonalPawn(Move move, Color color);
bool isLShape(Move move);
bool isStraightDirectional(Move move, Color color);

bool isBishopPathBlocked(char board[][8], Move move);
bool isRookPathBlocked(char board[][8], Move move);
bool isQueenPathBlocked(char board[][8], Move move);