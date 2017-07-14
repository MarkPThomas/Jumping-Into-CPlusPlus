#include <iostream>

using namespace std;

void playGame() { cout << "Playing game!\n"; }
void loadGame(){ cout << "Loading game!\n"; }
void playMultiplayer(){ cout << "Playing multiplayer game!\n"; }

int main()
{
	int input;

	cout << "1. Play game\n";
	cout << "2. Load game\n";
	cout << "3. Play multiplayer\n";
	cout << "4. Exit\n";
	cin >> input;

	switch (input)
	{
	case 1:
		playGame();
		break;
	case 2:
		loadGame();
		break;
	case 3:
		playMultiplayer();
		break;
	case 4:
		cout << "Thank you for playing!\n";
		break;
	default:
		cout << "Error, bad input, quitting\n";
		break;
	}
}