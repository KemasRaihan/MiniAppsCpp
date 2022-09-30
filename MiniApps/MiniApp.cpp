#include "MiniApp.h"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
	// changes the starting point in the sequence of values between 0 to RAND_MAX in the rand() function
	srand(time(NULL));
	displayMenu();
	return 0;
}

void displayMenu()
{
	bool terminate = false;
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
		int option;
		cin >> option;
		switch (option)
		{
		case 1:KeepCountingGame(); break;
		case 2:SquareRootCalculator(); break;
		case 3:CheckDigitGenerator(); break;
		case 4:CheckDigitChecker(); break;
		case 9: terminate = true; break;
		default:cout << "Invalid option. Please select again." << endl;
		}
	} while (!terminate);
}



void KeepCountingGame()
{
	cout << "Keep Counting Game\n";
	cout << "-------------------\n";
	cout << "You will be presented with 10 addition questions.\n";
	cout << "After the first question, the left - hand operand\n";
	cout << "is the result of the previous addition.\n";
	cout << "Press enter to start...";
	pressEnterToStart();

	int range = 10;
	int firstOperand = returnRandomInteger(range);
	int secondOperand;
	string randOperator;
	int question = 1;
	bool userAnswersIncorrectly = false;
	int userAnswer;
	int correctAnswer;

	// Game starts...
	// starts stopwatch
	auto startTime = chrono::steady_clock::now();
	while (question <= 10 && !userAnswersIncorrectly)
	{
		secondOperand = returnRandomInteger(range);
		randOperator = rand() % 2 == 0 ? "+" : "-";

		cout << "\n\nQuestion " << question << " : ";
		cout << firstOperand << " " << randOperator << " " << secondOperand;
		cout << " = ";
		cin >> userAnswer;

		correctAnswer = randOperator == "+" ? firstOperand + secondOperand : firstOperand - secondOperand;

		if (userAnswer != correctAnswer) userAnswersIncorrectly = true;

		firstOperand = correctAnswer;
		question++;

	}
	// end stopwatch
	auto endTime = chrono::steady_clock::now();

	if (!userAnswersIncorrectly)
	{
		double elapsedTime = (chrono::duration_cast <chrono::nanoseconds> (endTime - startTime).count()) / 1e9;
		cout << "\n\nQuestions complete in " << (int)elapsedTime << " seconds\n\n";
	}
}

void SquareRootCalculator()
{
	cout << "Square Root Calculator\n";
	cout << "-------------------\n";
	cout << "Please enter a positive number: ";
	int inputNumber;
	cin >> inputNumber;
	cout << "\nHow many decimal places do you want the solution calculated: ";
	int numberOfDecimalPlaces;
	cin >> numberOfDecimalPlaces;

	double lowerBound, upperBound;

	int* bounds = findBounds(inputNumber);
	lowerBound = bounds[0], upperBound = bounds[1];

	// calculates average until the difference between the bounds is less than the decimal place precision
	double average;
	double averageSquared;
	double decimalPrecision = pow(0.1, numberOfDecimalPlaces);
	do {
		average = (double)(lowerBound + upperBound) / 2;
		averageSquared = average * average;

		if (averageSquared > inputNumber)upperBound = average;
		else lowerBound = average;
	} while (abs(averageSquared - inputNumber) > decimalPrecision);

	cout << "The square root of " << inputNumber << " to ";
	cout << numberOfDecimalPlaces << " decimal places is ";
	cout << (int)(average * pow(10.0, numberOfDecimalPlaces)) / (pow(10.0, numberOfDecimalPlaces)) << "\n\n";


}

void CheckDigitGenerator()
{
	cout << "Check Digit Generator\n";
	cout << "-------------------\n";
	cout << "This calculator will take a 5-digit number and generate a trailing 6th check digit\n";
	cout << "Please enter 5 - digit number to generate final code: ";
	int number;
	cin >> number;
	while (!numberIsNDigits(number, 5))
	{
		cout << "Invalid input. Please try again: ";
		cin >> number;
	}
	int oddSum = 0, evenSum = 0;
	int digit;
	for (int i = 1; i <= 5; i++)
	{
		digit = number / pow(10, i - 1);
		digit %= 10;
		if (i % 2 == 0) evenSum += digit;
		else oddSum += digit;
	}
	int newSum = 7 * oddSum + 3 * evenSum;
	int sixthDigit = 10 - (newSum % 10);
	cout << "The 6-digit final number is " << number << sixthDigit << "\n\n";


}

void CheckDigitChecker()
{
	cout << "Check Digit Checker\n";
	cout << "-------------------\n";
	cout << "Please enter a six digit number to check: ";
	int number;
	cin >> number;
	if (numberIsNDigits(number, 6)) cout << "The number is valid.\n";
	else cout << "The number is invalid.\n";

}

void pressEnterToStart()
{
	cin.get();
	cin.ignore();
}

int returnRandomInteger(int range)
{
	return rand() % range + 1;
}

bool numberIsNDigits(int number, int N)
{
	return (number / pow(10, N) > 1e-1 && number / pow(10, N-1) < 10);
}

// find upper and lower bounds of the square root of the number
int* findBounds(int number)
{
	int n = 0;
	while (n * n < number) n++;
	int arr[2] = { n - 1,n };
	int* ptr = arr;
	return arr;
}
