#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
	// Precision
	cout << setprecision(3) << 3.71828 << endl;	// 3.72 (rounds)
	cout << 1.412 << endl;						// 1.41 (setprecision is permanent and is still in effect here)
	cout << setprecision(2) << 1234.0 << endl;  // 1.2e3 (if fewer than whole number sig figs, floating numbers displayed in scientific notation)
	cout << setprecision(2) << 1234 << endl;	// 1234 (if fewer than whole number sig figs, integer numbers displayed to decimal

	// For money:
	int cents = 1001; // $10.01
	cout << '$' << cents / 100 << "." << setw(2) << setfill('0') << cents % 100 << endl;

	// Output in different bases
	cout << "0X" << setbase(16) << 32 << endl;	// 32 written in hexadecimal as 0x20
	cout << "0" << setbase(8) << 32 << endl;	// 32 written in octadecimal as 0x20
	cout <<  setbase(10) << 32 << endl;			// 32 written in decimal as 0x20
	// Those correspond to the following shorthand:
	cout << "0X" << hex << 32 << endl;	// 32 written in hexadecimal as 0x20
	cout << "0" << oct << 32 << endl;	// 32 written in octadecimal as 0x20
	cout << dec << 32 << endl;			// 32 written in decimal as 0x20

	cout << setiosflags(ios_base::showbase) << setbase(16) << 32 << endl;
	cout << setiosflags(ios_base::showbase) << setbase(8) << 32 << endl;
	cout << setiosflags(ios_base::showbase) << setbase(10) << 32 << endl;

	// To reset bases:
	cout << setbase(16) << noshowbase << 32 << endl;
}