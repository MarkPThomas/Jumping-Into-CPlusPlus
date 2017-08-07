#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

enum Direction
{
	North,
	South,
	East,
	West
};

struct Position
{
	int row;
	int column;
};

struct Cell
{
	enum Wall
	{
		Wall_North = 0x0008,
		Wall_South = 0x0002,
		Wall_East = 0x0004,
		Wall_West = 0x0001,
		Wall_All = 0x000f,
		Wall_None = 0x0000
	};
	
	struct Position position;
	int walls;
	bool visited;
	
	int getWalls() const { return walls & Wall_All; }
	void setWalls(const int w) { walls = w & Wall_All; }
	void removeWall(const int w) {
		if (w != Wall_North && w != Wall_East && w != Wall_South && w != Wall_West)
		{
			return;
		}
		walls &= ~w;
	}


	string print() const
	{
		string cell = "";
		// Draw vertical wall.
		if ((getWalls() & Wall_West) != 0)
		{
			cell += '|';
		}
		else
		{
			cell += " ";
		}

		// Draw horizontal wall.
		if ((getWalls() & Wall_South) != 0)
		{
			cell += '_';
		}
		else
		{
			cell += " ";
		}
		return cell;
	}
};

struct VectorCell
{
	Cell* array = nullptr;
	int size = 0;

	bool isEmpty() const
	{
		return (size == 0);
	}
	
	void clear()
	{
		size = 0;
		if (array)
		{
			delete[] array;
			array = nullptr;
		}
	}

	/// <summary>
	/// Adds element to the back of the array.
	/// </summary>
	void pushBack(Cell *cell)
	{
		Cell* p_newvalues = new Cell[size + 1];

		// Copy values over
		for (int i = 0; i < size; i++)
		{
			p_newvalues[i] = array[i];
		}
		// Add new value to the end of the list
		p_newvalues[size] = *cell;

		// Free & reassign array
		if (array)
		{
			delete[] array;
			array = nullptr;
		}
		array = p_newvalues;
		size++;
	}

	/// <summary>
	/// Pop the top item from the stack.
	/// </summary>
	void popBack()
	{
		if (size == 1)
		{
			clear();
		}
		else
		{
			size--;
			Cell* p_newvalues = new Cell[size];
			// Copy values over, except the last one
			for (int i = 0; i < size; i++)
			{
				p_newvalues[i] = array[i];
			}

			// Free & reassign array
			if (array)
			{
				delete[] array;
				array = nullptr;
			}
			array = p_newvalues;
		}
	}
};

struct VectorDirection
{
	Direction* array = nullptr;
	int size = 0;

	bool isEmpty() const
	{
		return (size == 0);
	}

	void clear()
	{
		size = 0;
		if (array)
		{
			delete[] array;
			array = nullptr;
		}
	}

	/// <summary>
	/// Adds element to the back of the array.
	/// </summary>
	void pushBack(Direction direction)
	{
		Direction* p_newvalues = new Direction[size + 1];
		// Copy values over
		for (int i = 0; i < size; i++)
		{
			p_newvalues[i] = array[i];
		}
		// Add new value to the end of the list
		p_newvalues[size] = direction;

		// Free & reassign array
		if (array)
		{
			delete[] array;
			array = nullptr;
		}
		array = p_newvalues;
		size++;
	}

	/// <summary>
	/// Pop the top item from the stack.
	/// </summary>
	void popBack()
	{
		if (size == 1)
		{
			clear();
		}
		else
		{
			size--;
			Direction* p_newvalues = new Direction[size];
			// Copy values over, except the last one
			for (int i = 0; i < size; i++)
			{
				p_newvalues[i] = array[i];
			}

			// Free & reassign array
			if (array)
			{
				delete[] array;
				array = nullptr;
			}
			array = p_newvalues;
		}
	}
};

int main()
{	
	// Randomize the random number function
	srand(time(nullptr));

	int mazeWidth = 10;
	int mazeHeight = 10;
	

	do
	{
		mazeWidth = 10;
		mazeHeight = 10;
		cout << "Please specify the dimensions of the maze (at least 10x10):\n";
		cout << "Width: ";
		cin >> mazeWidth;
		cout << "Height: ";
		cin >> mazeHeight;
		cout << '\n';
	}
	while ((mazeWidth < 10) || (mazeHeight < 10));

	// Create 2-D array of cell objects
	Cell** maze = new Cell*[mazeWidth];
	for (int i = 0; i < mazeWidth; i++)
	{
		maze[i] = new Cell[mazeHeight];
	}

	// Set all cell initial properties
	for (int row = 0; row < mazeHeight; row++)
	{
		for (int column= 0; column < mazeWidth; column++)
		{
			maze[column][row].visited = false;
			maze[column][row].position.row = row;
			maze[column][row].position.column = column;
			maze[column][row].setWalls(Cell::Wall_All);
		}
	}


	// Set a random position in the maze
	int currentRow = rand() % mazeHeight;
	int currentColumn = rand() % mazeWidth;

	// Create a vector of Cell structs which will be used as a stack.
	VectorCell trail;

	// Grab the Cell at the currentColumn, currentRow position and push it on the trail stack.
	trail.pushBack(&maze[currentColumn][currentRow]);


	// Create a vector of direction values named live.
	VectorDirection currentDirections;

	// While the trail stack is not empty do the following:
	while (!trail.isEmpty()) { // stay in here till display
									 // Empty the live vector.
		currentDirections.clear();
		// Check the neighbors of the current cell to the north, east, south, and west.
		// If any of the neighbors have all four walls, add the direction to that 
		// neighbor to the live vector.
		if (currentColumn)
		{
			if (maze[currentColumn - 1][currentRow].getWalls() == Cell::Wall_All) // West has all walls
			{
				currentDirections.pushBack(West);
			}
		}
			
		if (currentColumn < mazeWidth - 1)
		{
			if (maze[currentColumn + 1][currentRow].getWalls() == Cell::Wall_All) // East has all walls
			{
				currentDirections.pushBack(East);
			}
		}

		if (currentRow)
		{
			if (maze[currentColumn][currentRow - 1].getWalls() == Cell::Wall_All) // North has all walls
				
			{
				currentDirections.pushBack(North);
			}
		}

		if (currentRow < mazeHeight - 1)
		{
			if (maze[currentColumn][currentRow + 1].getWalls() == Cell::Wall_All) // South has all walls
			{
				currentDirections.pushBack(South);
			}
		}

		if (!currentDirections.isEmpty()) 
		{
			// Choose one of the directions in the live vector at random
			int randomDirectionIndex = rand() % currentDirections.size;

			// Remove the walls between the current cell and the neighbor in that direction
			// and Change currentRow and currentColumn to refer to the neighbor
			maze[currentColumn][currentRow].visited = true;
			switch (currentDirections.array[randomDirectionIndex])
			{
			case 0:
				maze[currentColumn][currentRow].removeWall(Cell::Wall_North);
				maze[currentColumn][--currentRow].removeWall(Cell::Wall_South);
				break;
			case 1:
				maze[currentColumn][currentRow].removeWall(Cell::Wall_South);
				maze[currentColumn][++currentRow].removeWall(Cell::Wall_North);
				break;
			case 2:
				maze[currentColumn][currentRow].removeWall(Cell::Wall_East);
				maze[++currentColumn][currentRow].removeWall(Cell::Wall_West);
				break;
			case 3:
				maze[currentColumn][currentRow].removeWall(Cell::Wall_West);
				maze[--currentColumn][currentRow].removeWall(Cell::Wall_East);
				break;
			default:
				break;
			}

			// Push the new current cell onto the trail stack
			trail.pushBack(&maze[currentColumn][currentRow]);
		} 
		else 
		{
			// Pop the top item from the trail stack
			trail.popBack();

			// If the trail stack is not empty, set curX and curY to refer to the 
			// position of the top item in the trail stack.
			if (!trail.isEmpty()) 
			{
				currentRow = trail.array[0].position.row;
				currentColumn = trail.array[0].position.column;
			}
		}
	}

	// Print the maze
	// Top bar
	for (int column = 0; column < mazeWidth; column++)
	{
		if (column == 0)
		{
			cout << " _";
		}
		else
		{
			cout << "__";
		}
	}
	cout << '\n';
	// Print Maze
	for (int row = 0; row < mazeHeight; row++)
	{
		for (int column = 0; column < mazeWidth; column++)
		{
			cout << maze[column][row].print();
		}
		cout << "|\n";
	}

}
