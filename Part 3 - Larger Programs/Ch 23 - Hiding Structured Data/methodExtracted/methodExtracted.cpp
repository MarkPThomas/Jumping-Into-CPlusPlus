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

struct ChessBoard
{
	ChessPiece board[8][8];
	PlayerColor whoseMove;
	ChessPiece getPiece(int x, int y);
	PlayerColor getMove();
	void makeMove(
		int fromX,
		int fromY,
		int toX,
		int toY);
};


ChessPiece ChessBoard::getPiece(int x, int y)
{
	return board[x][y];
}

PlayerColor ChessBoard::getMove()
{
	return whoseMove;
}

void ChessBoard::makeMove(
	int fromX,
	int fromY,
	int toX,
	int toY)
{
	// Normally we'd want some code that validates the move first
	board[toX][toY] = board[fromX][fromY];
}