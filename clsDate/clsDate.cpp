#pragma warning(disable : 4996)

#include <iostream>
#include "clsDate.h"


using namespace std;

int main()
{
	clsDate Date1;
	//Date1.Print();


	//clsDate Date2("31/12/2023");
	//Date2.Print();
	//

	//clsDate Date3(1, 1, 1994);
	//Date3.Print();
	//

	//clsDate Date4(250, 2022);
	//Date4.Print();
	//Date4.PrintCalender(9, 2023);
	//Date3.PrintCalender(1, 1994);

	cout << clsDate::GetDifferanceDays(clsDate(1, 1, 1994)) << endl;

	cout << Date1.LastDayInMonth() <<endl;
	cout << Date1.LastMonth() << endl;
	cout << Date1.IsValidDate() << endl;

}


