#include "DateChanger.h"

void main()
{
	setlocale(LC_ALL,"RU");
	string initDate("31.12");
	string newDate("");

	DateChanger* few = new DateChanger();
	ReturnCode chto_to = few->GetDatePlus3Day(initDate, newDate);
}