#include <iostream>
#include <string>

using namespace std;

enum TicTacToeSquare
{
	TTTS_Blank,
	TTTS_O,
	TTTS_X
};

// Array will be sized to a larger size than may be used

void populateGameBoard(TicTacToeSquare array[][50], int size);
string setPlayer(bool playerXInSession);
string translateEnumToString(TicTacToeSquare squareState);
bool validIndex(int boardPosition[], int boardSize);
bool choiceTaken(int boardPosition[], TicTacToeSquare gameBoard[][50]);
void setChoice(int boardPosition[], TicTacToeSquare gameBoard[][50], bool playerXInSession);
TicTacToeSquare choiceSquare(bool playerXInSession);
bool choiceWins(bool playerXInSession, TicTacToeSquare gameBoard[][50], int size);
bool boardIsFull(TicTacToeSquare gameBoard[][50], int size);

int const minToWin = 4;

int main()
{
	bool gameFinished = false;
	bool playerXInSession = true;
	string player = "";
	int row = 0;
	int column = 0;

	// Set up game board
	int const size = 50;
	int sizeUsed = 4;

	cout << "Please specify the number of spaces to be used for the rows/columns of the square board:\n";
	cout << "(Default is " << minToWin << ")\n";
	cin >> sizeUsed;
	if (sizeUsed < minToWin) { sizeUsed = minToWin; }

	TicTacToeSquare gameBoard[size][size];
	populateGameBoard(gameBoard, size);

	do
	{
		// Set up current turn
		row = 0;
		column = 0;
		player = setPlayer(playerXInSession);

		// Draw board
		cout << "\n" << "Tic-Tac-Toe\n";
		cout << minToWin << "-in-a-row are needed to win!\n";
		string horizontalBar = " _";
		for (size_t i = 0; i < sizeUsed; i++)
		{
			horizontalBar += "__";
		}

		for (size_t i = 0; i <= sizeUsed; i++)
		{
			if (i == 0)
			{
				for (size_t j = 0; j <= sizeUsed; j++)
				{
					if (j == 0)
					{
						cout << " ";
					}
					else
					{
						cout << " " << j;
					}
				}
				cout << "\n";
			}
			else
			{
				cout << horizontalBar << "\n";
				for (size_t j = 0; j <= sizeUsed; j++)
				{
					if (j == 0)
					{
						cout << i;
					}
					else
					{
						cout << "|" << translateEnumToString(gameBoard[i - 1][j - 1]);
					}
				}
				cout << "|\n";
			}
		}
		cout << horizontalBar << "\n\n";

		cout << "Player " << player << ", choose your next board position to claim:\n";

		cout << "Row: \n";
		cin >> row;
		row--;

		cout << "Column: \n";
		cin >> column;
		column--;

		int boardPosition[2] = { row, column };

		// Check that choice is a valid index
		if (!validIndex(boardPosition, sizeUsed))
		{
			cout << "That is an invalid choice. Please try again.\n";
			continue;
		}

		// Check that choice is not already taken
		if (choiceTaken(boardPosition, gameBoard))
		{
			cout << "That square is already taken. Please try again.\n";
			continue;
		}

		// Assign choice
		setChoice(boardPosition, gameBoard, playerXInSession);

		// Check whether choice wins the game
		if (choiceWins(playerXInSession, gameBoard, sizeUsed))
		{
			cout << "Player " << player << " wins!\n";
			gameFinished = true;
		}

		// Check whether or the entire board is filled
		if (boardIsFull(gameBoard, sizeUsed))
		{
			cout << "Board is full. The game is a tie!\n";
			gameFinished = true;
		}

		// Check if game cannot be won before the board is filled
		// Meh

		// Change turns
		playerXInSession = !playerXInSession;
	} while (!gameFinished);
}


void populateGameBoard(TicTacToeSquare array[][50], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			array[i][j] = TTTS_Blank;
		}
	}
}

string setPlayer(bool playerXInSession)
{
	if (playerXInSession)
	{
		return "X";
	}
	return "O";
}

bool validIndex(int boardPosition[], int boardSize)
{
	return (((boardPosition[0] >= 0) && (boardPosition[1] >= 0)) &&
		((boardPosition[0] < boardSize) && (boardPosition[1] < boardSize)));
}

bool choiceTaken(int boardPosition[], TicTacToeSquare gameBoard[][50])
{
	return (gameBoard[boardPosition[0]][boardPosition[1]] != TTTS_Blank);
}

void setChoice(int boardPosition[], TicTacToeSquare gameBoard[][50], bool playerXInSession)
{
	gameBoard[boardPosition[0]][boardPosition[1]] = choiceSquare(playerXInSession);
}

TicTacToeSquare choiceSquare(bool playerXInSession)
{
	if (playerXInSession)
	{
		return TTTS_X;
	}
	return TTTS_O;
}

bool choiceWins(bool playerXInSession, TicTacToeSquare gameBoard[][50], int size)
{
	TicTacToeSquare choiceCheck = choiceSquare(playerXInSession);;
	double score;

	// Check rows
	for (size_t i = 0; i < size; i++)
	{
		score = 0;
		for (size_t j = 0; j < size; j++)
		{
			if (gameBoard[i][j] == choiceCheck)
			{
				score++;
				if (score >= minToWin) { return true; }
			}
			else
			{
				score = 0;
			}
		}
	}

	// Check columns
	for (size_t i = 0; i < size; i++)
	{
		score = 0;
		for (size_t j = 0; j < size; j++)
		{
			if (gameBoard[j][i] == choiceCheck)
			{
				score++;
				if (score >= minToWin) { return true; }
			}
			else
			{
				score = 0;
			}
		}
	}

	// Check diagonals
	score = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (gameBoard[i][i] == choiceCheck)
		{
			score++;
			if (score >= minToWin) { return true; }
		}
		else
		{
			score = 0;
		}
	}

	score = 0;
	for (size_t i = 0; i < size; i++)
	{
		int maxIndex = size - 1;
		if (gameBoard[maxIndex - i][maxIndex - i] == choiceCheck)
		{
			score++;
			if (score >= minToWin) { return true; }
		}
		else
		{
			score = 0;
		}
	}

	return false;
}

bool boardIsFull(TicTacToeSquare gameBoard[][50], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (gameBoard[i][j] == TTTS_Blank)
			{
				return false;
			}
		}
	}
	return true;
}

string translateEnumToString(TicTacToeSquare squareState)
{
	switch (squareState)
	{
	case TTTS_Blank:
		return " ";
	case TTTS_O:
		return "O";
	case TTTS_X:
		return "X";
	default:
		return "~";
	}
}