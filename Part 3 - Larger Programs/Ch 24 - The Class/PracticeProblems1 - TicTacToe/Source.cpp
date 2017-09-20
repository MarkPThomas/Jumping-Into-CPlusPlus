#include <iostream>
#include <string>
#include "ticTacToe.h"

using namespace std;

int main()
{
	bool gameFinished = false;
	bool playerXInSession = true;
	string player = "";
	int row = 0;
	int column = 0;

	// Set up game board
	int sizeUsed = 4;
	TicTacToeBoard gameBoard;

	cout << "Please specify the number of spaces to be used for the rows/columns of the square board:\n";
	cout << "(Default is " << gameBoard.minToWin << " and max is " << gameBoard.maxSize << ")\n";
	cin >> sizeUsed;
	if (sizeUsed < gameBoard.minToWin) { sizeUsed = gameBoard.minToWin; }
	if (sizeUsed > gameBoard.maxSize) { sizeUsed = gameBoard.maxSize; }

	gameBoard.size = sizeUsed;
	gameBoard.populateGameBoard();

	do
	{
		// Set up current turn
		row = 0;
		column = 0;
		player = gameBoard.setPlayer(playerXInSession);

		// Draw board
		gameBoard.drawBoard();
		
		cout << "Player " << player << ", choose your next board position to claim:\n";

		cout << "Row: \n";
		cin >> row;
		row--;

		cout << "Column: \n";
		cin >> column;
		column--;

		// Assign position and check that choice is a valid index
		Position boardPosition;
		boardPosition.row = row;
		boardPosition.column = column;

		// Check that choice is a valid index
		if (!gameBoard.validIndex(boardPosition))
		{
			cout << "That is an invalid choice. Please try again.\n";
			continue;
		}

		// Check that choice is not already taken
		if (gameBoard.choiceTaken(boardPosition))
		{
			cout << "That square is already taken. Please try again.\n";
			continue;
		}

		// Assign choice
		gameBoard.setChoice(boardPosition);

		// Check whether choice wins the game
		if (gameBoard.choiceWins())
		{
			cout << "Player " << player << " wins!\n";
			gameFinished = true;
		}

		// Check whether or the entire board is filled
		if (gameBoard.boardIsFull())
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



