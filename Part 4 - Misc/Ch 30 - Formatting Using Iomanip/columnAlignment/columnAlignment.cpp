#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person
{
	Person (const string& firstName,
			const string& lastName) : _firstName(firstName),
									  _lastName(lastName)
	{
		
	}

	string _firstName;
	string _lastName;
};

int main()
{
	vector<Person> people;
	people.push_back(Person("Joe", "Smith"));
	people.push_back(Person("Tonya", "Malligans"));
	people.push_back(Person("Jerome", "Noboggins"));
	people.push_back(Person("Mary", "Suzie-Purple"));

	// Get the max widths
	int firstNameMaxWidth = 0;
	int lastNameMaxWidth = 0;
	for(vector<Person>::iterator itr = people.begin(), end = people.end();
		itr != end;
		++itr)
	{
		if (itr->_firstName.length() > firstNameMaxWidth)
		{
			firstNameMaxWidth = itr->_firstName.length();
		}
		if (itr->_lastName.length() > lastNameMaxWidth)
		{
			lastNameMaxWidth = itr->_lastName.length();
		}
	}

	// Print the elements of the vector
	for (vector<Person>::iterator itr = people.begin(), end = people.end();
		itr != end;
		++itr)
	{
		cout << setw(firstNameMaxWidth + 2) << left << itr->_firstName;
		cout << setw(lastNameMaxWidth + 2) << left << itr->_lastName;
		cout << endl;
	}
}