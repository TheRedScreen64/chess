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