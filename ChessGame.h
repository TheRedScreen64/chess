#pragma once
#include <string>
#include <iostream>
#include <tuple>

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
    Undefined = 0,
    Black = 1,
    White = 2
};

void displayStats(char beatenPiecesBlack[16], char beatenPiecesWhite[16]);
void displayBoard(char[][8], int, int, Color, string);

Color selectColor();
Color promptForColor();
char promptForPiece();
Move promptForMove(int, bool*);

void doMove(char board[][8], Move move);
void checkConvertPawn(char board[][8], Move move, Color color);
void convertPawn(char board[][8], Vector2D pos, Color color);

bool ownsPiece(char board[][8], Vector2D pos, Color color);
bool isMoveValid(char board[][8], Color color, Move move, string*);
bool isBeat(char board[][8], Move move);
bool isValidBeat(char board[][8], Move move, Color color, string*);
bool isKingNearby(char board[][8], Move move, Color color);
bool isPieceOnSquare(char board[][8], Vector2D square);

Direction2D getDirection2D(Move move);
Direction getDirection(Move move);

bool isStraight(Move move);
bool isDiagonal(Move move);
bool isDiagonalPawn(Move move, Color color);
bool isLShape(Move move);
bool isPawnMove(Move move, Color color);

bool isBishopPathBlocked(char board[][8], Move move);
bool isRookPathBlocked(char board[][8], Move move);
bool isQueenPathBlocked(char board[][8], Move move);

// SaveGame.cpp
bool saveFileExists();
void askSaveGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color color);
void askLoadGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color* color);
void saveGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color color);
void loadGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color *color);