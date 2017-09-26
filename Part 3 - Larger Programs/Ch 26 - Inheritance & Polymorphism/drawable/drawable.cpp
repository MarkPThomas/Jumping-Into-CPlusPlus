#include <iostream>
#include "drawable.h"

using namespace std;

void Drawable::drawNonOverrridable()
{
	// Code to draw that is not overridable
	cout << "Drawable is drawing!\n";
}

void Drawable::drawOverridable()
{
	// Code to draw that is overridable
	cout << "Drawable is drawing!\n";
}