#include <iostream>
#include <list>
#include "HighScoreElement.h"

using namespace std;

void print(const list<HighScoreElement*>& scores);
list<HighScoreElement*> sortDescending(const list<HighScoreElement*>& scores);
list<HighScoreElement*> sortAscending(const list<HighScoreElement*>& scores);
HighScoreElement* getMinElement(const list<HighScoreElement*>& scores);

int main()
{
	list<HighScoreElement*> scores;
	scores.push_back(new HighScoreElement("Mark", 666));
	scores.push_back(new HighScoreElement("Char", 999));
	scores.push_back(new HighScoreElement("Moe", 50));
	scores.push_back(new HighScoreElement("Foo", 123));
	scores.push_back(new HighScoreElement("Bar", 321));
	scores.push_back(new HighScoreElement("Gnar", 50));
	
	cout << "Creating score elements added out of order...\n";
	print(scores);

	cout << "Sorting score elements by descending score and by name\n";
	scores = sortDescending(scores);
	print(scores);

	cout << "Sorting score elements by ascending score and by name\n";
	scores = sortAscending(scores);
	print(scores);
}

list<HighScoreElement*> sortDescending(const list<HighScoreElement*>& scores)
{
	list<HighScoreElement*> sortedScores;
	list<HighScoreElement*> unsortedScores(scores);
	while (unsortedScores.size() != 0)
	{
		HighScoreElement* minElement = getMinElement(unsortedScores);
		sortedScores.push_front(minElement);
		unsortedScores.remove(minElement);
	}
	return sortedScores;
}

list<HighScoreElement*> sortAscending(const list<HighScoreElement*>& scores)
{
	list<HighScoreElement*> sortedScores;
	list<HighScoreElement*> unsortedScores(scores);
	while (unsortedScores.size() != 0)
	{
		HighScoreElement* minElement = getMinElement(unsortedScores);
		sortedScores.push_back(minElement);
		unsortedScores.remove(minElement);
	}
	return sortedScores;
}

HighScoreElement* getMinElement(const list<HighScoreElement*>& scores)
{
	HighScoreElement* minElement = nullptr;
	for (list<HighScoreElement*>::const_iterator itr = scores.begin(), end = scores.end();
		itr != end;
		++itr)
	{
		if (!minElement)
		{
			minElement = *itr;
		}
		else if ((*itr)->compare(*minElement) == -1)
		{
			minElement = *itr;
		}
		else if ((*itr)->compare(*minElement) == 0)
		{
			// No action taken;
			cout << "Error. High Score elements are identical! The current one will be skipped...\n";
		}
	}
	return minElement;
}

void print(const list<HighScoreElement*>& scores)
{
	for (list<HighScoreElement*>::const_iterator itr = scores.begin(), end = scores.end();
		itr != end; 
		++itr)
	{
		cout << (*itr)->getName() << ": " << (*itr)->getScore() << '\n';
	}
	cout << '\n';
}
