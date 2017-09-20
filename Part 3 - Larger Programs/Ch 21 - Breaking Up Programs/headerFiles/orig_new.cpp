#include <iostream>
#include "linkedList.h" // Never include a *.cpp file directly. This leads to copies of functions and loses the time-saving benefits of separate compilation.

using namespace std;

int main()
{
	Node* list = nullptr;
	for (int i = 0; i < 10; ++i)
	{
		int value;
		cout << "Enter value for list node: ";
		cin >> value;
		list = addNode(list, value);
	}
	printList(list);
}