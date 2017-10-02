#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	// Setting padding amount and text alignment
	cout << setw(10) << "ten" << "four" << "four" << endl;			// Adds padding of 10 characters, default aligned on the right for the text
	cout << setw(10) << left << "ten" << "four" << "four" << endl;	// Alignment left

	// Changing the padding character
	cout << setfill('-') << setw(10) << "ten" << "four" << "four" << endl;

	// Permanently changing settings
	// 'fill' returns the previous fill character used, which can be used to reset the global change later
	const char lastFill = cout.fill('*');
	cout << setw(10) << "A" << setw(10) << "B" << setw(10) << "C" << endl;

	// Resetting the fill character
	cout.fill(lastFill); 
	cout << setw(10) << "D" << endl;

	// 'setf' acts similarly to fill, but acts for alignment of padded text
	int lastAlignment = cout.setf(ios_base::left);
	cout << setw(10) << "More aligned text" << setw(10) << "here" << endl;
	//cout.setf(lastAlignment);
	cout.setf(ios_base::right);
	cout << setw(10) << "With padded text alignment reset" << setw(10) << "here" << endl;
}