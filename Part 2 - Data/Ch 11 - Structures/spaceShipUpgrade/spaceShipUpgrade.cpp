#include <iostream>

using namespace std;

struct EnemySpaceShip
{
	int xCoordinate;
	int yCoordinate;
	int weaponPower;
};

EnemySpaceShip getNewEnemy()
{
	EnemySpaceShip ship;
	ship.xCoordinate = 0;
	ship.yCoordinate = 0;
	ship.weaponPower = 20;
	return ship;
}

EnemySpaceShip upgradeWeapons(EnemySpaceShip ship)
{
	ship.weaponPower += 10;
	return ship;
}

int main()
{
	EnemySpaceShip enemy = getNewEnemy();
	cout << "Weapon power: " << enemy.weaponPower << '\n';

	cout << "Upgrading space ship weapons...\n";

	enemy = upgradeWeapons(enemy);	
	cout << "Weapon power: " << enemy.weaponPower << '\n'; 
}
