#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace  std;

struct EnemySpaceShip
{
	int xCoordinate;
	int yCoordinate;
	int weaponPower;
	int shipID;
	EnemySpaceShip* p_nextEnemy;
};

void printShips(EnemySpaceShip* p_enemies);
EnemySpaceShip* addNewEnemyToList(EnemySpaceShip* p_list, int shipID);
void updgradeWeapons(EnemySpaceShip* p_ship);

int main()
{
	// Randomize the random number function
	srand(time(nullptr));

	// Create a linked list of 10 enemy shups
	EnemySpaceShip* p_enemies = nullptr;
	for (int i = 0; i < 10; i++)
	{
		p_enemies = addNewEnemyToList(p_enemies, i);
	}
	
	printShips(p_enemies);

	// Traverse the list to update all weapons
	EnemySpaceShip* p_current = p_enemies;
	while (p_current != nullptr)
	{
		updgradeWeapons(p_current);
		p_current = p_current->p_nextEnemy;
	}
	printShips(p_enemies);
}

EnemySpaceShip* addNewEnemyToList(EnemySpaceShip* p_list, int shipID)
{
	EnemySpaceShip* p_ship = new EnemySpaceShip;
	p_ship->xCoordinate = rand() % 100; // '->' is used instead of '.' for accessing fields through a pointer.
	p_ship->yCoordinate = rand() % 100;
	p_ship->weaponPower = rand() % 20;
	p_ship->shipID = shipID;
	p_ship->p_nextEnemy = p_list;
	return p_ship;
}

void updgradeWeapons(EnemySpaceShip* p_ship)
{
	p_ship->weaponPower += 10;
}


void printShips(EnemySpaceShip* p_enemies)
{
	cout << "Printing the list of enemy ships...\n";

	// Traverse the list to print the list
	EnemySpaceShip* p_current = p_enemies;
	while (p_current != nullptr)
	{
		cout << "Spaceship ID: " << p_current->shipID << '\n';
		cout << "Spaceship X Coordinate: " << p_current->xCoordinate << '\n';
		cout << "Spaceship Y Coordinate: " << p_current->yCoordinate << '\n';
		cout << "Spaceship Weapon Power: " << p_current->weaponPower << '\n';
		cout << '\n';
		p_current = p_current->p_nextEnemy;
	}
	cout << '\n';
}