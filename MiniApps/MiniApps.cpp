#include "MiniApps.h"
#include <iostream>

using namespace std;

void MiniApps::KeepCountingGame()
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
		randOperator = (rand() < RAND_MAX / 2) ? "+" : "-";

		cout << "\n\nQuestion " << question << " : ";
		cout << firstOperand << " " << randOperator << " " << secondOperand;
		cout << " = ";
		cin >> userAnswer;

		correctAnswer = (randOperator == "+") ? (firstOperand + secondOperand) : (firstOperand - secondOperand);

		if (userAnswer != correctAnswer) userAnswersIncorrectly = true;

		firstOperand = secondOperand;
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

void MiniApps::SquareRootCalculator()
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

	lowerBound = 0;
	upperBound = inputNumber;

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

void MiniApps::CheckDigitGenerator()
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

void MiniApps::CheckDigitChecker()
{
	cout << "Check Digit Checker\n";
	cout << "-------------------\n";
	cout << "Please enter a six digit number to check: ";
	int number;
	cin >> number;
	if (numberIsNDigits(number, 6)) cout << "The number is valid.\n";
	else cout << "The number is invalid.\n";

}

void MiniApps::pressEnterToStart()
{
	cin.get();
	cin.ignore();
}

int MiniApps::returnRandomInteger(int range)
{
	return rand() % range + 1;
}

bool MiniApps::numberIsNDigits(int number, int N)
{
	return (number >= pow(10, N - 1) && number < pow(10, N));
}
