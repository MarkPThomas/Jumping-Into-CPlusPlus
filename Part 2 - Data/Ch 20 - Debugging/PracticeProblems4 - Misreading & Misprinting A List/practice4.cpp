#include <iostream>

using namespace std;

struct Node
{
	int val;
	Node* next;
};

int main()
{
	int val;
	//Node* head; // This is a bug. The pointed should be initialized to null before any potential use.
	Node* head = nullptr;
	while (true)
	{
		cout << "Enter a value, 0 to replay: " << endl;
		cin >> val;
		//if (val = 0) //This is a bug. val is being assigned rather than compared, so the loop can never be exited.
		if (val == 0)  
		{
			cout << '\n';
			break;
		}

		Node* temp = new Node;
		//temp = head; // This is a bug. Property 'next' should be used here.
		temp->next = head;
		temp->val = val;
		head = temp;
	}

	Node* itr = head;
	while (itr)
	{
		cout << itr->val << endl;
		itr = itr->next;
		//delete itr; // This is a bug. This value is still used in the loop, so deleting it will cause problems with 'while(itr)'.
	}
	// This fixes the bug. This only needs to be deleted once, outside the loop, since it is defined outside the loop.
	delete itr;
}