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
	ChessPiece getPiece(int x, int y);
	PlayerColor getMove();
	void makeMove(
		int fromX,
		int fromY,
		int toX,
		int toY);
private:
	ChessPiece _board[8][8];
	PlayerColor _whoseMove;
};


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