class Drawable
{
public:
	virtual void draw() = 0;
	virtual ~Drawable();
};

class MyDrawable : public Drawable
{
public:
	virtual void draw();
	MyDrawable();
	virtual ~MyDrawable();
private:
	int* _myData;
};

Drawable::~Drawable()
{
	// The superclass destructor should be made virtual since the class contains a virtual method.
}


MyDrawable::MyDrawable()
{
	_myData = new int;
}

MyDrawable::~MyDrawable()
{
	delete _myData;
}

void MyDrawable::draw()
{
	// Code to do the drawing.
}

void deleteDrawable(Drawable* drawable)
{
	delete drawable;
}

int main()
{
	deleteDrawable(new MyDrawable());
}
