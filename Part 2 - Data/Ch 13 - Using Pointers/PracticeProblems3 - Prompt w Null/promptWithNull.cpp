#include <iostream>
#include <string>

using namespace std;

void getNameByPointer(string* firstName, string* lastName)
{
	cout << "Please enter your first name: ";
	cin >> *firstName;

	// Check for null
	if (!lastName || lastName->empty()) // can also be 'if(lastName == nullptr)
	{
		string tempLastName;
		cout << "Please enter your last name: ";
		cin >> tempLastName;

		// Note: This fails if lastName is null. 
		// I cannot find a way to assign to a null pointer that carries out of the method without using a double pointer or pointer reference, which are not yet introduced in the text.
		//*lastName = tempLastName;					// (1) Throws exception 'Read Access violations: std::_String_alloc<std::_String_base_types<char,std::allocator<char> > >::_Myres(...) returned 0x18'.
		// lastName = &tempLastName;				// (2) This assignment is limited to the method scope.
		// lastName = new string(tempLastName);		// (3) This assignment is limited to the method scope.
	}
}

void getNameByReference(string& firstName, string& lastName)
{
	cout << "Please enter your first name: ";
	cin >> firstName;

	if (lastName.empty()) // can also be 'if(lastName == nullptr)
	{
		cout << "Please enter your last name: ";
		cin >> lastName;
	}
}

int main()
{
	cout << "Calling pointer method with variables... \n";
	string firstName;
	string lastName;

	getNameByPointer(&firstName, &lastName);
	cout << "Your name is " << firstName << " " << lastName << '\n';
	cout << '\n';

	cout << "Calling pointer method with variable and null pointer...\n";
	string firstName1;				// Standard initialization
	string *lastName1 = nullptr;	// Null pointer

	getNameByPointer(&firstName1, lastName1); 
	if(lastName1)
	{
		cout << "Your name is " << firstName1 << " " << *lastName1 << '\n';
	}
	else
	{
		cout << "Your name is " << firstName1 << '\n';
	}
	cout << '\n';
	
	cout << "Calling pointer method with initialized pointer and null pointer...\n";
	string *firstName2 = &firstName;	// Note: Changing the value of firstName1 will also change the value of firstName.									
	string *lastName2 = nullptr;		// Null pointer

	getNameByPointer(firstName2, lastName2);
	if (lastName1)
	{
		cout << "Your name is " << *firstName2 << " " << *lastName2 << '\n';
	}
	else
	{
		cout << "Your name is " << *firstName2 << '\n';
	}
	cout << '\n';


	cout << "Calling reference method with variables... \n";
	string firstName3;
	string lastName3;

	getNameByReference(firstName3, lastName3);
	cout << "Your name is " << firstName3 << " " << lastName3 << '\n';
	cout << '\n';

	// The following will compile but results in a runtime error.
	// Null values cannot be passed into a reference parameter
	/*cout << "Calling reference method with variable and null pointer... \n";
	string firstName4;
	string lastName4 = nullptr;

	getNameByReference(firstName4, lastName4);
	cout << "Your name is " << firstName4 << " " << lastName4 << '\n';*/
}