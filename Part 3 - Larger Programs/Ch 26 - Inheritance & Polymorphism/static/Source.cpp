#include <iostream>

using namespace std;

class Node
{
public:
	Node();
private:
	static int _getNextSerialNumber();

	// Static. One copy for the whole class.
	static int _nextSerialNumber;

	// Non-static. Available to each object, but not to static methods.
	int _serialNumber;
};

int Node::_nextSerialNumber = 0;

Node::Node()
	: _serialNumber(_getNextSerialNumber())
{
	cout << _serialNumber << endl;
}

int Node::_getNextSerialNumber()
{
	// Use the postfix version of ++ to return the value that was previously in the variable.
	return _nextSerialNumber++;
}

int main()
{
	Node node;
	Node node1;
	Node node2;
}