#include "DateChanger.h"

DateChanger::DateChanger() {}
DateChanger::~DateChanger() {}

bool DateChanger::IsValidDateString(string initDate)
{
	/*static const regex r1(R"(^((0[1-9]|[12][0-9]|3[0])([.])(0[469]|1[1]))$)");
	if (regex_match(initDate, r1))
	{
		return regex_match(initDate, r1);
	}
	else 
	{
		static const regex r2(R"(^((0[1-9]|[12][0-9]|)([.])(0[2]))$)");
		if (regex_match(initDate, r2))
		{
			return regex_match(initDate, r2);
		}
	}*/
	static const regex r(R"(^(((0[1-9]|[12][0-9]|3[01])([.])(0[13578]|1[02]))|((0[1-9]|[12][0-9]|)([.])(0[2]))|((0[1-9]|[12][0-9]|3[0])([.])(0[469]|1[1])))$)");
	//static const regex r(R"((^(3[0-1])([.])(0[13578]|1[02]))|(^(3[0])([.])(0[469]|1[1]))|(^((0[1-9])|(1[0-9])|(2[0-9]))([.])((0[1-9])|(1[0-2])))$)");
	

	return regex_match(initDate, r);
}

void DateChanger::Tokenize(string str, char delim, vector<string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void DateChanger::Add3Day(int currentDays, int currentMonths, int& newDays, int& newMonths)
{
                          /* 1  2  3  4  5  6  7  8  9  10 11 12*/
	vector<int> monthsAll{ 0,31,29,31,30,31,30,31,31,30,31,30,31 };

	for (int i = 0; i < monthsAll.size(); i++)
	{
		if (i == currentMonths && monthsAll[i] == 31)
		{
			if (currentDays >= 1 && currentDays <= 28)
			{
				newDays = currentDays + 3;
				newMonths = currentMonths;
			}
			else if (currentDays > 28 && currentDays <= 31)
			{
				newMonths = currentMonths + 1;

				if (newMonths > 12)
				{
					newMonths = 1;
					int sum = currentDays + 3;
					newDays = sum - 31;
				}
				else
				{
					int sum = currentDays + 3;
					newDays = sum - 31;
				}
			}
		}
		else if (i == currentMonths && monthsAll[i] == 30 && currentDays < 31)
		{
			if (currentDays >= 1 && currentDays <= 27)
			{
				newDays = currentDays + 3;
				newMonths = currentMonths;
			}
			else if (currentDays > 27 && currentDays <= 30)
			{
				newMonths = currentMonths + 1;
				int sum = currentDays + 3;
				newDays = sum - 30;
			}
		}
		else if (i == currentMonths && monthsAll[i] == 29 && currentDays < 30)
		{
			if (currentDays >= 1 && currentDays <= 26)
			{
				newDays = currentDays + 3;
				newMonths = currentMonths;
			}
			else if (currentDays > 26 && currentDays <= 29)
			{
				newMonths = currentMonths + 1;
				int sum = currentDays + 3;
				newDays = sum - 29;
			}
		}
	}
}

/**
������� ��������� ������� � ���������� �������.
@param hours: �������� �����.
@param minutes: �������� �����.
@param time_text: ������ � �������� �������.
**/
void DateChanger::DateToText(int days, int months, string& date_text)
{
	vector<string> days_names =
	{
		"0", "������", "������", "������", "���������", "�����", "������", "�������", "�������", "�������", "�������",
		"������������", "�����������", "�����������", "�������������", "�����������", "������������", "�����������", "�������������",
		"�������������", "���������", "�������� ������", "�������� ������", "�������� ������", "�������� ���������", "�������� �����",
		"�������� ������", "�������� �������", "�������� �������", "�������� �������", "���������", "�������� ������"
	};

	date_text = days_names[days];

	string months_names("");
	switch (months)
	{
	case 1:
	{
		months_names = "������";
		break;
	}

	case 2:
	{
		months_names = "�������";
		break;
	}

	case 3:
	{
		months_names = "�����";
		break;
	}
	case 4:
	{
		months_names = "������";
		break;
	}
	case 5:
	{
		months_names = "���";
		break;
	}
	case 6:
	{
		months_names = "����";
		break;
	}
	case 7:
	{
		months_names = "����";
		break;
	}
	case 8:
	{
		months_names = "�������";
		break;
	}
	case 9:
	{
		months_names = "��������";
		break;
	}
	case 10:
	{
		months_names = "�������";
		break;
	}
	case 11:
	{
		months_names = "������";
		break;
	}
	case 12: {
		months_names = "�������";
		break;
	}
	}

	date_text += " " + months_names;
}

/**
����� �������, ����������� �� 5 ����� � ��������� �������.
@param initDate: ����� ��� ��������� � ������� ������ HH:MM.
@param newTime: �������� ������������� ������� ����� ����������� 5 �����.

@return ��� ������, ��������� � ������������ ExitCode.
**/
ReturnCode DateChanger::GetDatePlus3Day(string initDate, string& newDate)
{
	cout << "---------- ������� ----------" << endl;

	// �������� ���������� ������� �� ������������ ������� DD.MM.
	if (!IsValidDateString(initDate)) {
		cout << "[+] ������� ������������ �������� ����";
		return NOT_VALID_INIT_DATE;
	}

	// ��������� �������� �������� ����, �����.
	vector<string> date;
	const char delitel = '.';
	Tokenize(initDate, delitel, date);
	int current_days = stoi(date.front());
	int current_months = stoi(date.back());

	cout << "��������� ����:" << endl;
	cout << "����: " << current_days << " �����: " << current_months << endl << endl;

	// ���������� 3 ����.
	int newDays = NULL;
	int newMonths = NULL;
	Add3Day(current_days, current_months, newDays, newMonths);

	// ������������ ������ � �������� ���������� ����.
	string date_text("");
	DateToText(newDays, newMonths, date_text);

	cout << "����� ���� (+3 ���):" << endl;
	cout << "����: " << newDays << " �����: " << newMonths << endl;
	cout << "��������� ������: " << date_text << endl;

	cout << "---------- ������� ----------" << endl << endl;

	newDate = date_text;

	return SUCCESS;
}