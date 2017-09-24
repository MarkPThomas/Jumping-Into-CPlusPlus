#include "constructor.h"

ChessBoard::ChessBoard()
// The colon is followed by the list of variables with the argument to the constructor.
// This is called the initialiation list.
// An initialization list must be used for the following fields:
// 1. const fields
// 2. reference fields
	: _whoseMove(PC_WHITE), _moveCount(0)
{
	//_whoseMove = PC_WHITE;

	// Start off by emptying the whole board, then fill it in with pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_board[i][j] = EMPTY_SQUARE;
		}
	}
}

ChessBoard::ChessBoard(int boardSize) : _whoseMove(PC_WHITE), _moveCount(0)
{
	if (boardSize > _maxBoardSize)
	{
		boardSize = _maxBoardSize;
	}

	// Start off by emptying the whole board, then fill it in with pieces
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			_board[i][j] = EMPTY_SQUARE;
		}
	}
}


ChessPiece ChessBoard::getPiece(int x, int y)
{
	return _board[x][y];
}

PlayerColor ChessBoard::getMove()
{
	return _whoseMove;
}

void ChessBoard::makeMove(
	int fromX,
	int fromY,
	int toX,
	int toY)
{
	// Normally we'd want some code that validates the move first
	_board[toX][toY] = _board[fromX][fromY];
}