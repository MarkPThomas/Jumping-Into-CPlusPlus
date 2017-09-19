#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

void printScores(map<string, int>& scores);
void getMapKeysUnsorted(map<string, int>& myMap, string nodeKeys[], int currentIndex = 0);
map<string, int>& addNewScore(map<string, int>& scores);
map<string, int>& updateScore(map<string, int>& scores);

const int maxNumberOfScores = 100;

int main()
{
	int choice = 0;
	bool exitProgram = false;
	int numberOfScores = 0;
	map<string, int> scores;

	while (!exitProgram)
	{
		numberOfScores = scores.size();
		cout << "Select from the following options:\n";
		cout << "0. Exit\n";
		cout << "1. Add new score\n";
		if (numberOfScores > 0)
		{
			cout << "2. Modify existing score\n";
		}
		cin >> choice;

		switch (choice)
		{
			case 0:
				exitProgram = true;
				break;
			case 1:
				scores = addNewScore(scores);
				printScores(scores);
				break;
			case 2:
				scores = updateScore(scores);
				printScores(scores);
				break;
			default:
				exitProgram = true;
				break;
		}
	}
}

map<string, int>& addNewScore(map<string, int>& scores)
{
	string name = "";
	int score = 0;
	cin.ignore();
	
	do
	{
		name = "";
		cout << "Please enter a new name and score to add:\n";
		cout << "Name:\n";
		getline(cin, name, '\n');
		if (name == "") { break; }

		// Check that the name does not exist
		if (scores.find(name) != scores.end())
		{
			cout << "That entry already exists. \n";
			cout << "Please enter a new name to add a score for.\n";
			continue;
		}

		score = 0;
		cout << '\n';
		cout << "Score: ";
		cin >> score;
		cout << "\n\n";
		cin.ignore();

		scores[name] = score;
	} while (name != "");
	return scores;
}

map<string, int>& updateScore(map<string, int>& scores)
{
	string name = "";
	int score = 0;
	cin.ignore();

	do
	{
		name = "";
		cout << "Please enter a name to update the score for:\n";
		cout << "Name:\n";
		getline(cin, name, '\n');
		if (name == "") { break; }

		// Check that the name does not exist
		if (scores.find(name) == scores.end())
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to display.\n";
			continue;
		}

		score = 0;
		cout << '\n';
		cout << "Score: ";
		cin >> score;
		cout << "\n\n";
		cin.ignore();

		scores[name] = score;
	} while (name != "");
	return scores;
}

// ==== Remove as this does not print the map in order. ====
//
//void printScores(map<string, int>& scores)
//{
//	cout << '\n';
//	cout << "High Scores\n";
//	cout << "===================\n";
//	for (map<string, int>::iterator itr = scores.begin(), end = scores.end(); itr != end; ++itr)
//	{
//		cout << itr->first << ": " << itr->second << "\n";
//	}
//	cout << '\n';
//}

void printScores(map<string, int>& scores)
{
	int numberOfScores = scores.size();
	if (numberOfScores == 0)
	{
		return;
	}

	string mapKeys[maxNumberOfScores];
	getMapKeysUnsorted(scores, mapKeys);

	// Get entries in ascending order
	string priorName = "";
	int priorScore = 0;
	vector<string> names;
	vector<string> nameScores;
	for (int i = 0; i < numberOfScores; i++)
	{
		// Set current name to prior name, or first name if this is the first iteration.
		string currentName;
		int currentScore = 0;
		priorName == "" ? currentName = mapKeys[0] : currentName = priorName;
		priorName == "" ? currentScore = scores[mapKeys[0]] : currentScore = priorScore;

		// Get next name in order of score
		for (int index = 0; index < numberOfScores; index++)
		{
			// Skip this index if the name already exists in the tracking list
			if (find(names.begin(), names.end(), mapKeys[index]) != names.end())
			{
				continue;
			}

			if ((scores[mapKeys[index]] >= priorScore) &&
				((currentName == priorName) ||
				 ((scores[mapKeys[index]] <= currentScore))))
			{
				currentScore = scores[mapKeys[index]];
				currentName = mapKeys[index];
			}
		}
		names.push_back(currentName);
		nameScores.push_back(currentName + ": " + to_string(currentScore));

		priorName = currentName;
		priorScore = currentScore;
	}

	// Print entries in descending score order
	cout << '\n';
	cout << "High Scores\n";
	cout << "===========\n\n";
	for (vector<string>::reverse_iterator ritr = nameScores.rbegin(), end = nameScores.rend(); ritr != end; ++ritr)
	{
		cout << *ritr << '\n';
	}
	cout << "===========\n\n";
}

void getMapKeysUnsorted(map<string, int>& myMap, string nodeKeys[], int currentIndex)
{
	for (map<string, int>::iterator itr = myMap.begin(), end = myMap.end(); itr != end; ++itr) {
		nodeKeys[currentIndex] = itr->first;
		currentIndex++;
	}
}
