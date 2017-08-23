// This header is needed for NULL; normally it's included by other header files, 
// but we don't need any other headers here
#include <cstddef>

struct EnemySpaceShip
{
	int xCoordinate;
	int yCoordinate;
	int weaponPower;
	EnemySpaceShip* p_nextEnemy;
};

EnemySpaceShip* p_enemies = nullptr;

EnemySpaceShip* getNewEnemy()
{
	EnemySpaceShip* p_ship = new EnemySpaceShip;
	p_ship->xCoordinate = 0; // '->' is used instead of '.' for accessing fields through a pointer.
	p_ship->yCoordinate = 0;
	p_ship->weaponPower = 20;
	p_ship->p_nextEnemy = p_enemies;
	p_enemies = p_ship;
	return p_ship;
}

void updgradeWeapons(EnemySpaceShip* p_ship)
{
	p_ship->weaponPower += 10;
}

int main()
{
	EnemySpaceShip* p_enemy = getNewEnemy();
	updgradeWeapons(p_enemy);
}