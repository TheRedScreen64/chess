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
    };

    static char beatenPiecesBlack[16];
    int lastInsertBlack = -1;
    static char beatenPiecesWhite[16];
    int lastInsertWhite = -1;

    Color color = selectColor();

    string message = "";
    string winner = "";
    bool running = true;

    while (running) {
        displayBoard(board, 8, 8, color, message);
        displayStats(beatenPiecesBlack, beatenPiecesWhite);
        message = "";
        Move move = promptForMove(8);
        message = doMove(board, color, 8, move);

        if (message.find("beat") != string::npos) {
            string colorAsString = color == Color::Black ? "Black" : "White";
            string piece = message.substr(5, message.find(":", 0));
            if (piece[0] == 'k' || piece[0] == 'K') {
                winner = colorAsString;
                running = false;
                break;
            }
            if (color == Color::Black) {
                beatenPiecesWhite[lastInsertWhite + 1] = piece[0];
                lastInsertWhite++;
            }
            else {
                beatenPiecesBlack[lastInsertBlack + 1] = piece[0];
                lastInsertBlack++;
            }
            if (lastInsertBlack >= 15) {
                winner = "White";
                running = false;
            }
            else if (lastInsertWhite >= 15) {
                winner = "Black";
                running = false;
            }
            message = "";
        }

        if (message != "") {
            continue;
        }

        color = color == Color::Black ? Color::White : Color::Black;
    }

    system("cls");

    cout << winner << " has won!\n";
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
    cout << "Which color do you want to play? (Black 0, White 1): ";
    cin >> tempNumber;
    color = (Color)tempNumber;
    return color;
}

Move promptForMove(int maxCoord) {
    Vector2D fromPos;
    Vector2D toPos;
    bool moveValid = false;
    while (!moveValid) {
        string input;
        cout << "What is your next move? fromX,fromY,toX,toY: ";
        cin >> input;

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

string doMove(char board[][8], Color color, int sizeX, Move move) {
    string message = isMoveValid(board, color, move);
    if (message != "") {
        return message;
    }

    char piece = board[move.from.y - 1][move.from.x - 1];
    board[move.from.y - 1][move.from.x - 1] = ' ';
    board[move.to.y - 1][move.to.x - 1] = piece;

    return "";
}

// TODO: Change sketchy return type to bool
string isMoveValid(char board[][8], Color color, Move move) {
    if (board[move.from.y - 1][move.from.x - 1] == ' ') {
        return "There's no piece at that location.";
    }
    if (!ownsPiece(board, move.from, color)) {
        return "You don't own that piece.";
    }

    // TODO: Add return if from pos = to pos
    
    // TODO: Improve error messages
    switch (tolower(board[move.from.y - 1][move.from.x - 1])) {
    case 'p':
        if (isStraightDirectional(move, color)) {
            if (isPieceOnSquare(board, move.to)) {
                return "Target pos is already occupied";
            }
        } else if (!(isDiagonalPawn(move, color) && isPieceOnSquare(board, move.to) && !ownsPiece(board, move.to, color))) {
            // TODO: ugly if statement
            return "Move is not permitted";
        }
        break;
    case 'r':
        if (!isStraight(move)) {
            return "Move is not straight";
        }
        if (isRookPathBlocked(board, move)) {
            return "Move is blocked";
        }
        break;
    case 'n':
        if (!isLShape(move)) {
            return "Move is not L shape";
        }
        break;
    case 'b':
        if (!isDiagonal(move)) {
            return "Move is not diagonal";
        }
        if (isBishopPathBlocked(board, move)) {
            return "Move is blocked";
        }
        break;
    case 'q':
        if (!(isDiagonal(move) || isStraight(move))) {
            return "Move is not diagonal or straight";
        }
        if (isQueenPathBlocked(board, move)) {
            return "Move is blocked";
        }
        break;
    case 'k':
        if (abs(move.to.x - move.from.x) > 1 || abs(move.to.y - move.from.y) > 1) {
            return "Move is to far";
        }
        break;
    default:
        return "Not a valid piece type.";
    }

    Status checkBeatStatus = checkBeatPiece(board, move, color);
    if (checkBeatStatus.status) {
        return checkBeatStatus.msg;
    }

    return "";
}

Status checkBeatPiece(char board[][8], Move move, Color color) {
    if (board[move.to.y - 1][move.to.x - 1] != ' ') {
        if (ownsPiece(board, move.to, color)) {
            // TODO: Implement error type
            return { false, "That's your own piece" };
        }
        else {
            char movedPiece = board[move.from.y - 1][move.from.x - 1];
            char piece = board[move.to.y - 1][move.to.x - 1];
            string pieceStr = string(1, piece);

            board[move.from.y - 1][move.from.x - 1] = ' ';
            board[move.to.y - 1][move.to.x - 1] = movedPiece;
            return { true, "beat:" + pieceStr };
        }
    }
    return { false };
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


// NOTE: Only used by pawn
bool isStraightDirectional(Move move, Color color) {
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