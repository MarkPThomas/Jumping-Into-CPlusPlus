#include <iostream>
#include <string>

using namespace std;

void SingNinetyNineBottlesSong()
{
	for (size_t beer = 99; beer > 0; beer--)
	{
		if (beer != 99)
		{
			cout << beer << " bottles of beer on the wall.\n";
		}
		cout << beer << " bottles of beer on the wall, " << beer << " bottles of beer.\n" <<
			"Take one down, pass it around...\n";
	}
}

int logIn()
{
	string password = "guest";
	string userInput = "";
	int attemptLimit = 5;

	for (size_t attempts = 0; attempts < attemptLimit; attempts++)
	{
		if (attempts > 0)
		{
			cout << "You entered an incorrect password! \n" <<
				"Attempts remaining: " << attemptLimit - attempts << "\n";
		}
		cout << "Please enter your password" << "\n";
		cin >> userInput;
		if (userInput == password)
		{
			cout << "Congratulations! You have been granted access..." << "\n";
			return 0;
		}
	}
	cout << "Sadly we can't let you in. Goodbye :-( " << "\n";
	return 1;
}

string selectBeerChoice(string beerOptions[])
{
	string beerChoice = "";
	string message = "\n";
	for (size_t i = 0; i < sizeof(beerOptions); i++)
	{
		message += "\n\t" + beerOptions[i];
	}

	cout << "Please specify which type of beer you would like:" <<  message << "\n";
	//cin.clear();

	getline(cin, beerChoice, '\n');
	return beerChoice;
}

bool validBeerChoice(string beerChoice, string beerOptions[])
{
	bool isValid = false;
	for (size_t i = 0; i < sizeof(beerOptions); i++)
	{
		if(beerChoice == beerOptions[i])
		{
			isValid = true;
			break;
		}
	}
	return isValid;
}

int main()
{
	// Login to program
	if (logIn() == 1) { return 1; }
	
	// This is required to avoid the do loop from repeating twice. 
	// The data entered into the password trips the first loop, otherwise.
	cin.clear(); cin.ignore(INT_MAX, '\n'); 

	// Get beer
	string beerOptions[4] = { "Stout", "IPA", "Wheat Beer", "Ale" };
	string beerChoice = "";

	do
	{
		beerChoice = selectBeerChoice(beerOptions);
	} while (!validBeerChoice(beerChoice, beerOptions));

	cout << "Good choice!" << endl;

	// Sing about beer
	SingNinetyNineBottlesSong();
}