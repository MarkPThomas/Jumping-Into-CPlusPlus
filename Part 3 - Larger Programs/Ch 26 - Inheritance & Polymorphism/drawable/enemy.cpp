#include <iostream>
#include "enemy.h"

using namespace std;

void Enemy::drawOverridable()
{
	// Code to draw that is overriding
	cout << "Enemy is drawing!\n";
}

void Enemy::draw()
{
	// Code implementing the draw method that was inherited from 'drawable'.
	cout << "Enemy is drawing!\n";
}

