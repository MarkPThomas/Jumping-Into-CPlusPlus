#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	// (1) A seed is needed. Unique seeds are needed for a truly random result, so date/time is a convenient seed to use.
	// (2) For debugging purposes, it can be useful to store this seed in a variable rather than using it directly as
	//		a parameter in srand. 
	//		In this way, if an issue occurs, this value can be noted, and then inserted 'manually' into sRand for debugging.
	int sRandSeed = time(nullptr);
  cout << "Time Seed: " << sRandSeed << '\n';
	srand(sRandSeed);
	cout << "Random Number: " << rand() << '\n';
}
