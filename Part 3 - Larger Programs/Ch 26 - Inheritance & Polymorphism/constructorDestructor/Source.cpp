#include <iostream>
#include <string>

using namespace std;

class FooSuperClass
{
public:
	FooSuperClass(const string& val)
	{
		cout << "FooSuperclass's constructor says: " << val << endl;
	}
};

class Foo : public FooSuperClass
{
public:
	Foo() : FooSuperClass("aaarg!")
	{
		cout << "Foo's constructor" << endl;
	}
	~Foo() { cout << "Foo's destructor" << endl; }
};

class Bar: public Foo
{
public:
	Bar() { cout << "Bar's constructor" << endl; }
	~Bar() { cout << "Bar's destructor" << endl; }
};

int main()
{
	Bar bar;
}