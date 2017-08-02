#include <iostream>
#include <string>

using namespace std;

struct User
{
	string name;
	int scores[50];

	int highScore()
	{
		int highScore = 0;
		for (size_t i = 0; i < 50; i++)
		{
			if (scores[i] > highScore) { highScore = scores[i]; }
		}
		return highScore;
	}
};

void listUsers(User users[], int numberOfUsers);
void allScores(User user);
void allScores(User users[], int numberOfUsers);
void allScoresFromSpecifiedUser(User users[], int numberOfUsers);
void highestScores(User users[], int numberOfUsers);

int main()
{
	User users[50];
	int usersAdded = 0;

	for (size_t i = 0; i < 50; i++)
	{
		string result;
		cout << "Please enter your name: \n";
		getline(cin, users[i].name, '\n');

		cout << "Enter scores. Enter 0 to stop.\n";
		for (size_t j = 0; j < 50; j++)
		{
			cout << "Score: ";
			cin >> users[i].scores[j];
			if (users[i].scores[j] <= 0) { break; }
		}
		
		usersAdded++;
		cout << "Would you like to enter scores for another user? (Y/N)\n";
		cin >> result;
		if (result == "N") { break; }

		cout << '\n';
		cin.ignore();
		cin.clear();
	}
	cout << '\n';
	cout << '\n';

	int option = 0;
	do
	{
		cout << "Please select from the following:\n";
		cout << "(1) Print names of all users\n";
		cout << "(2) Print the highest score from each user\n";
		cout << "(3) Print all scores from a specified user\n";
		cout << "(4) Print all scores from all users\n";
		cout << "(5) Exit\n";
		cout << "=========\n";
		cin >> option;
		cin.ignore();
		cin.clear();

		cout << "\n\n";
		switch (option)
		{
		case 1:
			listUsers(users, usersAdded);
			break;
		case 2:
			highestScores(users, usersAdded);
			break;
		case 3:
			allScoresFromSpecifiedUser(users, usersAdded);
			break;
		case 4:
			allScores(users, usersAdded);
			break;
		case 5:
			break;
		default:
			; // Repeat prompt
		}
	}
	while (option != 5);
}

void allScoresFromSpecifiedUser(User users[], int numberOfUsers)
{
	cout << "Users:\n";
	int choice = -1;
	for (size_t i = 0; i < numberOfUsers; i++)
	{
		cout << '(' << i << ") " << users[i].name << '\n';
		cout << "______\n";
	}
	do
	{
		cout << "Please choose the user by number to print all scores for.\n";
		cin >> choice;
	}
	while (choice < 0 || numberOfUsers <= choice);
	
	cout << "\n\n";
	allScores(users[choice]); 
	cout << "\n\n";
}

void listUsers(User users[], int numberOfUsers)
{
	cout << "Users:\n";
	for (size_t i = 0; i < numberOfUsers; i++)
	{
		cout << users[i].name << '\n';
	}
	cout << "\n\n";
}

void highestScores(User users[], int numberOfUsers)
{
	cout << "Highest score for each user:\n";
	for (size_t i = 0; i < numberOfUsers; i++)
	{
		cout << users[i].name << ": " << users[i].highScore() << '\n';
	}
	cout << "\n\n";
}

void allScores(User users[], int numberOfUsers)
{
	cout << "All scores for all users:\n";
	for (size_t i = 0; i < numberOfUsers; i++)
	{
		allScores(users[i]);
	}
}

void allScores(User user)
{
	cout << "All scores for user " << user.name << ":\n";
	int scoreIndex = 0;
	do
	{
		int score = user.scores[scoreIndex];
		if (score <= 0) { break; }
		cout << score << '\n';
		scoreIndex++;
	}
	while (true);
	cout << "\n\n";
}