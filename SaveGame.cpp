#include "ChessGame.h"
#include <fstream>

bool saveFileExists() {
	ifstream file("savegame.txt");
	return file.good();
}

void askSaveGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color color) {
	while (true) {
		system("cls");
		string input;
		cout << "Do you want to save the game? (y/n): ";
		cin >> input;

		if (input == "y") {
			saveGame(board, beatenPiecesBlack, beatenPiecesWhite, color);
			break;
		}
		else if (input == "n") {
			break;
		}
	}
}

void askLoadGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color* color) {
	if (!saveFileExists()) return;
	
	while (true) {
		system("cls");
		string input;
		cout << "Do you want to load the last game? (y/n): ";
		cin >> input;

		if (input == "y") {
			loadGame(board, beatenPiecesBlack, beatenPiecesWhite, color);
			break;
		}
		else if (input == "n") {
			break;
		}
	}
}

void saveGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color color) {
	fstream file;
	file.open("savegame.txt", ios::out | ios::trunc);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			file << board[i][j];
		}
	}
	file << endl;

	file << beatenPiecesBlack << endl;
	file << beatenPiecesWhite << endl;

	file << int(color);

	file.close();
}

void loadGame(char board[][8], char beatenPiecesBlack[16], char beatenPiecesWhite[16], Color *color) {
	fstream file;
	file.open("savegame.txt", ios::in);

	if (!file) {
		return;
	}

	string boardLine, beatenPiecesBlackLine, beatenPiecesWhiteLine, colorLine;
	Vector2D pos = { 0, 0 };
	while (getline(file, boardLine) &&
		getline(file, beatenPiecesBlackLine) &&
		getline(file, beatenPiecesWhiteLine) &&
		getline(file, colorLine)) {
		for (char temp : boardLine) {
			cout << temp;
			board[pos.y][pos.x] = temp;
			pos.x++;
			if (pos.x >= 8) {
				pos.y++;
				pos.x = 0;
			}
		}
		for (int i = 0; i < beatenPiecesBlackLine.length(); i++) {
			beatenPiecesBlack[i] = beatenPiecesBlackLine[i];
		}
		for (int i = 0; i < beatenPiecesWhiteLine.length(); i++) {
			beatenPiecesWhite[i] = beatenPiecesWhiteLine[i];
		}
		*color = (Color)stoi(colorLine);
	}

	file.close();
}