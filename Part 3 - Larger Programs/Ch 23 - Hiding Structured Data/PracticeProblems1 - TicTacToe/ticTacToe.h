#pragma once
#include <string>

using namespace std;

enum SquareState
{
	TTTS_Blank,
	TTTS_O,
	TTTS_X
};

struct Position
{
	int row = 0;
	int column = 0;
};

struct TicTacToeSquare
{
	SquareState state = TTTS_Blank;
	Position position;
};

struct TicTacToeBoard
{
	// Array will be sized to a larger size than may be used
	static int const minToWin = 4;
	static int const maxSize = 50;
	TicTacToeSquare gameBoard[maxSize][maxSize];
	int size = maxSize;
	bool playerXInSession;

	void populateGameBoard();
	static TicTacToeSquare createSquare(int row, int column, SquareState state);
	TicTacToeSquare getSquare(Position boardPosition);
	string setPlayer(bool playerXInSession);
	
	bool validIndex(Position boardPosition);
	bool choiceTaken(Position boardPosition);
	void setChoice(Position boardPosition);

	SquareState choiceSquare();
	bool choiceWins();
	bool boardIsFull();

	static string translateEnumToString(SquareState squareState);
	void drawBoard();
};

