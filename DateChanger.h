#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

enum ReturnCode
{
	NOT_VALID_INIT_DATE,
	SUCCESS
};

class DateChanger
{
	private:
		bool IsValidDateString(string initDate);
		void Tokenize(string str, char delim, vector<string>& out);
		void Add3Day(int currentDays, int currentMonths, int& newDays, int& newMonths);
		void DateToText(int Days, int Months, string& DateText);

	public:
		DateChanger();
		~DateChanger();

		ReturnCode GetDatePlus3Day(string initDate, string& newDate);
};