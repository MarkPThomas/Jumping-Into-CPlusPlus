#include <iostream>
#include "ship.h"

using namespace std;

void Ship::drawOverridable()
{
	// Code to draw that is overriding
	cout << "Ship is drawing!\n";
}

void Ship::draw()
{
	// Code implementing the draw method that was inherited from 'drawable'.
	cout << "Ship is drawing!\n";
}

