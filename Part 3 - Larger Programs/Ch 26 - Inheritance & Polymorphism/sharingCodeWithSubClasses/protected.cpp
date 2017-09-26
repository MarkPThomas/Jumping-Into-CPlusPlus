#include <iostream>

using namespace std;

class Drawable
{
public:
	virtual void draw();
	virtual ~Drawable();
protected:
	void clearRegion(int x1, int y1, int x2, int y2);
};

Drawable::~Drawable()
{
	
}


void Drawable::clearRegion(int x1, int y1, int x2, int y2)
{
	cout << "Clear Region, a protected method, has been called.\n";
}

void Drawable::draw()
{
	cout << "Drawable:\n";
	clearRegion(2, 4, 5, 8);
	cout << '\n';
}

class MyDrawable : public Drawable
{
public:
	virtual void draw();
};

void MyDrawable::draw()
{
	cout << "MyDrawable:\n";
	clearRegion(2, 4, 5, 8);
	cout << '\n';
}

int main()
{
	Drawable drawable;
	//drawable.clearRegion(2, 4, 5, 8); // Member is inaccessible
	drawable.draw();

	MyDrawable myDrawable;
	//myDrawable.clearRegion(2, 4, 5, 8);// Member is inaccessible
	myDrawable.draw();
}