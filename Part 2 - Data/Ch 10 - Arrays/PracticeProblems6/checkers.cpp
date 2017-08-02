#include <iostream>
#include <string>

using namespace std;

// Board indices (8x8)
// 00	01	02	03	04	05	06	07
// 10	11	12	13	14	15	16	17
// 20	21	22	23	24	25	26	27
// 30	31	32	33	34	35	36	37
// 40	41	42	43	44	45	46	47
// 50	51	52	53	54	55	56	57
// 60	61	62	63	64	65	66	67
// 70	71	72	73	74	75	76	77
//
// Rules for valid squares:
// even row + odd column
// odd row + even column
// x vs. X for regular vs. king
// o vs. O for regular vs. king
// # for filled square?

enum CheckersSquare
{
	Checkers_Filled,
	Checkers_NotFilled,
	Checkers_SinglePiece_Black,
	Checkers_KingPiece_Black,
	Checkers_SinglePiece_Red,
	Checkers_KingPiece_Red
};

enum CheckersPlayers
{
	CheckersPlayers_Black,
	CheckersPlayers_Red,
};

enum CheckersMoves
{
	CheckersMoves_ForwardLeft = 1,
	CheckersMoves_ForwardRight = 2,
	CheckersMoves_BackwardLeft = 3,
	CheckersMoves_BackwardRight = 4,
};

// Array will be sized to a larger size than may be used
int const maxBoardSize = 50;
int const minBoardSize = 8;

int const maxPieces = 500;
int const minPieces = 12;

void drawBoard(CheckersSquare gameBoard[][50], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);

void populateGameBoard(CheckersSquare array[][50], int size);
void populateBlackPieces(int boardSize, CheckersSquare playerPieces[][50], int numberOfPieces);
void populateRedPieces(int boardSize, CheckersSquare playerPieces[][50], int numberOfPieces);
bool isTurnWinning(int boardPosition[], int boardMove[], CheckersPlayers player, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], CheckersSquare gameBoard[][50], int boardSizeUsed);
CheckersPlayers setPlayer(CheckersPlayers playerBlackInSession);

void getBoardPosition(int boardPosition[], int boardSizeUsed, CheckersPlayers player, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);
bool isValidPosition(int boardPosition[], CheckersPlayers player, CheckersSquare playerPieces[][50]);

void getMoveOffset(CheckersPlayers player, CheckersMoves move, int moveOffset[2]);
void chooseBoardMove(int boardPosition[], int boardMove[], int boardSizeUsed, CheckersSquare playerPiece, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);
bool moveIsValid(int boardPosition[], int offset[], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);
bool moveIsOntoOppositionPiece(int landingRow, int landingColumn, CheckersSquare oppositionPieces[][50]);
bool isInBounds(int row, int column, int boardSizeUse);
bool isOnBoardTopBottomEdge(int row, int boardSizeUsed);
bool makeBoardMove(int boardPosition[], int boardMove[], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);
void kingPiece(int row, int column, CheckersSquare playerPieces[][50]);

bool choiceWins(int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);
bool areAllOppositionPiecesEliminated(int boardSizeUsed, CheckersSquare oppositionPieces[][50]);
bool areAllOppositionPiecesTrapped(int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50]);
bool isPieceTrapped(int boardPosition[], CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], int boardSizeUsed);
bool pieceCanJumpNeighboringPiece(int boardPosition[], CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], int boardSizeUsed);

string translateEnumToString(CheckersSquare squareState);
string translateEnumToString(CheckersPlayers squareState);
bool isEven(int number);
bool isOdd(int number);
bool isValidSquare(int row, int column);
bool isPieceKing(CheckersSquare playerPiece);
CheckersPlayers getPlayer(CheckersSquare playerPiece);

int main()
{
	// Set up game board
	int boardSizeUsed = minBoardSize;

	CheckersSquare gameBoard[maxBoardSize][maxBoardSize];
	populateGameBoard(gameBoard, maxBoardSize);

	// Set up number of pieces & starting player
	int numberOfPiecesUsed = minPieces;

	CheckersSquare BlackPieces[maxBoardSize][maxBoardSize];
	populateBlackPieces(boardSizeUsed, BlackPieces, numberOfPiecesUsed);

	CheckersSquare RedPieces[maxBoardSize][maxBoardSize];
	populateRedPieces(boardSizeUsed, RedPieces, numberOfPiecesUsed);

	CheckersPlayers player = CheckersPlayers_Black;

	// Run game
	bool gameFinished;
	int boardPosition[2];
	int boardMove[2];
	drawBoard(gameBoard, boardSizeUsed, BlackPieces, RedPieces);
	do
	{	
		if (player == CheckersPlayers_Black)
		{
			gameFinished = isTurnWinning(boardPosition, boardMove, player, BlackPieces, RedPieces, gameBoard, boardSizeUsed);
		}
		else
		{
			gameFinished = isTurnWinning(boardPosition, boardMove, player, RedPieces, BlackPieces, gameBoard, boardSizeUsed);
		}

		// Set up next turn
		player = setPlayer(player);
	} while (!gameFinished);
}

bool isTurnWinning(int boardPosition[], int boardMove[], CheckersPlayers player, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], CheckersSquare gameBoard[][50], int boardSizeUsed)
{
	getBoardPosition(boardPosition, boardSizeUsed, player, playerPieces, oppositionPieces);
	CheckersSquare playerPiece = playerPieces[boardPosition[0]][boardPosition[1]];

	// Handle 1 or more moves, depending on each move result
	bool nextPlayer;
	do
	{
		chooseBoardMove(boardPosition, boardMove, boardSizeUsed, playerPiece, playerPieces, oppositionPieces);
		nextPlayer = !makeBoardMove(boardPosition, boardMove, boardSizeUsed, playerPieces, oppositionPieces);
		drawBoard(gameBoard, boardSizeUsed, playerPieces, oppositionPieces);

		// Check whether move wins the game
		if (choiceWins(boardSizeUsed, playerPieces, oppositionPieces))
		{
			cout << "\n" << "Player " << translateEnumToString(player) << " wins!\n";
			return true;
		}
	} while (!nextPlayer);
	return false;
}

void drawBoard(CheckersSquare gameBoard[][50], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
	cout << "\n" << "Checkers\n";
	cout << "\n" << "Black (O) Side\n";
	string horizontalBar = " _";
	for (size_t i = 0; i < boardSizeUsed; i++)
	{
		horizontalBar += "__";
	}

	for (size_t i = 0; i <= boardSizeUsed; i++)
	{
		if (i == 0)
		{
			for (size_t j = 0; j <= boardSizeUsed; j++)
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
			for (size_t j = 0; j <= boardSizeUsed; j++)
			{
				if (j == 0)
				{
					cout << i;
				}
				else
				{
					string squareCharacter;
					if (playerPieces[i - 1][j - 1] != Checkers_NotFilled)
					{
						squareCharacter = translateEnumToString(playerPieces[i - 1][j - 1]);
					}
					else if (oppositionPieces[i - 1][j - 1] != Checkers_NotFilled)
					{
						squareCharacter = translateEnumToString(oppositionPieces[i - 1][j - 1]);
					}
					else
					{
						squareCharacter = translateEnumToString(gameBoard[i - 1][j - 1]);
					}
					
					cout << "|" << squareCharacter;
				}
			}
			cout << "|\n";
		}
	}
	cout << "\n" << "Red (X) Side\n";
	cout << horizontalBar << "\n\n";
}

void populateGameBoard(CheckersSquare array[][50], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (isValidSquare(i, j))
			{
				array[i][j] = Checkers_Filled;
			}
			else
			{
				array[i][j] = Checkers_NotFilled;
			}
		}
	}
}

void populateBlackPieces(int boardSize, CheckersSquare playerPieces[][50], int numberOfPieces)
{
	int currentPlayerPiece = 1;

	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++)
		{
			if ((currentPlayerPiece <= numberOfPieces) && 
				(isValidSquare(i, j)))
			{
				playerPieces[i][j] = Checkers_SinglePiece_Black;
				currentPlayerPiece++;
			}
			else
			{
				playerPieces[i][j] = Checkers_NotFilled;
			}
		}
	}
}

void populateRedPieces(int boardSize, CheckersSquare playerPieces[][50], int numberOfPieces)
{
	int currentPlayerPiece = 1;

	// Counting starts from lower right side 
	// (note using int for decrement loop as size_t is unsigned and has errors when the incrementor < 0)
	for (int i = boardSize - 1; i >= 0 ; i--)
	{
		for (int j = boardSize - 1; j >= 0; j--)
		{
			if ((currentPlayerPiece <= numberOfPieces) &&
				(isValidSquare(i, j)))
			{
				playerPieces[i][j] = Checkers_SinglePiece_Red;
				currentPlayerPiece++;
			}
			else
			{
				playerPieces[i][j] = Checkers_NotFilled;
			}
		}
	}
}

CheckersPlayers setPlayer(CheckersPlayers playerBlackInSession)
{
	if (playerBlackInSession == CheckersPlayers_Red)
	{
		return CheckersPlayers_Black;
	}
	return CheckersPlayers_Red;
}



void getMoveOffset(CheckersPlayers player, CheckersMoves move, int moveOffset[2])
{
	switch (move)
	{
		case CheckersMoves_ForwardLeft:
			moveOffset[0] = 1;
			moveOffset[1] = 1;
			break;
		case CheckersMoves_ForwardRight:
			moveOffset[0] = 1;
			moveOffset[1] = -1;
			break;
		case CheckersMoves_BackwardLeft:
			moveOffset[0] = -1;
			moveOffset[1] = 1;
			break;
		case CheckersMoves_BackwardRight:
			moveOffset[0] = -1;
			moveOffset[1] = -1;
			break;
		default:
			moveOffset[0] = 0;
			moveOffset[1] = 0;
			break;
	}

	// Adjust for player direction
	int direction = 1;
	if (player == CheckersPlayers_Red)
	{
		direction = -1;
	}

	moveOffset[0] = moveOffset[0] * direction;
	moveOffset[1] = moveOffset[1] * direction;
}

CheckersPlayers getPlayer(CheckersSquare playerPiece)
{
	if ((playerPiece == Checkers_SinglePiece_Black) || (playerPiece == Checkers_KingPiece_Black))
	{
		return CheckersPlayers_Black;
	}
	return CheckersPlayers_Red;
}

bool isPieceKing(CheckersSquare playerPiece)
{
	return ((playerPiece == Checkers_KingPiece_Black) || (playerPiece == Checkers_KingPiece_Red));
}



void getBoardPosition(int boardPosition[], int boardSizeUsed, CheckersPlayers player, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
	int startRow = 0;
	int startColumn = 0;
	bool isCurrentValidPosition;

	do
	{
		cout << "Player " << translateEnumToString(player) << ", choose the piece to move:\n";

		cout << "Row: \n";
		cin >> startRow;
		startRow--;
		boardPosition[0] = startRow;

		cout << "Column: \n";
		cin >> startColumn;
		startColumn--;
		boardPosition[1] = startColumn;
		
		cout << '\n';
		isCurrentValidPosition = isValidPosition(boardPosition, player, playerPieces);
		if (!isCurrentValidPosition)
		{
			cout << "Position chosen is invalid. \n";
			cout << "Please choose a row/column locating the piece to move.\n";
			continue;
		}

		isCurrentValidPosition = !isPieceTrapped(boardPosition, playerPieces, oppositionPieces, boardSizeUsed);
		if (!isCurrentValidPosition)
		{
			cout << "Piece chosen is trapped! \n";
			cout << "Please choose a different piece.\n";
			continue;
		}
	}
	while (!isCurrentValidPosition);
}

bool isValidPosition(int boardPosition[], CheckersPlayers player, CheckersSquare playerPieces[][50])
{
	if (player == CheckersPlayers_Black)
	{
		return ((playerPieces[boardPosition[0]][boardPosition[1]] == Checkers_SinglePiece_Black) ||
			(playerPieces[boardPosition[0]][boardPosition[1]] == Checkers_KingPiece_Black));
	}

	if (player == CheckersPlayers_Red)
	{
		return ((playerPieces[boardPosition[0]][boardPosition[1]] == Checkers_SinglePiece_Red) ||
			(playerPieces[boardPosition[0]][boardPosition[1]] == Checkers_KingPiece_Red));
	}

	return false;
}



void chooseBoardMove(int boardPosition[], int boardMove[], int boardSizeUsed, CheckersSquare playerPiece, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
	int moveChoice = 0;
	int tempMove[2];
	bool isCurrentValidMove = false;
	CheckersPlayers player = getPlayer(playerPiece);
	
	bool isCurrentPieceKing = isPieceKing(playerPiece);
	int maxEnum = 2;
	if (isCurrentPieceKing) { maxEnum = 4; }
	
	string pieceType = "regular";
	if (isCurrentPieceKing)
	{
		pieceType = "king";
	}

	do
	{
		cout << "\n" << "Player " << translateEnumToString(player) << ", choose where to move the " << pieceType << " piece in reference to your starting side and direction:\n";
		cout << "1: Forward-Left\n";
		cout << "2: Forward-Right\n";
		if (isCurrentPieceKing)
		{
			cout << "3: Backward-Left\n";
			cout << "4: Backward-Right\n";
		}
		cin >> moveChoice;

		// (1) Is a valid choice selected?
		if (moveChoice < 1 || moveChoice > maxEnum)
		{
			cout << "Please enter a valid move number.\n";
			continue;
		}
		
		getMoveOffset(player, static_cast<CheckersMoves>(moveChoice), tempMove);

		// (2) Is landing square valid?
		isCurrentValidMove = moveIsValid(boardPosition, tempMove, boardSizeUsed, playerPieces, oppositionPieces);
		if (!isCurrentValidMove)
		{
			cout << "\n" << "Move will land piece out of bounds, or onto an occupied square." << "\n";
			cout << "Please choose another move." << "\n";
		}
	} while (!isCurrentValidMove);

	boardMove[0] = tempMove[0];
	boardMove[1] = tempMove[1];
}

bool moveIsValid(int boardPosition[], int offset[], int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
	int landingRow = boardPosition[0] + offset[0];
	int landingColumn = boardPosition[1] + offset[1];

	// (1) Cannot move out of bounds
	if (!isInBounds(landingRow, landingColumn, boardSizeUsed)) { return false; }

	// (2) Cannot move onto own piece
	CheckersSquare neighboringPlayerPiece = playerPieces[landingRow][landingColumn];
	if (neighboringPlayerPiece != Checkers_NotFilled) { return false; }

	// (3) Can only move onto opposition piece of the following square is in bounds & clear
	if (moveIsOntoOppositionPiece(landingRow, landingColumn, oppositionPieces))
	{
		landingRow += offset[0];
		landingColumn += offset[1];

		// (3a) Cannot move out of bounds
		if (!isInBounds(landingRow, landingColumn, boardSizeUsed)) { return false; }

		// (3b) Cannot move onto any occupied square
		CheckersSquare landingSquareOpposition = oppositionPieces[landingRow][landingColumn];
		CheckersSquare landingSquarePlayer = playerPieces[landingRow][landingColumn];
		if ((landingSquareOpposition != Checkers_NotFilled) ||
			(landingSquarePlayer != Checkers_NotFilled))
		{
			return false;
		}
	}
	return true;
}

bool moveIsOntoOppositionPiece(int landingRow, int landingColumn, CheckersSquare oppositionPieces[][50])
{
	CheckersSquare neighboringOpposingPiece = oppositionPieces[landingRow][landingColumn];
	return (neighboringOpposingPiece != Checkers_NotFilled);
}

bool isInBounds(int row, int column, int boardSizeUse)
{
	return ((0 <= row) && (row < boardSizeUse) &&
			(0 <= column) && (column < boardSizeUse));
}



bool makeBoardMove(int boardPosition[], int boardMove[], int boardSizeUsed, CheckersSquare playerPieces[][50],  CheckersSquare oppositionPieces[][50])
{
	int landingRow = boardPosition[0] + boardMove[0];
	int landingColumn = boardPosition[1] + boardMove[1];
	bool continueTurn = false;
	bool pieceWasJumped = false;

	// (1) Check if land on opposition piece. If so,
	if (moveIsOntoOppositionPiece(landingRow, landingColumn, oppositionPieces))
	{
		// (1a) Remove opposition piece.
		oppositionPieces[landingRow][landingColumn] = Checkers_NotFilled;
		pieceWasJumped = true;
		cout << "A piece was just jumped!\n";

		// (1b) repeat offset move	.
		landingRow += boardMove[0];
		landingColumn += boardMove[1];

		// (1c) Note that turn can continue.
		continueTurn = true;
	}
	
	// (2) Move player piece by offset.
	CheckersSquare currentPiece = playerPieces[boardPosition[0]][boardPosition[1]];
	playerPieces[boardPosition[0]][boardPosition[1]] = Checkers_NotFilled;
	playerPieces[landingRow][landingColumn] = currentPiece;
	boardPosition[0] = landingRow;
	boardPosition[1] = landingColumn;

	// (3) Check if player had jumped a piece and can jump any other pieces. If not, the turn is over.
	if (pieceWasJumped) { continueTurn = pieceCanJumpNeighboringPiece(boardPosition, playerPieces, oppositionPieces, boardSizeUsed); }

	// (4) Check if top/bottom edge of board. If so, king the piece, but any continuing turns must be stopped.
	if (isOnBoardTopBottomEdge(landingRow, boardSizeUsed))
	{
		if (!isPieceKing(currentPiece))
		{
			kingPiece(landingRow, landingColumn, playerPieces);
			cout << "Piece is upgraded to a king!\n";
		}
		continueTurn = false;
	}

	return continueTurn;
}

bool isOnBoardTopBottomEdge(int row, int boardSizeUsed)
{
	return ((row == 0) || (row == (boardSizeUsed - 1)));
}

void kingPiece(int row, int column, CheckersSquare playerPieces[][50])
{
	CheckersSquare currentPiece = playerPieces[row][column];
	if (currentPiece == Checkers_SinglePiece_Black)
	{
		playerPieces[row][column] = Checkers_KingPiece_Black;
	}
	if (currentPiece == Checkers_SinglePiece_Red)
	{
		playerPieces[row][column] = Checkers_KingPiece_Red;
	}
}



bool choiceWins(int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
	// (1) All opposition pieces eliminated
	// (2) All remaining opposition pieces cannot move.
	return (areAllOppositionPiecesEliminated(boardSizeUsed, oppositionPieces) || areAllOppositionPiecesTrapped(boardSizeUsed, playerPieces, oppositionPieces));
}

bool areAllOppositionPiecesEliminated(int boardSizeUsed, CheckersSquare oppositionPieces[][50])
{
	for (size_t i = 0; i < boardSizeUsed; i++)
	{
		for (size_t j = 0; j < boardSizeUsed; j++)
		{
			if (oppositionPieces[i][j] != Checkers_NotFilled)
			{
				return false;
			}
		}
	}
	return true;
}

bool areAllOppositionPiecesTrapped(int boardSizeUsed, CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50])
{
	for (size_t i = 0; i < boardSizeUsed; i++)
	{
		for (size_t j = 0; j < boardSizeUsed; j++)
		{
			if (oppositionPieces[i][j] != Checkers_NotFilled)
			{
				// Note that player/opposition parameters are switched in method call. This is because the next turn is being investigated.
				int boardPosition[2] = { i, j };
				if (!isPieceTrapped(boardPosition, oppositionPieces, playerPieces, boardSizeUsed))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool isPieceTrapped(int boardPosition[], CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], int boardSizeUsed)
{
	CheckersSquare playerPiece = playerPieces[boardPosition[0]][boardPosition[1]];
	CheckersPlayers player = getPlayer(playerPiece);
	bool isCurrentPieceKing = isPieceKing(playerPiece);

	int maxEnum = 2;
	if (isCurrentPieceKing) { maxEnum = 4; }
	int tempMove[2];
	for (size_t i = 1; i <= maxEnum; i++)
	{
		getMoveOffset(player, static_cast<CheckersMoves>(i), tempMove);
		if (moveIsValid(boardPosition, tempMove, boardSizeUsed, playerPieces, oppositionPieces)) { return false; }
	}

	return true;
}

bool pieceCanJumpNeighboringPiece(int boardPosition[], CheckersSquare playerPieces[][50], CheckersSquare oppositionPieces[][50], int boardSizeUsed)
{
	CheckersSquare playerPiece = playerPieces[boardPosition[0]][boardPosition[1]];
	CheckersPlayers player = getPlayer(playerPiece);
	bool isCurrentPieceKing = isPieceKing(playerPiece);

	int maxEnum = 2;
	if (isCurrentPieceKing) { maxEnum = 4; }
	int tempMove[2];
	for (size_t i = 1; i <= maxEnum; i++)
	{
		getMoveOffset(player, static_cast<CheckersMoves>(i), tempMove);

		// (1) Is there a neighboring opposition piece
		CheckersSquare oppositionPiece = oppositionPieces[boardPosition[0] + tempMove[0]][boardPosition[1] + tempMove[1]];
		if (oppositionPiece == Checkers_NotFilled) { return false; }

		// (2) Can the opposition piece be jumped?
		if (moveIsValid(boardPosition, tempMove, boardSizeUsed, playerPieces, oppositionPieces)) { return true; }
	}

	return false;
}



string translateEnumToString(CheckersSquare squareState)
{
	switch (squareState)
	{
	case Checkers_Filled:
		return " ";
	case Checkers_NotFilled:
		return " ";
	case Checkers_SinglePiece_Red:
		return "x";
	case Checkers_KingPiece_Red:
		return "X";
	case Checkers_SinglePiece_Black:
		return "o";
	case Checkers_KingPiece_Black:
		return "O";
	default:
		return "~";
	}
}

string translateEnumToString(CheckersPlayers squareState)
{
	switch (squareState)
	{
	case CheckersPlayers_Black:
		return "O";
	case CheckersPlayers_Red:
		return "X";
	default:
		return "[Unknown Player]";
	}
}

bool isEven(int number)
{
	return (number % 2 == 0);
}

bool isOdd(int number)
{
	return !isEven(number);
}

bool isValidSquare(int row, int column)
{
	return ((isEven(row) && isOdd(column)) ||
			(isOdd(row) && isEven(column)));
}