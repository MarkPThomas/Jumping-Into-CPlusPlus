#include <iostream>
#include <string>

using namespace std;


// (1) 
// Break the number up into chunks of 3 digits

// (2)
// For each 3-digit chunk, compute the text;
// append the magnitude of that chunk;
// append the chunks together

// (3)
// To compute the text of a 3-digit chunk, compute the number of hundreds,
// and convert that one-digit number to text, and add "hundreds", appending 
// the text of the two-digit chunk

// (4)
// To compute the text of a two-digit chunk, if it's less than 20, look it up;
// if it's great than 20, compute the number of tens, and look up the word,
// and append the text of the one digit number


string getOneDigitNumber(char number);
string getTeensNumber(char number);
string getTensNumber(char number);
string getTwoDigitNumber(char ten, char one);
string getThreeDigitNumber(char hundred, char ten, char one);
string getMagnitude(int divisionsOfThree);


int main()
{
	int min = -999999;
	int max = 999999;

	for (int i = min; i <= max; i++)
	{
		string numberAsString = to_string(i);
		
		// Test sign
		string sign = "";
		bool isNegative = (numberAsString.at(0) == '-');
		if (isNegative)
		{
			sign = "Negative ";
		}

		// Skip first character if number is negative
		int signOffset = 0;
		if (isNegative) { signOffset = 1; }

		// Get left-most magnitude
		int numberCount = numberAsString.length() - signOffset;
		
		string numberInEnglish = "";
		int tens = numberCount % 3;
		int divisionsOfThree = (numberCount - 1) / 3;

		// Generate first ones or tens in the sequence.
		if ((divisionsOfThree > 0) && (tens > 0))
		{
			switch (tens)
			{
			case 1:
				numberInEnglish = getTwoDigitNumber(numberAsString.at(0), numberAsString.at(1));
				break;
			case 2:
				numberInEnglish = getOneDigitNumber(numberAsString.at(0));
				break;
			default:
				break;
			}
			numberInEnglish += " " + getMagnitude(divisionsOfThree) + ", ";
			divisionsOfThree--;
		}

		// Cycle through string after first one or ten, in increments of 3 characters.
		for (size_t j = tens + signOffset; j < numberAsString.length(); j += 3)
		{
			string threeDigits = numberAsString.substr(j, 3);
			numberInEnglish += 
				getThreeDigitNumber(threeDigits.at(0), threeDigits.at(1), threeDigits.at(2)) + " " + getMagnitude(divisionsOfThree);
			if (divisionsOfThree != 0)
			{
				numberInEnglish += ", ";
			}

			divisionsOfThree--;
		}
		cout << numberAsString << ": " << sign << numberInEnglish << '\n';
	}
}

string getOneDigitNumber(char number)
{
	switch(number)
	{
		case '1':
			return "one";
		case '2':
			return "two"; 
		case '3':
			return "three"; 
		case '4':
			return "four"; 
		case '5':
			return "five"; 
		case '6':
			return "six"; 
		case '7':
			return "seven"; 
		case '8':
			return "eight"; 
		case '9':
			return "nine"; 
		default:
			return "";
	}
}

string getTeensNumber(char number)
{
	switch (number)
	{
		case '0':
			return "ten";
		case '1':
			return "eleven";
		case '2':
			return "twelve";
		case '3':
			return "thirteen";
		case '4':
			return "fourteen";
		case '5':
			return "fifteen";
		case '6':
			return "sixteen";
		case '7':
			return "seventeen";
		case '8':
			return "eighteen";
		case '9':
			return "nineteen";
		default:
			return "";
	}
}

string getTensNumber(char number)
{
	switch (number)
	{
	case '1':
		return "ten";
	case '2':
		return "twenty";
	case '3':
		return "thirty";
	case '4':
		return "fourty";
	case '5':
		return "fifty";
	case '6':
		return "sixty";
	case '7':
		return "seventy";
	case '8':
		return "eighty";
	case '9':
		return "ninety";
	default:
		return "";
	}
}

string getTwoDigitNumber(char ten, char one)
{
	string numberString = string() + ten + one;
	if (ten == '0')
	{
		return  getOneDigitNumber(one);
	}
	else if (ten == '1')
	{
		return getTeensNumber(one);
	}
	else // Number is >= 20
	{
		return (getTensNumber(ten) + " " + getOneDigitNumber(one));
	}
}

string getThreeDigitNumber(char hundred, char ten, char one)
{
	string numberString = string() + ten + one;
	if (hundred == '0')
	{
		return  getTwoDigitNumber(ten, one);
	}
	else 
	{
		return (getOneDigitNumber(hundred) + " hundred " + getTwoDigitNumber(ten, one));
	}
}

string getMagnitude(int divisionsOfThree)
{
	switch (divisionsOfThree)
	{
		case 1:
			return "thousand";
		case 2:
			return "million";
		case 3:
			return "billion";
		case 4:
			return "trillion";
		default:
			return "";
	}
}

