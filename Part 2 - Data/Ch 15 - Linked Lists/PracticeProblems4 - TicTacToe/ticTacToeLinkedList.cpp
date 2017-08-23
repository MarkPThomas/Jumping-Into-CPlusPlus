#include <iostream>
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
	int row;
	int column;
};

struct TicTacToeSquare
{
	SquareState state;
	Position position;
	TicTacToeSquare* next;
	TicTacToeSquare* previous;
};

TicTacToeSquare* addToLinkedList(TicTacToeSquare* p_list, int row, int column, SquareState state);
TicTacToeSquare* createGameBoard(int size);
TicTacToeSquare* getSquare(Position boardPosition, TicTacToeSquare* gameBoard);
void drawBoard(int size, TicTacToeSquare& gameBoard);
string setPlayer(bool playerXInSession);
string translateEnumToString(SquareState squareState);
bool validIndex(Position boardPosition, int boardSize);
bool choiceTaken(TicTacToeSquare& currentSquare);
void setChoice(TicTacToeSquare* currentSquare, bool playerXInSession);
SquareState choiceSquare(bool playerXInSession);
bool squareMatches(TicTacToeSquare& gameBoard, SquareState choiceCheck, int row, int column);
bool choiceWins(bool playerXInSession, TicTacToeSquare& gameBoard, int size);
bool boardIsFull(TicTacToeSquare* gameBoard);

int const minToWin = 4;

int main()
{
	bool gameFinished = false;
	bool playerXInSession = true;
	string player = "";
	int row = 0;
	int column = 0;

	// Set up game board
	int sizeUsed = 4;

	cout << "Please specify the number of spaces to be used for the rows/columns of the square board:\n";
	cout << "(Default is " << minToWin << ")\n";
	cin >> sizeUsed;
	if (sizeUsed < minToWin) { sizeUsed = minToWin; }

	TicTacToeSquare* gameBoard = createGameBoard(sizeUsed);

	do
	{
		// Set up current turn
		row = 0;
		column = 0;
		player = setPlayer(playerXInSession);

		// Draw board
		drawBoard(sizeUsed, *gameBoard);

		cout << "Player " << player << ", choose your next board position to claim:\n";

		cout << "Row: \n";
		cin >> row;
		row--;

		cout << "Column: \n";
		cin >> column;
		column--;

		// Assign position and check that choice is a valid index
		Position boardPosition = { row, column };
		if (!validIndex(boardPosition, sizeUsed))
		{
			cout << "That is an invalid choice. Please try again.\n";
			continue;
		}

		// Get new board square
		TicTacToeSquare* currentSquare = getSquare(boardPosition, gameBoard);
		if (!currentSquare)
		{
			cout << "You have selected a position that does not exist on the board. Please try again.\n";
			continue;;
		}

		// Check that choice is not already taken
		if (choiceTaken(*currentSquare))
		{
			cout << "That square is already taken. Please try again.\n";
			continue;
		}

		// Assign choice
		setChoice(currentSquare, playerXInSession);

		// Check whether choice wins the game
		if (choiceWins(playerXInSession, *gameBoard, sizeUsed))
		{
			cout << "Player " << player << " wins!\n";
			gameFinished = true;
		}

		// Check whether or the entire board is filled
		if (boardIsFull(gameBoard))
		{
			cout << "Board is full. The game is a tie!\n";
			gameFinished = true;
		}

		// Check if game cannot be won before the board is filled
		// Meh

		// Change turns
		playerXInSession = !playerXInSession;
	} while (!gameFinished);

	delete gameBoard;
}

TicTacToeSquare* addToLinkedList(TicTacToeSquare* p_list, int row, int column, SquareState state)
{
	TicTacToeSquare* p_item = new TicTacToeSquare;
	p_item->position.row = row;
	p_item->position.column = column;
	p_item->state = state;

	p_item->previous = nullptr;
	p_item->next = p_list;
	if (p_list)
	{
		p_list->previous = p_item;
	}
	
	return p_item;
}

TicTacToeSquare* createGameBoard(int size)
{
	TicTacToeSquare* p_item = new TicTacToeSquare;
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			p_item = addToLinkedList(p_item, row, column, TTTS_Blank);
		}
	}
	return p_item;
}

TicTacToeSquare* getSquare(Position boardPosition, TicTacToeSquare* gameBoard)
{
	TicTacToeSquare* p_current = gameBoard;
	while (p_current != nullptr)
	{
		if ((p_current->position.row == boardPosition.row) &&
			(p_current->position.column == boardPosition.column))
		{
			return p_current;
		}
		p_current = p_current->next;
	}
	return nullptr;
}

void drawBoard(int size, TicTacToeSquare& gameBoard)
{
	// Draw board
	cout << "\n" << "Tic-Tac-Toe\n";
	cout << minToWin << "-in-a-row are needed to win!\n";
	string horizontalBar = " _";
	for (int row = 0; row < size; row++)
	{
		horizontalBar += "__";
	}

	for (int row = 0; row <= size; row++)
	{
		if (row == 0)
		{
			for (int column = 0; column <= size; column++)
			{
				if (column == 0)
				{
					cout << " ";
				}
				else
				{
					cout << " " << column;
				}
			}
			cout << "\n";
		}
		else
		{
			cout << horizontalBar << "\n";
			for (int column = 0; column <= size; column++)
			{
				if (column == 0)
				{
					cout << row;
				}
				else
				{
					Position boardPosition = { row-1, column-1 };
					TicTacToeSquare* currentSquare = getSquare(boardPosition, &gameBoard);
					cout << "|" << translateEnumToString(currentSquare->state);
				}
			}
			cout << "|\n";
		}
	}
	cout << horizontalBar << "\n\n";
}

string setPlayer(bool playerXInSession)
{
	if (playerXInSession)
	{
		return "X";
	}
	return "O";
}

bool validIndex(Position boardPosition, int boardSize)
{
	return (((boardPosition.row >= 0) && (boardPosition.column >= 0)) &&
		((boardPosition.row < boardSize) && (boardPosition.column < boardSize)));
}

bool choiceTaken(TicTacToeSquare& gameSquare)
{
	return (gameSquare.state != TTTS_Blank);
}

void setChoice(TicTacToeSquare* gameSquare, bool playerXInSession)
{
	gameSquare->state = choiceSquare(playerXInSession);
}

SquareState choiceSquare(bool playerXInSession)
{
	if (playerXInSession)
	{
		return TTTS_X;
	}
	return TTTS_O;
}

bool choiceWins(bool playerXInSession, TicTacToeSquare& gameBoard, int size)
{
	SquareState choiceCheck = choiceSquare(playerXInSession);;
	double score;

	// Check columns
	for (int row = 0; row < size; row++)
	{
		score = 0;
		for (int column = 0; column < size; column++)
		{
			if (squareMatches(gameBoard, choiceCheck, row, column))
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

	// Check rows
	for (int column = 0; column < size; column++)
	{
		score = 0;
		for (int row = 0; row < size; row++)
		{
			if (squareMatches(gameBoard, choiceCheck, row, column))
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
	for (int rowAndColumn = 0; rowAndColumn < size; rowAndColumn++)
	{
		if (squareMatches(gameBoard, choiceCheck, rowAndColumn, rowAndColumn))
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
	for (int rowColumn = 0; rowColumn < size; rowColumn++)
	{
		int maxIndex = size - 1;
		if (squareMatches(gameBoard, choiceCheck, rowColumn, rowColumn))
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

bool squareMatches(TicTacToeSquare& gameBoard, SquareState choiceCheck, int row, int column)
{
	Position boardPosition = { row, column };
	TicTacToeSquare* currentSquare = getSquare(boardPosition, &gameBoard);
	return (currentSquare->state == choiceCheck);
}

bool boardIsFull(TicTacToeSquare* gameBoard)
{
	TicTacToeSquare* p_current = gameBoard;
	while (p_current != nullptr)
	{
		if ((p_current->state == TTTS_Blank))
		{
			return false;
		}
		p_current = p_current->next;
	}
	return true;
}

string translateEnumToString(SquareState squareState)
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