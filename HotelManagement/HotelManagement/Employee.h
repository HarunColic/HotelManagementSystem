#pragma once
#include<iostream>
#include"Room.h"
#include"User.h"
#include"Guest.h"
using namespace std;

class Employee : public User
{
	char *_employeeID;

public:

	void polymorph() {

	}

	Employee() :User()
	{
		_employeeID = nullptr;
	}

	Employee(char *employeeID, char *fullName) :User(fullName) {

		_employeeID = new char[strlen(employeeID) + 1];
		strcpy_s(_employeeID, strlen(employeeID) + 1, employeeID);
	}

	~Employee()
	{
		delete[]_employeeID;
		_employeeID = nullptr;
	}

	void addRoom(Room room) {

		Room *temp = new Room[_totalRooms + 1];

		for (int i = 0; i < _totalRooms; i++) {

			temp[i] = _rooms[i];

			roomNo--;
		}

		temp[_totalRooms] = room;

		delete[] _rooms;
		_rooms = temp;

		roomNo--;

		_totalRooms++;

		cout << "Room added" << endl;
	}

	void modifyRoom(char *roomNumber) {

		bool roomExists;

		try
		{
			for (int i = 0; i < _totalRooms; i++) {

				if (strcmp(roomNumber, _rooms[i].getRoomNumber()) == 0)
					roomExists = true;
			}

			if (!roomExists)
				throw exception("Room doesn't exist");
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}

		for (int i = 0; i < _totalRooms; i++) {

			if (strcmp(roomNumber, _rooms[i].getRoomNumber()) == 0) {

				cout << "1. modify room description" << endl;
				cout << "2. modify room price" << endl;
				cout << "3. modify room type" << endl;
				cout << "4. modify room status" << endl;

				int input;

				do
				{
					cin >> input;

				} while (input > 4 || input < 1);

				switch (input)
				{
				case 1: _rooms[i].modifyRoomDescription(); break;
				case 2: _rooms[i].modifyRoomPrice(); break;
				case 3: _rooms[i].modifyRoomType(); break;
				case 4: _rooms[i].modifyRoomStatus(); break;
				}
			}
		}
	}

	void generateBill(Guest g) {

		bool roomExists;

		try
		{
			for (int i = 0; i < _totalRooms; i++) {

				if (strcmp(g.getRoomNumber(), _rooms[i].getRoomNumber()) == 0)
					roomExists = true;
			}

			if (!roomExists)
				throw exception("Room doesn't exist");
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}

		float totalCost;

		for (int i = 0; i < _totalRooms; i++) {

			if (strcmp(g.getRoomNumber(), _rooms[i].getRoomNumber()) == 0) {

				totalCost = _rooms[i].getRoomPrice() * daysPassed(g.getCheckInDate(), g.getCheckOutDate());
			}

		}

		cout << "Guest name: " << g.getUserName() << endl;
		cout << "Room occupied " << g.getRoomNumber() << endl;
		cout << "Check in date: " << g.getCheckInDate() << endl;
		cout << "Check out date: " << g.getCheckOutDate() << endl;
		cout << "Total cost: " << totalCost << endl;
	}

	void generateMenu() {


		cout << "1. List rooms" << endl;
		cout << "2. Modify a room" << endl;
		cout << "3. Add a room" << endl;
		cout << "4. Generate bill" << endl;

	}

	friend ostream &operator <<(ostream & COUT, Employee &E) {

		COUT << "Name: " << E._fullName << endl;
		COUT << "Employee ID: " << E._employeeID << endl;

		return COUT;
	}
};
