#include "ChessGame.h"

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
    };;

    static char beatenPiecesBlack[16];
    int lastInsertBlack = -1;
    static char beatenPiecesWhite[16];
    int lastInsertWhite = -1;

    Color color = Color::Undefined;

    askLoadGame(board, beatenPiecesBlack, beatenPiecesWhite, &color);
    
    if (color == Color::Undefined) {
        color = selectColor();
    }

    string errMessage = "";
    string winner = "";
    bool patt = false;
    bool running = true;

    while (running) {
        displayBoard(board, 8, 8, color, errMessage);
        displayStats(beatenPiecesBlack, beatenPiecesWhite);
        errMessage = "";

        bool exit = false;
        Move move = promptForMove(8, &exit);
        if (exit) {
            askSaveGame(board, beatenPiecesBlack, beatenPiecesWhite, color);
            return 0;
        }

        if (!isMoveValid(board, color, move, &errMessage)) {
            continue;
        }

        if (isBeat(board, move) && isValidBeat(board, move, color, &errMessage)) {
            string colorAsString = color == Color::Black ? "Black" : "White";
            char piece = board[move.to.y - 1][move.to.x - 1];

            if (piece == 'k' || piece == 'K') {
                winner = colorAsString;
                break;
            }

            if (color == Color::Black) {
                beatenPiecesWhite[lastInsertWhite + 1] = piece;
                lastInsertWhite++;
            }
            else {
                beatenPiecesBlack[lastInsertBlack + 1] = piece;
                lastInsertBlack++;
            }

            if (lastInsertBlack >= 14 && lastInsertWhite >= 14) {
                patt = true;
                break;
            }
        }

        if (errMessage == "") {
            doMove(board, move);
            color = color == Color::Black ? Color::White : Color::Black;
        }
    }

    system("cls");

    if (patt) {
        cout << "Patt!\n";
    }
    else {
        cout << winner << " has won!\n";
    }
}

void displayStats(char beatenPiecesBlack[16], char beatenPiecesWhite[16]) {
    cout << "Beaten pieces: (Black) " << beatenPiecesBlack << ", (White) " << beatenPiecesWhite << endl;
    cout << endl;
}

void displayBoard(char board[][8], int sizeX, int sizeY, Color currentColor, string message) {
    system("cls");

    string colorAsString = currentColor == Color::Black ? "Black" : "White";
    cout << "\nIt is " << colorAsString << "'s turn\n";
    cout << endl;

    if (message.length() > 0) {
        cout << message << endl;
        cout << endl;
    }

    cout << "   ";
    for (int x = 0; x < sizeX; x++) {
        cout << " " << x + 1 << " ";
    }
    cout << endl;
    for (int y = 0; y < sizeY; y++) {
        cout << "\33[0m " << y + 1 << " ";
        for (int x = 0; x < sizeX; x++) {
            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    cout << "\33[30m\33[47m";
                }
                else {
                    cout << "\33[97m\33[40m";
                }
            }
            else {
                if (x % 2 == 0) {
                    cout << "\33[97m\33[40m";
                }
                else {
                    cout << "\33[30m\33[47m";
                }
            }
            
            cout << " " << board[y][x] << " ";
        }
        cout << endl;
    }
    cout << "\33[0m\n";
}


Color selectColor() {
    Color color;
    bool colorSelected = false;
    while (!colorSelected) {
        color = promptForColor();
        if (color != Color::White && color != Color::Black) {
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
    cout << "Which color do you want to play? (Black 1, White 2): ";
    cin >> tempNumber;
    color = (Color)tempNumber;
    return color;
}

char promptForPiece() {
    char piece;
    string input;
    cout << "Which piece do you want your pawn to become? (q,r,b,n)";
    cin >> input;
    piece = input[0];
    return piece;
}

Move promptForMove(int maxCoord, bool *exit) {
    Vector2D fromPos;
    Vector2D toPos;
    bool moveValid = false;
    while (!moveValid) {
        string input;
        cout << "What is your next move? fromX,fromY,toX,toY or exit: ";
        cin >> input;

        if (input == "exit") {
            *exit = true;
            return {};
        }

        fromPos.x = stoi(input.substr(0, input.find(",", 0)));
        input = input.substr(input.find(",", 0) + 1, input.length());

        fromPos.y = stoi(input.substr(0, input.find(",", 0)));
        input = input.substr(input.find(",", 0) + 1, input.length());

        toPos.x = stoi(input.substr(0, input.find(",", 0)));
        input = input.substr(input.find(",", 0) + 1, input.length());

        toPos.y = stoi(input.substr(0, input.find(",", 0)));
        input = input.substr(input.find(",", 0) + 1, input.length());

        if (fromPos.x < 1 || fromPos.x > maxCoord || fromPos.y < 1 || fromPos.y > maxCoord) {
            system("cls");
            cout << "From value must be in the range (1," << maxCoord << ")\n";
            continue;
        }
        if (toPos.x < 1 || toPos.x > maxCoord || toPos.y < 1 || toPos.y > maxCoord) {
            system("cls");
            cout << "To value must be in the range (1," << maxCoord << ")\n";
            continue;
        }

        // TODO: Add checks

        moveValid = true;
    }

    return { fromPos, toPos };
}


void doMove(char board[][8], Move move) {
    char piece = board[move.from.y - 1][move.from.x - 1];
    board[move.from.y - 1][move.from.x - 1] = ' ';
    board[move.to.y - 1][move.to.x - 1] = piece;
}

void convertPawn(char board[][8], Vector2D pos, Color color) {
    if (pos.y != 1 && pos.y != 8) return;

    system("cls");
    char piece;
    bool pieceSelected = false;
    while (!pieceSelected) {
        piece = promptForPiece();
        if (piece != 'q' && piece != 'r' && piece != 'b' && piece != 'n') {
            system("cls");
            continue;
        }
        pieceSelected = true;
    }
    system("cls");

    piece = color == Color::Black ? piece : toupper(piece);

    board[pos.y - 1][pos.x - 1] = piece;
}


bool ownsPiece(char board[][8], Vector2D pos, Color color) {
    if (islower(board[pos.y - 1][pos.x - 1]) && color == Color::Black) {
        return true;
    }
    else if (isupper(board[pos.y - 1][pos.x - 1]) && color == Color::White) {
        return true;
    }
    else {
        return false;
    }
}

bool isMoveValid(char board[][8], Color color, Move move, string *errMessage) {
    if (board[move.from.y - 1][move.from.x - 1] == ' ') {
        *errMessage = "There's no piece at that location.";
        return false;
    }

    if (!ownsPiece(board, move.from, color)) {
        *errMessage = "You don't own that piece.";
        return false;
    }

    if (move.from.x == move.to.x && move.from.y == move.to.y) {
        *errMessage = "Come on, I can't see the difference there.";
        return false;
    }
    
    switch (tolower(board[move.from.y - 1][move.from.x - 1])) {
    case 'p':
        if (isPawnMove(move, color)) {
            if (isPieceOnSquare(board, move.to)) {
                *errMessage = "Target pos is already occupied";
                return false;
            }
        } else if (!(isDiagonalPawn(move, color) && isPieceOnSquare(board, move.to) && !ownsPiece(board, move.to, color))) {
            // TODO: ugly if statement
            *errMessage = "Move is not permitted";
            return false;
        }
        if (color == Color::Black && move.to.y == 8) {
            convertPawn(board, move.to, color);
            board[move.from.y - 1][move.from.x - 1] = ' ';
            return false;
        }
        else if (color == Color::White && move.to.y == 1) {
            convertPawn(board, move.to, color);
            board[move.from.y - 1][move.from.x - 1] = ' ';
            return false;
        }
        break;
    case 'r':
        if (!isStraight(move)) {
            *errMessage = "Move is not straight";
            return false;
        }
        if (isRookPathBlocked(board, move)) {
            *errMessage = "Move is blocked";
            return false;
        }
        break;
    case 'n':
        if (!isLShape(move)) {
            *errMessage = "Move is not L shape";
            return false;
        }
        break;
    case 'b':
        if (!isDiagonal(move)) {
            *errMessage = "Move is not diagonal";
            return false;
        }
        if (isBishopPathBlocked(board, move)) {
            *errMessage = "Move is blocked";
            return false;
        }
        break;
    case 'q':
        if (!(isDiagonal(move) || isStraight(move))) {
            *errMessage = "Move is not diagonal or straight";
            return false;
        }
        if (isQueenPathBlocked(board, move)) {
            *errMessage = "Move is blocked";
            return false;
        }
        break;
    case 'k':
        if (abs(move.to.x - move.from.x) > 1 || abs(move.to.y - move.from.y) > 1) {
            *errMessage = "Move is to far";
            return false;
        }
        if (isKingNearby(board, move, color)) {
            *errMessage = "Opponents king is nearby";
            return false;
        }
        break;
    default:
        *errMessage = "Not a valid piece type.";
        return false;
    }

    return true;
}

bool isKingNearby(char board[][8], Move move, Color color) {
    Vector2D nearbySquares[8] = {
        { move.to.x - 1, move.to.y },
        { move.to.x + 1, move.to.y },
        { move.to.x, move.to.y - 1 },
        { move.to.x, move.to.y + 1 },
        { move.to.x - 1, move.to.y - 1 },
        { move.to.x - 1, move.to.y + 1 },
        { move.to.x + 1, move.to.y - 1 },
        { move.to.x + 1, move.to.y + 1 }
    };

    char kingPiece = color == Color::Black ? 'K' : 'k';

    for (int i = 0; i < 8; i++) {
        if (nearbySquares[i].x > -1 && nearbySquares[i].x < 8 && nearbySquares[i].y > -1 && nearbySquares[i].y < 8) {
            cout << board[nearbySquares[i].y - 1][nearbySquares[i].x - 1];
            if (board[nearbySquares[i].y - 1][nearbySquares[i].x - 1] == kingPiece) {
                return true;
            }
        }
    }
    return false;
}

bool isBeat(char board[][8], Move move) {
    if (board[move.to.y - 1][move.to.x - 1] != ' ') {
        return true;
    }
    return false;
}

bool isValidBeat(char board[][8], Move move, Color color, string *errMessage) {
    if (ownsPiece(board, move.to, color)) {
        *errMessage = "You can't beat your own piece";
        return false;
    }
    else {
        return true;
    }
}

bool isPieceOnSquare(char board[][8], Vector2D square) {
    if (board[square.y - 1][square.x - 1] != ' ') {
        return true;
    }
    return false;
}

bool isStraight(Move move) {
    if (move.from.x == move.to.x) {
        return true;
    }
    if (move.from.y == move.to.y) {
        return true;
    }
    return false;
}

bool isDiagonal(Move move) {
    if (abs(move.to.x - move.from.x) == abs(move.to.y - move.from.y)){
        return true;
    }
    return false;
}

bool isDiagonalPawn(Move move, Color color) {
    if (abs(move.from.x - move.to.x) != 1) {
        return false;
    }
    if (color == Color::Black && move.from.y - move.to.y == -1) {
        return true;
    }
    if (color == Color::White && move.from.y - move.to.y == 1) {
        return true;
    }
    return false;
}

bool isLShape(Move move) {
    if (abs(move.from.x - move.to.x) == 2 && abs(move.from.y - move.to.y) == 1) {
        return true;
    }
    if (abs(move.from.x - move.to.x) == 1 && abs(move.from.y - move.to.y) == 2) {
        return true;
    }
    return false;
}

bool isPawnMove(Move move, Color color) {
    if (move.from.x != move.to.x) {
        return false;
    }
    if (color == Color::Black && move.from.y == 2 && (move.from.y - move.to.y == -1 || move.from.y - move.to.y == -2)) {
        return true;
    }
    if (color == Color::White && move.from.y == 7 && (move.from.y - move.to.y == 1 || move.from.y - move.to.y == 2)) {
        return true;
    }
    if (color == Color::Black && move.from.y - move.to.y == -1) {
        return true;
    }
    if (color == Color::White && move.from.y - move.to.y == 1) {
        return true;
    }
    
    return false;
}


Direction2D getDirection2D(Move move) {
    int dirX = move.to.x > move.from.x ? 1 : -1;
    int dirY = move.to.y > move.from.y ? 1 : -1;

    return { dirX, dirY };
}

Direction getDirection(Move move) {
    if (move.to.x > move.from.x && move.to.y == move.from.y) {
        return Direction::Right;
    }
    else if (move.to.x < move.from.x && move.to.y == move.from.y) {
        return Direction::Left;
    }
    else if (move.to.y > move.from.y && move.to.x == move.from.x) {
        return Direction::Down;
    }
    else if (move.to.y < move.from.y && move.to.x == move.from.x) {
        return Direction::Up;
    }
    else {
        return Direction::Undefined;
    }
}

bool isRookPathBlocked(char board[][8], Move move) {
    switch (getDirection(move))
    {
    case Direction::Right:
        for (int i = 1; i < (move.to.x - move.from.x); i++) {
            cout << i;
            if (isPieceOnSquare(board, { move.from.x + i, move.from.y })) {
                return true;
            }
        }
        break;
    case Direction::Left:
        for (int i = 1; i < (move.from.x - move.to.x); i++) {
            cout << i;
            if (isPieceOnSquare(board, { move.from.x - i, move.from.y })) {
                return true;
            }
        }
        break;
    case Direction::Down:
        for (int i = 1; i < (move.to.y - move.from.y); i++) {
            cout << i;
            if (isPieceOnSquare(board, { move.from.x, move.from.y + i })) {
                return true;
            }
        }
        break;
    case Direction::Up:
        for (int i = 1; i < (move.from.y - move.to.y); i++) {
            cout << i;
            if (isPieceOnSquare(board, { move.from.x, move.from.y - i })) {
                return true;
            }
        }
        break;
    default:
        break;
    }

    return false;
}

bool isBishopPathBlocked(char board[][8], Move move) {
    Direction2D dir2d = getDirection2D(move);

    for (int i = 1; i < abs(move.to.x - move.from.x); i++) {
        if (isPieceOnSquare(board, { move.from.x + i * dir2d.x, move.from.y + i * dir2d.y })) {
            return true;
        }
    }
    return false;
}

bool isQueenPathBlocked(char board[][8], Move move) {
    if (isStraight(move)) {
        return isRookPathBlocked(board, move);
    }
    else {
        return isBishopPathBlocked(board, move);
    }
}