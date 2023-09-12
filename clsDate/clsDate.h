
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

class clsDate
{
private :

	short _Day;
	short _Month;
	short _Year;


public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Year  = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day   = now->tm_mday;

	}
	
	clsDate(string Date)
	{
		vector <string> Date1 = Split(Date, "/");

		_Day = stoi(Date1[0]);
		_Month = stoi(Date1[1]);
		_Year = stoi(Date1[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	
	clsDate(short Day, short Year)
	{
		clsDate Date = GetDateFromDayOrderInYear(Day, Year);

		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}


	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	vector <string> Split(string S1, string Delim)
	{
		vector<string> vString;

		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word   
			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
		}

		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}

		return vString;

	}

	bool IsYearLeap(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	short NumberDaysInYear(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}
		int NumberDays[12] = {
			31, 28,
			31, 30,
			31, 30,
			31, 31,
			30, 31,
			30, 31 };

		return (Month == 2 ? (IsYearLeap(Year) ? 29 : 28) : NumberDays[Month - 1]);
	}


	short TotalDaysBegingInYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (int i = 0; i < Month; i++)
		{
			TotalDays += NumberDaysInYear(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}

	clsDate GetDateFromDayOrderInYear(int DaysOrderInYear, int Year)
	{

		clsDate Date;
		short ReamingDays = DaysOrderInYear;
		short MonthDay = 0;

		Date._Year = Year;
		Date._Month = 1;

		while (true)
		{
			MonthDay = NumberDaysInYear(Date._Month, Year);

			if (ReamingDays > MonthDay)
			{
				ReamingDays -= MonthDay;
				Date._Month++;
			}
			else
			{
				Date._Day = ReamingDays;
				break;
			}
		}
		return Date;

	}
};

