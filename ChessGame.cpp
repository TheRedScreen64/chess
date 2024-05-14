#include "ChessGame.h"

using namespace std;

int main()
{
    static char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };

    Color color = selectColor();

    string test;
    bool running = true;
    while (running) {
        displayBoard(board, 8, 8);
        // for now
        running = false;
    }
}

void displayBoard(char board[][8], int sizeX, int sizeY) {
    system("cls");
    cout << "\33[93m";
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    cout << "\33[47m";
                }
                else {
                    cout << "\33[40m";
                }
            }
            else {
                if (x % 2 == 0) {
                    cout << "\33[40m";
                }
                else {
                    cout << "\33[47m";
                }
            }
            
            cout << " " << board[y][x] << " ";
        }
        cout << endl;
    }
    cout << "\33[0m";
}

Color selectColor() {
    Color color;
    bool colorSelected = false;
    while (!colorSelected) {
        color = promptForColor();
        if (color != White && color != Black) {
            system("cls");
            continue;
        }
        colorSelected = true;
    }
    system("cls");
    return color;
}

Color promptForColor() {
    Color color;
    int tempNumber;
    cout << "Which color do you want to play? (Black 0, White 1)";
    cin >> tempNumber;
    color = (Color)tempNumber;
    return color;
}