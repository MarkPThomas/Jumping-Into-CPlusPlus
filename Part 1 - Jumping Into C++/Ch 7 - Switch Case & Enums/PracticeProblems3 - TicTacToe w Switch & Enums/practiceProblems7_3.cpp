#include <iostream>
#include <string>

using namespace std;

enum TicTacToeSquare
{
	TTTS_Blank,
	TTTS_O,
	TTTS_X
};

string setPlayer(bool playerXInSession);
bool validIndex(int boardPosition);
bool choiceTaken(int boardPosition);
void setChoice(int boardPosition, bool playerXInSession);
TicTacToeSquare choiceSquare(bool playerXInSession);
bool choiceWins(bool playerXInSession);

TicTacToeSquare square11 = TTTS_Blank;
TicTacToeSquare square12 = TTTS_Blank;
TicTacToeSquare square13 = TTTS_Blank;

TicTacToeSquare square21 = TTTS_Blank;
TicTacToeSquare square22 = TTTS_Blank;
TicTacToeSquare square23 = TTTS_Blank;

TicTacToeSquare square31 = TTTS_Blank;
TicTacToeSquare square32 = TTTS_Blank;
TicTacToeSquare square33 = TTTS_Blank;

int main()
{
	bool gameFinished = false;
	bool playerXInSession = true;
	string player = "";
	int boardPosition = 0;

	do
	{
		// Set up current turn
		boardPosition = 0;
		player = setPlayer(playerXInSession);

		// Draw board
		cout << "Tic-Tac-Toe\n";
		cout << "_______\n";
		cout << "|" << square11 << "|" << square12 << "|" << square13 << "|\n";
		cout << "_______\n";
		cout << "|" << square21 << "|" << square22 << "|" << square23 << "|\n";
		cout << "_______\n";
		cout << "|" << square31 << "|" << square32 << "|" << square33 << "|\n";
		cout << "_______\n\n";

		cout << "Player " << player << ", choose your next move by entering the index of the board position to claim:\n";
		cout << "_______\n";
		cout << "|11|12|13|\n";
		cout << "_______\n";
		cout << "|21|22|23|\n";
		cout << "_______\n";
		cout << "|31|32|33|\n";
		cout << "_______\n\n";

		//cin.clear(); cin.ignore(INT_MAX, '\n');

		cin >> boardPosition;
		// Check that choice is a valid index
		if (!validIndex(boardPosition))
		{
			cout << "That is an invalid choice. Please try again.\n";
			continue;
		}
		
		// Check that choice is not already taken
		if (choiceTaken(boardPosition))
		{
			cout << "That square is already taken. Please try again.\n";
			continue;
		}
		
		// Assign choice
		setChoice(boardPosition, playerXInSession);

		// Check whether choice wins the game
		if (choiceWins(playerXInSession))
		{
			cout << "Player " << player << " wins!\n";
			gameFinished = true;
		}

		// Change turns
		playerXInSession = !playerXInSession;
	}
	while (!gameFinished);
}

string setPlayer(bool playerXInSession)
{
	if (playerXInSession)
	{
		return "X";
	}
	return "O";
}

bool validIndex(int boardPosition)
{
	return ((boardPosition == 11) || (boardPosition == 12) || (boardPosition == 13) ||
			(boardPosition == 21) || (boardPosition == 22) || (boardPosition == 23) ||
			(boardPosition == 31) || (boardPosition == 32) || (boardPosition == 33));
}

bool choiceTaken(int boardPosition)
{
	switch(boardPosition)
	{
		case 11:
			return square11 != TTTS_Blank;
		case 12:
			return square12 != TTTS_Blank;
		case 13:
			return square13 != TTTS_Blank;
		case 21:
			return square21 != TTTS_Blank;
		case 22:
			return square22 != TTTS_Blank;
		case 23:
			return square23 != TTTS_Blank;
		case 31:
			return square31 != TTTS_Blank;
		case 32:
			return square32 != TTTS_Blank;
		case 33:
			return square33 != TTTS_Blank;
		default:
			return true;
	}
}

void setChoice(int boardPosition, bool playerXInSession)
{
	switch (boardPosition)
	{
	case 11:
		square11 = choiceSquare(playerXInSession);
		break;
	case 12:
		square12 = choiceSquare(playerXInSession);
		break;
	case 13:
		square13 = choiceSquare(playerXInSession);
		break;
	case 21:
		square21 = choiceSquare(playerXInSession);
		break;
	case 22:
		square22 = choiceSquare(playerXInSession);
		break;
	case 23:
		square23 = choiceSquare(playerXInSession);
		break;
	case 31:
		square31 = choiceSquare(playerXInSession);
		break;
	case 32:
		square32 = choiceSquare(playerXInSession);
		break;
	case 33:
		square33 = choiceSquare(playerXInSession);
		break;
	default:
		// No action to be taken
		break;
	}
}

TicTacToeSquare choiceSquare(bool playerXInSession)
{
	if (playerXInSession)
	{
		return TTTS_X;
	}
	return TTTS_O;
}

bool choiceWins(bool playerXInSession)
{
	double result = 0;
	TicTacToeSquare choiceCheck = choiceSquare(playerXInSession);;

	// Check rows
	result = (square11 == choiceCheck) && (square12 == choiceCheck) && (square13 == choiceCheck);
	if (result == 1) { return true; }

	result = (square21 == choiceCheck) && (square22 == choiceCheck) && (square23 == choiceCheck);
	if (result == 1) { return true; }

	result = (square31 == choiceCheck) && (square32 == choiceCheck) && (square33 == choiceCheck);
	if (result == 1) { return true; }

	// Check columns
	result = (square11 == choiceCheck) && (square21 == choiceCheck) && (square31 == choiceCheck);
	if (result == 1) { return true; }

	result = (square12 == choiceCheck) && (square22 == choiceCheck) && (square32 == choiceCheck);
	if (result == 1) { return true; }

	result = (square13 == choiceCheck) && (square23 == choiceCheck) && (square33 == choiceCheck);
	if (result == 1) { return true; }

	// Check diagonals
	result = (square11 == choiceCheck) && (square22 == choiceCheck) && (square33 == choiceCheck);
	if (result == 1) { return true; }

	result = (square13 == choiceCheck) && (square22 == choiceCheck) && (square31 == choiceCheck);
	if (result == 1) { return true; }

	return false;
}