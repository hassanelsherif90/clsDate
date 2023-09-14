
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

	static bool IsYearLeap(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool IsYearLeap()
	{
		return IsYearLeap(_Year);
	}

	static short NumberDaysInYear(short Month, short Year)
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

	short NumberDaysInYear()
	{
		return NumberDaysInYear(_Month, _Year);
	}

	static short TotalDaysBegingInYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (int i = 0; i < Month; i++)
		{
			TotalDays += NumberDaysInYear(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}

	short TotalDaysBegingInYear()
	{
		return TotalDaysBegingInYear(_Day, _Month, _Year);
	}

	clsDate GetDateFromDayOrderInYear(short DaysOrderInYear, short Year)
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

	static short DayOrderOfWeek(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + (12 * a) - 2;
		return ((Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
	}

	short DayOrderOfWeek()
	{
		return DayOrderOfWeek(_Day, _Month, _Year);
	}

	static string NameOfMonth(short Month)
	{
		string arrMonth[12] =
		{
			"Jan", "Feb", "Mar",
			"Apr", "May", "Jun",
			"Jul", "Aug", "Des",
			"Oct", "Nov", "Dec"
		};

		return arrMonth[Month - 1];
	}

	string NameOfMonth()
	{
		return NameOfMonth(_Month);
	}

	static void PrintCalender(short Month, short Year)
	{
		int NumberOfDays;
		short Curent = DayOrderOfWeek(1, Month, Year);
		NumberOfDays = NumberDaysInYear(Month, Year);

		printf("\n______________________%s___________________________\n", NameOfMonth(Month).c_str());
		printf("\n   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		for (i = 0; i < Curent; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n_____________________________________________________\n");
	}

	void PrintCalender()
	{
		PrintCalender(_Month , _Year);
	}

	static bool LastMonth(short Month)
	{
		return (Month == 12);
	}

	bool LastMonth()
	{
		return LastMonth(_Month);
	}

	static bool LastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumberDaysInYear(Date._Month, Date._Year));
	}

	bool LastDayInMonth()
	{
		return LastDayInMonth(*this);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (LastDayInMonth(Date))
		{
			if (LastMonth(Date._Month))
			{
				Date._Day = 1;
				Date._Month = 1;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
		{
			Date._Day++;
		}
		return Date;
	}

	clsDate IncreaseDateByOneDay()
	{
		return IncreaseDateByOneDay(*this);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(* this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsDate1EqualeDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1AfterDate2(Date1, Date2));
	}

	bool IsDateEqualeDate2(clsDate Date2)
	{
		return IsDate1EqualeDate2(*this, Date2);
	}

	static int GetDifferanceDays(clsDate Date1, clsDate Date2 = clsDate() , bool IncludeDay = false)
	{
		int Days = 0;
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return IncludeDay ? ++Days : Days;
	}

	int PeriodLengthDays(clsDate Period, bool IncludeEndDate = false)
	{
		return GetDifferanceDays(* this, Period,  IncludeEndDate);
	}

	bool IsValidDate()
	{
		if (this-> _Day < 1 || this -> _Day > 31)
			return false;

		if (this-> _Month < 1 || this-> _Month > 12)
			return false;

		if (this->_Month == 2)
		{
			if (IsYearLeap(this->_Year))
			{
				if (this -> _Day > 29)
					return false;
			}
			else
			{
				if (this -> _Day > 29)
					return false;
			}
		}

		short DaysInMonth = NumberDaysInYear(this -> _Month, this -> _Year);

		if (this -> _Month > DaysInMonth)
			return false;

		return true;
	}

};

