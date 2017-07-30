#include <iostream>
#include <string>
#include <locale>

using namespace std;

// ===== Pattern check and strategy =====
// Nine hundred and ninety nine thousand, nine hundred and ninety nine

// 999,999,999
// Nine hundred and ninety nine million, nine hundred and ninety nine thousand, nine hundred and ninety nine
// Nine hundred, ninety nine million, nine hundred, ninety nine thousand, nine hundred ninety nine
// Nine hundred ninety nine million nine hundred ninety nine thousand nine hundred ninety nine

// 900,000,000
// Nine hundred million

// 900,000,001
// Nine hundred million and one
// Nine hundred million one

// 90,000,000
// Ninety million

// 9,000,000
// Nine million


// 20
// 2 - 0 = 2 vs. 1
// 21
// 2 - 1 = 1 vs. 0

// 20,000
// 2 - 3 = -1 + (1) = 0 vs. 1
// 21,000
// 2 - 4 = -2 + (1) = -1 vs. 0

// 20,000,000
// 2 - 6 = -4 + (2) = -2 vs. 1
// 21,000,000
// 2 - 7 = -5 + (2) = -3 vs. 0



// 200
// 2 - 0 = 2
// 201
// 2 - 1 = 1
// 210
// 2 - 2 = 0

// 500,000
// 2 - 3 = -1 + (1) = 0 vs. 2
// 501,000
// 2 - 4 = -2 + (1) = -1 vs. 1
// 520,000
// 2 - 5 = -3 + (1)  = -2 vs. 0

// 500,000,000
// 2 - 6 = -4 + (2) = -2 vs. 2
// 501,000,000
// 2 - 7 = -5 + (2) = -3 vs. 1
// 520,000,000
// 2 - 8 = -6 + (2)  = -4 vs. 0
// 520,100,000
// 2 - 8 = -6 + (2)  = -4 vs. 0

// 3
// Three
// 23
// Twenty three
// Twenty-three
// 20
// Twenty

// (0) Filter input:
//	(0a) Remove leading spaces
//  (0b) Remove ",", "-", and "and"
//	(0c) 
// (1) Divide text into chunks divided by trillion, billion, million, thousand
// (2) Break chunks into separate words
// (3) Cycle through words, last to first, matching to numbers

// Method signatures
bool isNegative(string number);

string wordsToNumbers(string word);
bool isTens(string word);
string getTens(string numberAsWord);
bool isHundreds(string word);
string getHundreds(string numberAsWord);
int getMagnitudeBalance(string currentWord, string numberAsString);
bool isMagnitudeBalanced(int magnitudeBalance);
string getPaddedForMagnitude(string numberAsString,	int magnitudeBalance);

bool isNumberDemarcator(char character);
bool isFirstLetter(string numberInEnglish,	int numberIndexFromEnd);
int wordsToMagnitude(string word);

string addZeroPadding(int numberOfZeroes);
string addCommasMagnitude(string numberAsWord);

// Global constants
char const space = ' ';
char const comma = ',';
char const hyphen = '-';


// Program
int main()
{
	// User input
	string numberInEnglish = "";
	cout << "Please write in any number you wish to see written out in digits: " << '\n';
	getline(cin, numberInEnglish, '\n');

	string numberAsString = "";
	string currentWord = "";
	for (size_t i = 0; i < numberInEnglish.length(); i++)
	{
		// Get last letter and increment forward
		char currentLetter = tolower(numberInEnglish[numberInEnglish.length() - 1 - i]);
		
		if (!isNumberDemarcator(currentLetter)) 
		{
			// Continue constructing word
			currentWord = currentLetter + currentWord;
		}
		
		if (isNumberDemarcator(currentLetter) ||
			isFirstLetter(numberInEnglish, i)) 
		{
			// Analyze word
			string currentNumber = wordsToNumbers(currentWord);
			int magnitudeBalance = getMagnitudeBalance(currentWord, numberAsString);

			if (!(currentNumber == ""))
			{
				numberAsString = currentNumber + numberAsString;
			}
			else if (isTens(currentWord))
			{
				numberAsString = getTens(numberAsString);
			}
			else if (isHundreds(currentWord))
			{
				numberAsString = getHundreds(numberAsString);
			}
			else if (!isMagnitudeBalanced(magnitudeBalance))
			{
				numberAsString = getPaddedForMagnitude(numberAsString, magnitudeBalance);
			}
			currentWord = "";
		}
	}

	// Add commas:
	numberAsString = addCommasMagnitude(numberAsString);

	// Add sign:
	if (isNegative(numberInEnglish))
	{
		numberAsString = "-" + numberAsString;
	}
	cout << "The number you entered was " << numberAsString << '\n';
}

bool isNumberDemarcator(char character)
{
	return ((character == hyphen) ||
		(character == comma) ||
		(character == space));
}

bool isFirstLetter(string numberInEnglish, 
	int numberIndexFromEnd)
{
	return (numberIndexFromEnd == numberInEnglish.length() - 1);
}

bool isNegative(string number)
{
	string negative = "negative";
	if (number.length() > negative.length())
	{
		for (size_t i = 0; i < negative.length(); i++)
		{
			if (!(tolower(number[i]) == negative[i]))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

string wordsToNumbers(string word)
{
	if (word == "one")
		return "1";
	if (word == "two")
		return "2";
	if (word == "three")
		return "3";
	if (word == "four")
		return "4";
	if (word == "five")
		return "5";
	if (word == "six")
		return "6";
	if (word == "seven")
		return "7";
	if (word == "eight")
		return "8";
	if (word == "nine")
		return "9";
	if (word == "ten")
		return "10";
	if (word == "eleven")
		return "11";
	if (word == "twelve")
		return "12";
	if (word == "thirteen")
		return "13";
	if (word == "fourteen")
		return "14";
	if (word == "fifteen")
		return "15";
	if (word == "sixteen")
		return "16";
	if (word == "seventeen")
		return "17";
	if (word == "eighteen")
		return "18";
	if (word == "nineteen")
		return "19";
	if (word == "twenty")
		return "2";
	if (word == "thirty")
		return "3";
	if (word == "forty")
		return "4";
	if (word == "fifty")
		return "5";
	if (word == "sixty")
		return "6";
	if (word == "seventy")
		return "7";
	if (word == "eighty")
		return "8";
	if (word == "ninety")
		return "9";
	return "";
}

bool isTens(string word)
{
	return ((word == "twenty") ||
		(word == "thirty") ||
		(word == "forty") ||
		(word == "fifty") ||
		(word == "sixty") ||
		(word == "seventy") ||
		(word == "eighty") ||
		(word == "ninety"));
}

string getTens(string numberAsWord)
{
	int numberLength = numberAsWord.length();
	if (numberLength < 2)
	{
		numberAsWord = addZeroPadding(1 - numberLength) + numberAsWord;
	}
	else
	{
		int offset = 1;
		while (offset - numberLength < 0)
		{
			offset += 3;
		}
		numberAsWord = addZeroPadding(offset - numberLength) + numberAsWord;
	}
	return numberAsWord;
}

bool isHundreds(string word)
{
	return (word == "hundred");
}

string getHundreds(string numberAsWord)
{
	int numberLength = numberAsWord.length();

	int offset = 2;
	while (offset - numberLength < 0)
	{
		offset += 3;
	}
	numberAsWord = addZeroPadding(offset - numberLength) + numberAsWord;

	return numberAsWord;
}

int getMagnitudeBalance(string currentWord,
	string numberAsString)
{
	int currentMagnitude = wordsToMagnitude(currentWord);
	int numberLength = numberAsString.length();
	return (currentMagnitude - numberLength);
}

bool isMagnitudeBalanced(int magnitudeBalance)
{
	return (magnitudeBalance <= 0);
}

string getPaddedForMagnitude(string numberAsString,
	int magnitudeBalance)
{
	return (addZeroPadding(magnitudeBalance) + numberAsString);
}


int wordsToMagnitude(string word)
{
	if (word == "thousand") { return 3; }
	if (word == "million") { return 6; }
	if (word == "billion") { return 9; }
	if (word == "trillion") { return 12; }
	return 0;
}

string addZeroPadding(int numberOfZeroes)
{
	string currentPadding = "";
	for (size_t j = 0; j < numberOfZeroes; j++)
	{
		currentPadding += "0";
	}
	return currentPadding;
}

string addCommasMagnitude(string numberAsWord)
{
	string numberAsWordWithCommas = "";
	int subcount = 0;
	int originalLength = numberAsWord.length();
	for (size_t i = 0; i < originalLength; i++)
	{
		numberAsWordWithCommas = numberAsWord[originalLength - 1 - i] + numberAsWordWithCommas;
		subcount++;
		if ((subcount == 3) && !(i == originalLength - 1))
		{
			subcount = 0;
			numberAsWordWithCommas = "," + numberAsWordWithCommas;
		}
	}
	return numberAsWordWithCommas;
}

