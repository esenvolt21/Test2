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
Перевод цифрового времени к прописному формату.
@param hours: Значение часов.
@param minutes: Значение минут.
@param time_text: Строка с прописью времени.
**/
void DateChanger::DateToText(int days, int months, string& date_text)
{
	vector<string> days_names =
	{
		"0", "Первое", "Второе", "Третье", "Четвертое", "Пятое", "Шестое", "Седьмое", "Восьмое", "Девятое", "Десятое",
		"Одиннадцатое", "Двенадцатое", "Тринадцатое", "Четырнадцатое", "Пятнадцатое", "Шестнадцатое", "Семнадцатое", "Восемнадцатое",
		"Девятнадцатое", "Двадцатое", "Двадцать первое", "Двадцать второе", "Двадцать третье", "Двадцать четвертое", "Двадцать пятое",
		"Двадцать шестое", "Двадцать седьмое", "Двадцать восьмое", "Двадцать девятое", "Тридцатое", "Тридцать первое"
	};

	date_text = days_names[days];

	string months_names("");
	switch (months)
	{
	case 1:
	{
		months_names = "января";
		break;
	}

	case 2:
	{
		months_names = "февраля";
		break;
	}

	case 3:
	{
		months_names = "марта";
		break;
	}
	case 4:
	{
		months_names = "апреля";
		break;
	}
	case 5:
	{
		months_names = "мая";
		break;
	}
	case 6:
	{
		months_names = "июня";
		break;
	}
	case 7:
	{
		months_names = "июля";
		break;
	}
	case 8:
	{
		months_names = "августа";
		break;
	}
	case 9:
	{
		months_names = "сентября";
		break;
	}
	case 10:
	{
		months_names = "октября";
		break;
	}
	case 11:
	{
		months_names = "ноября";
		break;
	}
	case 12: {
		months_names = "декабря";
		break;
	}
	}

	date_text += " " + months_names;
}

/**
Вывод времени, измененного на 5 минут в текстовом формате.
@param initDate: Время для изменения в формате строки HH:MM.
@param newTime: Тестовое представление времени после прибавления 5 минут.

@return Код ошибки, указанный в перечислении ExitCode.
**/
ReturnCode DateChanger::GetDatePlus3Day(string initDate, string& newDate)
{
	cout << "---------- ОТЛАДКА ----------" << endl;

	// Проверка указанного времени на соответствие формату DD.MM.
	if (!IsValidDateString(initDate)) {
		cout << "[+] Указано недопустимое значение даты";
		return NOT_VALID_INIT_DATE;
	}

	// Получение текущего значения день, месяц.
	vector<string> date;
	const char delitel = '.';
	Tokenize(initDate, delitel, date);
	int current_days = stoi(date.front());
	int current_months = stoi(date.back());

	cout << "Указанная дата:" << endl;
	cout << "День: " << current_days << " Месяц: " << current_months << endl << endl;

	// Добавление 3 дней.
	int newDays = NULL;
	int newMonths = NULL;
	Add3Day(current_days, current_months, newDays, newMonths);

	// Формирование текста с прописью полученной даты.
	string date_text("");
	DateToText(newDays, newMonths, date_text);

	cout << "Новая дата (+3 дня):" << endl;
	cout << "День: " << newDays << " Месяц: " << newMonths << endl;
	cout << "Результат работы: " << date_text << endl;

	cout << "---------- ОТЛАДКА ----------" << endl << endl;

	newDate = date_text;

	return SUCCESS;
}