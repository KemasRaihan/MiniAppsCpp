#pragma once
#include <iostream>
#include <chrono>
using namespace std;

class MiniApps
{
public:
	MiniApps();
	~MiniApps();
	static void displayMenu();
	static void KeepCountingGame();
	static void SquareRootCalculator();
	static void CheckDigitGenerator();
	static void CheckDigitChecker();
	static void pressEnterToStart();
	static int returnRandomInteger(int range);
	static bool numberIsNDigits(int number, int N);
};

