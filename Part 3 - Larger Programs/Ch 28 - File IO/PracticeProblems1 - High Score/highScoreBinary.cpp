#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> readBinaryFile(string fileName);
vector<int> readTextFile(string fileName);
int writeBinaryFile(string fileName, const vector<int>& scores);
int writeTextFile(string fileName, const vector<int>& scores);
int insertFile(string fileName);
void print(const vector<int>& scores);

int main()
{
	string fileName = "highScores";
	// 1. Write basic file
	cout << "Writing base file " << fileName << '\n';
	vector<int> scores 
	{ 
		1000,
		987,
		864,
		766,
		744,
		500,
		453,
		321,
		201,
		98,
		5 
	};
	writeTextFile(fileName, scores);
	writeBinaryFile(fileName, scores);
	readBinaryFile(fileName);
	print(scores);

	// 2. Read file in for insert
	if (insertFile(fileName) != 0)
	{
		cout << "Error inserting into file. Program will exit...\n";
		return 1;
	}

	// 3. Validate by reading file back in and writing a readable text file.
	vector<int> newScores = readBinaryFile(fileName);
	//vector<int> newScores;
	//newScores = readBinaryFile(fileName);
	writeTextFile(fileName, newScores);
	print(newScores);
}

vector<int> readBinaryFile(string fileName)
{
	cout << "Opening binary file " << fileName << '\n';
	ifstream aFile(fileName + ".bin",
		ios::binary);
	if (!aFile.is_open())
	{
		cout << "Could not open file!" << '\n';
	}
	else
	{
		cout << "File is opened!\n";
	}

	cout << "Reading file...\n";
	
	int numberOfScores;
	if(!aFile.read(
		reinterpret_cast<char*>(&numberOfScores),
		sizeof(numberOfScores)
		))
	{
		cout << "Error reading from file." << endl;
		vector<int> scoresEmpty;
		return scoresEmpty;
	}
	
	vector<int> scores(numberOfScores);
	aFile.read(
		reinterpret_cast<char*>(&scores[0]),
		numberOfScores * sizeof(int)
	);

	return scores;
}

vector<int> readTextFile(string fileName)
{
	cout << "Opening text file " << fileName << '\n';
	ifstream fileReader(fileName + ".txt");
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
	int score;
	while (fileReader >> score)
	{
		scores.push_back(score);
	}

	return scores;
}

int writeBinaryFile(string fileName, const vector<int>& scores)
{
	cout << "Writing file to binary format..." << '\n';
	ofstream aFile(fileName + ".bin",
		ios::trunc | ios::binary );
	if (!aFile.is_open())
	{
		cout << "Could not open file!" << '\n';
		return 1;
	}

	int numberOfScores = scores.size();
	if (!aFile.write(
		reinterpret_cast<char*>(&numberOfScores),
		sizeof(numberOfScores)
		))
	{
		{
			cout << "Error writing to file." << endl;
			vector<int> scoresEmpty;
			return 1;
		}
	}
	aFile.write(
		reinterpret_cast<const char*>(&scores[0]),
		numberOfScores * sizeof(int)
	);

	return 0;
}

int writeTextFile(string fileName, const vector<int>& scores)
{
	cout << "Writing file to text format..." << '\n';
	ofstream fileWriter(fileName +".txt");
	if (!fileWriter.is_open())
	{
		cout << "Could not open file!" << '\n';
		return 1;
	}

	for (vector<int>::const_iterator itr = scores.begin(), end = scores.end();
		itr != end;
		++itr)
	{
		fileWriter << *itr << '\n';
	}
	return 0;
}

int insertFile(string fileName)
{
	cout << "Inserting data into file..." << '\n';
	fstream aFile(fileName + ".bin",
		ios::binary | ios::out | ios::in);

	if (!aFile.is_open())
	{
		cout << "Could not open file!" << '\n';
		return 1;
	}

	int newHighScore;
	cout << "Enter a new high score: ";
	cin >> newHighScore;

	// The while loop below searches the file until it finds a value less than the current high score.
	// At this point, we know we want to insert our high score right before that value.
	// To make sure that we know the right position, we keep track of the position prior to the current score.
	// The preScorePosition
	streampos preScorePosition = aFile.tellg();
	int numberOfScores;
	if (!aFile.read(
		reinterpret_cast<char*>(&numberOfScores),
		sizeof(numberOfScores)
	))
	{
		cout << "Error reading from file." << endl;
		vector<int> scoresEmpty;
		return 1;
	}
	int currentScore = 0;
	while (aFile.read(
		reinterpret_cast<char*>(&currentScore),
		sizeof(currentScore)))
	{
		if (currentScore < newHighScore)
		{
			break;
		}
		preScorePosition = aFile.tellg();
	}

	// If fail is true, and we aren't at EOF, there was some bad input.
	if (aFile.fail() && !aFile.eof())
	{
		cout << "Bad score/read--exiting...\n";
		return 1;
	}

	// Without calling clear, we won't be able to write to the file if we hit EOF.
	aFile.clear();

	// Return to the point right before the last score we read, for reading so that we can
	//    read in all of the scores that are less than our high score, and move them one
	//    position later in the file.
	aFile.seekg(preScorePosition);

	// Now we will read in all the scores, starting with the one we previously read in.
	vector<int> scores;
	while (aFile.read(
		reinterpret_cast<char*>(&currentScore),
		sizeof(currentScore)))
	{
		scores.push_back(currentScore);
	}

	// We expect to reach the end of the file via this read loop, 
	//    because we want to read in all scores in the file.
	if (!aFile.eof())
	{
		cout << "Bad score/read--exiting...";
		return 1;
	}

	// Since we hit EOF, we need to clear the file again so that we can write to it.
	aFile.clear();

	// Seek back to the position we want to do our insert.
	aFile.seekp(preScorePosition);

	// Write out our new high score.
	aFile.write(
		reinterpret_cast<char*>(&newHighScore),
		sizeof(newHighScore));

	// Loop through the rest of the scores, outputting all of them.
	aFile.write(
		reinterpret_cast<char*>(&scores[0]),
		scores.size() * sizeof(int)
	);

	// Update the number of scores at the top of the file
	numberOfScores++;
	aFile.seekp(0, ios_base::beg);
	if (!aFile.write(
		reinterpret_cast<char*>(&numberOfScores),
		sizeof(numberOfScores)
	))
	{
		{
			cout << "Error writing to file." << endl;
			vector<int> scoresEmpty;
			return 1;
		}
	}

	return 0;
}

void print(const vector<int>& scores)
{

	cout << "File contents are: \n";
	for (vector<int>::const_iterator itr = scores.begin(), end = scores.end();
		itr != end;
		++itr)
	{
		cout << *itr << '\n';
	}
}