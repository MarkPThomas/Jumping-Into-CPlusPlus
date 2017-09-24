#pragma once

enum ChessPiece
{
	EMPTY_SQUARE,
	WHITE_PAWN
};

enum PlayerColor
{
	PC_WHITE,
	PC_BLACK
};

class ChessBoard
{
public:
	ChessBoard();
	ChessBoard(int boardSize);
	ChessPiece getPiece(int x, int y);
	PlayerColor getMove();
	void makeMove(
		int fromX,
		int fromY,
		int toX,
		int toY);
private:
	const static int _maxBoardSize = 50;
	ChessPiece _board[_maxBoardSize][_maxBoardSize];
	PlayerColor _whoseMove;
	int _moveCount;
};
