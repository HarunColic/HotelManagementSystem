#pragma once
#include<iostream>
using namespace std;

class Date
{
	int _d, _m, _y;

public:

	Date()
	{
		_d = _m = _y = 0;
	}

	Date(int d, int m, int y) {

		_d = d;
		_m = m;
		_y = y;
	}

	Date(Date &D) {

		_d = D._d;
		_m = D._m;
		_y = D._y;
	}

	~Date()
	{
	}

	void operator =(Date &D) {

		_d = D._d;
		_m = D._m;
		_y = D._y;
	}

	friend ostream &operator <<(ostream &COUT, Date &D) {

		COUT << D._d << "/" << D._m << "/" << D._y;

		return COUT;
	}

	int &getMonth() {

		return _m;
	}

	int &getDay() {

		return _d;
	}
};