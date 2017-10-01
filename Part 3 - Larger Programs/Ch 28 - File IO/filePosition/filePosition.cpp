#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	fstream file(
		"highScores.txt",
		ios::in | ios::out
			);

	if(!file.is_open())
	{
		cout << "Could not open file!" << '\n';
		return 0;
	}

	int newHighScore;
	cout << "Enter a new high score: ";
	cin >> newHighScore;

	// The while loop below searches the file until it finds a value less than the current high score.
	// At this point, we know we want to insert our high score right before that value.
	// To make sure that we know the right position, we keep track of the position prior to the current score.
	// The preScorePosition
	streampos preScorePosition = file.tellg();
	int currentScore;
	while (file >> currentScore)
	{
		if (currentScore < newHighScore)
		{
			break;
		}
		preScorePosition = file.tellg();
	}

	// If fail is true, and we aren't at EOF, there was some bad input.
	if (file.fail() && !file.eof())
	{
		cout << "Bad score/read--exiting...\n";
		return 0;
	}

	// Without calling clear, we won't be able to write to the file if we hit EOF.
	file.clear();

	// Return to the point right before the last score we read, for reading so that we can
	//    read in all of the scores that are less than our high score, and move them one
	//    position later in the file.
	file.seekg(preScorePosition);

	// Now we will read in all the scores, starting with the one we previously read in.
	vector<int> scores;
	while (file >> currentScore)
	{
		scores.push_back(currentScore);
	}

	// We expect to reach the end of the file via this read loop, 
	//    because we want to read in all scores in the file.
	if (!file.eof())
	{
		cout << "Bad score/read--exiting...";
		return 0;
	}

	// Since we hit EOF, we need to clear the file again so that we can write to it.
	file.clear();

	// Seek back to the position we want to do our insert.
	file.seekp(preScorePosition);

	// If we are not writing to the beginning of the file, we need to include a newline.
	// The reason is that when a number is read in, it stops at the first whitespace,
	//    so the position we are at prior to writing is at the end of the number rather
	//    than at the start of the next line.
	if (preScorePosition != streampos(0))
	{
		file << endl;
	}

	// Write out our new high score.
	file << newHighScore << endl;

	// Loop through the rest of the scores, outputting all of them.
	for (vector<int>::iterator itr = scores.begin(), end = scores.end();
		itr != end;
			++itr)
	{
		file << *itr << endl;
	}
}
