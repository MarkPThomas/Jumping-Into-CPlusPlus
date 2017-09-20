#include <iostream>
#include <string>
#include <map>

using namespace std;

// Map is copied! 
void displayMap(map<string, string> mapToPrint)
{
	for (map<string, string>::iterator itr = mapToPrint.begin(), end = mapToPrint.end(); itr != end; ++itr)
	{
		cout << itr->first << " --> " << itr->second << endl;
	}
}

// Map is referenced and is read only.
// Note that const_iterator must be used on the parameter now.
void displayMapConst(const map<string, string>& mapToPrint)
{
	for (map<string, string>::const_iterator itr = mapToPrint.begin(), end = mapToPrint.end(); itr != end; ++itr)
	{
		cout << itr->first << " --> " << itr->second << endl;
	}
}

void fun(int x)
{
	
}

void funConst(const int& x)
{
	
}

int main()
{
	map<string, string> mapToPrint;
	mapToPrint["Foo"] = "Bar";
	mapToPrint["Mark"] = "Thomas";
	mapToPrint["Fie"] = "Fei";
	mapToPrint["Foe"] = "Fum";

	displayMap(mapToPrint);
	cout << '\n';
	displayMapConst(mapToPrint);
}