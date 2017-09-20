//#include <iostream>
//
//using namespace std;
//
//struct Node
//{
//	Node* next;
//	int value;
//};
//
//Node* addNode(Node*  list, int value)
//{
//	Node* newNode = new Node;
//	newNode->value = value;
//	newNode->next = list;
//
//	return newNode;
//}
//
//void printList(const Node* list)
//{
//	const Node* currentNode = list;
//	while (currentNode)
//	{
//		cout << currentNode->value << endl;
//		currentNode = currentNode->next;
//	}
//}
//
//int main()
//{
//	Node* list = nullptr;
//	for (int i = 0; i < 10; ++i)
//	{
//		int value;
//		cout << "Enter value for list node: ";
//		cin >> value;
//		list = addNode(list, value);
//	}
//	printList(list);
//}