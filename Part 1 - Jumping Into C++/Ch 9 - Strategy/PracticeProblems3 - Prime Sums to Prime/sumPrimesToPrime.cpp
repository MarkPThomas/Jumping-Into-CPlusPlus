#include <iostream>
#include <string>

using namespace std;

bool isDivisible(int number, int divisor);
bool isPrime(int number);
int getPrimeFactor(int number);
string numberHasPrimeFactorsWhichSumToPrime(int number);

int main()
{
	for (size_t i = 1; i <= 1000; i++)
	{
		string message = numberHasPrimeFactorsWhichSumToPrime(i);
		if (!(message == ""))
		{
			cout << message << "\n";
		}
	}
}

bool isPrime(int number)
{
	// Handle simple cases

	// Bracket lowest numbers from consideration
	if (number == 0) { return false; }
	if (number == 1) { return false; }

	// Known primes & their multiples
	int prime = 2;
	if (number == prime) { return true; }
	if (isDivisible(number, prime)) { return false; }
	prime = 3;
	if (number == prime) { return true; }
	if (isDivisible(number, prime)) { return false; }
	prime = 5;
	if (number == prime) { return true; }
	if (isDivisible(number, prime)) { return false; }
	prime = 7;
	if (number == prime) { return true; }
	if (isDivisible(number, prime)) { return false; }

	// Main check
	int maxNumberTest = floor(sqrt(number));

	for (size_t i = 2; i <= maxNumberTest; i++)
	{
		if (isDivisible(number, i))
		{
			return false;
		}
	}
	return true;
}

bool isDivisible(int number, int divisor)
{
	return  number % divisor == 0;
}

/// <summary>
/// Uses Direct Search Factorization (Trial Division) for determining the lowest prime factor. <para/>
/// If a valid number cannot be found, 0 is returned.
/// </summary>
/// <param name="number">The number.</param>
/// <returns>int.</returns>
int getPrimeFactor(int number)
{
	// Handle simple case
	if (number == 0) { return 0; }
	if (number == 1) { return 0; }
	if (number == 2) { return number; }

	int maxNumberTest = floor(sqrt(number));

	for (size_t i = 2; i <= maxNumberTest; i++)
	{
		if (isDivisible(number, i) && isPrime(i))
		{
			return i;
		}
	}
	return 0;
}

string numberHasPrimeFactorsWhichSumToPrime(int number)
{
	// Check simple limiting cases
	if (number == 0) { return ""; }
	if (number == 1) { return ""; }
	if (isPrime(number))
	{
		return to_string(number) + " is its own prime factor. \n";
	}
	
	// Regular check
	int remainder = number;
	int currentSum = 0;
	string message = to_string(number) + " has prime factors: ";
	bool isFirstTerm = true;
	while (true)
	{
		int primeFactor = getPrimeFactor(remainder);
		if (primeFactor == 0)
		{
			return "An error has occurred with number " + to_string(number) + "\n";
		}
		if (!isFirstTerm)
		{
			message += ", ";
		}
		message += to_string(primeFactor);
		
		currentSum += primeFactor;
		remainder = (remainder / primeFactor);

		if (isPrime(remainder))
		{
			if (isPrime(remainder + currentSum))
			{
				message += ", " + to_string(remainder);
				message += "\n";
				message += "Which sum to: " + to_string(remainder + currentSum) + "\n";
				return message;
			}
			return "";
		}
		isFirstTerm = false;
	}
	return "";
}