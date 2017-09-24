#include <iostream>
#include "constructor.h"

using namespace std;

int main()
{
	// 3 ways of intializing the object:

	// 1. Default constructor
	ChessBoard board1;

	// 2. Constructor with parameters
	ChessBoard board2(8);

	// 3. Pointer
	ChessBoard* board3 = new ChessBoard();

}