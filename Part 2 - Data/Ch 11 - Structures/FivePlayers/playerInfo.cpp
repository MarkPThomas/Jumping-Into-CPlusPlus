#include <iostream>
#include  <string>

using namespace std;

struct PlayerInfo
{
	int skillLevel;
	string name;
};

int main()
{
	PlayerInfo players[5];
	for (size_t i = 0; i < 5; i++)
	{
		cout << "Please enter the name for player: "
			<< i << '\n';
		// First access the element of the array, using norma array syntax;
		// then access the field of the struture using the '.' syntax
		cin >> players[i].name;
		cout << "Please enter the skill level for " << players[i].name << '\n';
		cin >> players[i].skillLevel;
	}
	for (size_t i = 0; i < 5; i++)
	{
		cout << players[i].name << " is at skill level " << players[i].skillLevel << '\n';
	}
}