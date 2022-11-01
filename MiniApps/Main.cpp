#include "MiniApps.h"
#include <iostream>
#include <chrono>
using namespace std;

void displayMenu();

int main()
{
	// changes the starting point in the sequence of values between 0 to RAND_MAX in the rand() function
	srand(time(NULL));

	displayMenu();

	// check for memory leaks in the programme
#ifdef _DEBUG
	  _CrtSetBreakAlloc(87);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	return 0;
}

void displayMenu()
{
	bool terminate = false;
	int option;
	do
	{
		cout << "P4CS Mini Applications" << endl;
		cout << "----------------------" << endl;
		cout << "Please select an option: " << endl;
		cout << "1) Keep Counting Game" << endl;
		cout << "2) Square Root Calculator" << endl;
		cout << "3) Check-Digit Generator" << endl;
		cout << "4) Check-Digit Checker" << endl;
		cout << "9) Quit" << endl;

		cout << "\nPlease enter an option: ";
		cin >> option;
		switch (option)
		{
		case 1:MiniApps::KeepCountingGame(); break;
		case 2:MiniApps::SquareRootCalculator(); break;
		case 3:MiniApps::CheckDigitGenerator(); break;
		case 4:MiniApps::CheckDigitChecker(); break;
		case 9: cout << "\nGoodbye!"; break;
		default:cout << "\nInvalid option. Please select again.\n" << endl;
		}
	} while (option!=9);
}




