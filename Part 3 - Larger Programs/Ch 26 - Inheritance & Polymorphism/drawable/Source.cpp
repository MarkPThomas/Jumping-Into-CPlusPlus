#include <iostream>
#include <vector>
#include "drawable.h"
#include "ship.h"
#include "enemy.h"

using namespace std;

int main()
{
	Ship s;
	cout << "Calling methods on Ship:\n";
	s.drawNonOverrridable();
	s.drawOverridable();
	s.draw();
	cout << '\n';

	// Vectors storing classes should always store them as pointers, in case later classes inherit from the base classe but become larger in memory.
	// By storing only the pointer, the size of all classes should remain the same.
	vector<Drawable*> drawables; 

	// Store Ship in the vector by creating a new Ship pointer.
	drawables.push_back(new Ship());
	drawables.push_back(new Enemy());

	cout << "Calling methods on vector<Drawable*>\n";
	for (vector<Drawable*>::iterator itr = drawables.begin(),
		end = drawables.end();
			itr != end;
				++itr)
	{
		(*itr)->drawNonOverrridable();
		(*itr)->drawOverridable();
		(*itr)->draw();
		cout << '\n';
	}
}