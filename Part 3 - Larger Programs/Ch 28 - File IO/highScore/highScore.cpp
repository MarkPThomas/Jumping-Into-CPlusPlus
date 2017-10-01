#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string fileName = "highScores.txt";
	cout << "Reading file " << fileName << '\n';
	ifstream fileReader(fileName);
	if (!fileReader.is_open())
	{
		cout << "Could not open file!" << '\n';
	}
	else
	{
		cout << "File is opened!\n";
	}

	cout << "Reading file...\n";
	vector<int> scores;
	for (int i = 0; i < 10; i++)
	{
		int score;
		if (fileReader >> score)
		{
			scores.push_back(score);
		}
	}
	cout << "File contents are: \n";
	for(vector<int>::iterator itr = scores.begin(), end = scores.end();
		itr != end;
			++itr)
	{
		cout << *itr << '\n';
	}
}