#pragma once
#include<iostream>
using namespace std;

Room *_rooms; //Global array of rooms(can be accessed by either the employee or the customer and modified respectively)
int _totalRooms = 0; //Keeps track of the total number of rooms in the hotel

//counts the number of days passed between the check in and the check out date(used in determining the fee the guest has to pay)
int daysPassed(Date from, Date to) {

	int dayCount = 0;

	int monthGap = from.getMonth() - to.getMonth();

	if (from.getDay() > to.getDay()) {

		dayCount = from.getDay() - to.getDay();
		dayCount += (monthGap * 30);
	}
	else
		dayCount = (from.getDay() + (monthGap * 30)) - to.getDay();

	return abs(dayCount);
}

class User
{
protected:
	char *_fullName;

public:

	virtual void polymorph() = 0 {

	}

	User()
	{

		_fullName = nullptr;
	}

	User(char *fullName) {

		_fullName = new char[strlen(fullName) + 1];
		strcpy_s(_fullName, strlen(fullName) + 1, fullName);
	}

	User(User &U) {

		_fullName = new char[strlen(U._fullName) + 1];
		strcpy_s(_fullName, strlen(U._fullName) + 1, U._fullName);
	}

	virtual ~User()
	{

		delete[] _fullName;
		_fullName = nullptr;

	}

	char *getUserName() {

		return _fullName;
	}

};