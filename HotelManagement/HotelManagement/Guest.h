#pragma once
#include<iostream>
#include<regex>
#include"Date.h"
#include"User.h"
using namespace std;

bool booked = false;
bool checkedIn = false;
bool checkedOut = false;

class Guest : public User
{

	char *_contactNumber;
	Date _checkInDate;
	Date _checkOutDate;
	char *_roomNumber; //Number of the room this guest has occupied

public:

	void polymorph() {


	}

	Guest() :User()
	{
		_contactNumber = nullptr;
		_roomNumber = nullptr;
	}

	/*Guest(char *contactNumber, char *roomNumber, char *fullName):User(fullName) {

	_contactNumber = new char[strlen(contactNumber) + 1];
	strcpy_s(_contactNumber, strlen(contactNumber) + 1, contactNumber);

	_roomNumber = new char[strlen(roomNumber) + 1];
	strcpy_s(_roomNumber, strlen(roomNumber) + 1, roomNumber);
	}
	*/

	Guest(Guest &G) :User(G._fullName) {

		/*		if (_contactNumber != nullptr) {

		delete[] _contactNumber;
		_contactNumber = nullptr;
		}

		if (_roomNumber != nullptr) {

		delete[] _roomNumber;
		_roomNumber = nullptr;
		}
		*/
		_contactNumber = new char[strlen(G._contactNumber) + 1];
		strcpy_s(_contactNumber, strlen(G._contactNumber) + 1, G._contactNumber);

		_checkInDate = G._checkInDate;

		_checkOutDate = G._checkOutDate;

		_roomNumber = new char[strlen(G._roomNumber) + 1];
		strcpy_s(_roomNumber, strlen(G._roomNumber) + 1, G._roomNumber);


	}

	~Guest()
	{
		delete[] _contactNumber;
		_contactNumber = nullptr;

		delete[] _roomNumber;
		_roomNumber = nullptr;
	}

	Date &getCheckInDate() {

		return _checkInDate;
	}

	Date &getCheckOutDate() {

		return _checkOutDate;
	}

	char *getRoomNumber() {

		return _roomNumber;
	}

	void bookRoom(char *roomNumber) {

		bool roomExists = false;

		try
		{
			for (int i = 0; i < _totalRooms; i++) {

				if (strcmp(roomNumber, _rooms[i].getRoomNumber()) == 0)
					roomExists = true;
			}

			if (!roomExists) {

				throw exception("Room doesn't exist");
				system("pause>0");
			}

			for (int i = 0; i < _totalRooms; i++) {

				if (strcmp(_rooms[i].getRoomNumber(), roomNumber) == 0)
					_rooms[i].setRoomReserved();
				booked = true;
			}
			
			cout << "Room booked successfully" << endl;
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}

		for (int i = 0; i < _totalRooms; i++) {

			if (strcmp(roomNumber, _rooms[i].getRoomNumber()) == 0) {
				_rooms[i].setRoomReserved();

				if (this->_roomNumber != nullptr) {

					delete[] _roomNumber;
					_roomNumber = nullptr;
				}

				_roomNumber = new char[strlen(roomNumber) + 1];
				strcpy_s(_roomNumber, strlen(roomNumber) + 1, roomNumber);
			}
		}
	}

	void checkIn(Date checkInDate) {

		_checkInDate = checkInDate;
	}

	void checkOut(Date checkOutDate) {

		_checkOutDate = checkOutDate;
	}

	void generateMenu() {

		char inpt;

		do
		{
			cout << "1. List rooms" << endl;
			cout << "2. Book a room" << endl;
			cout << "3. Check In" << endl;
			cout << "4. Check Out" << endl;

			int input;

			do
			{
				
				while (!(cin>>input)){
					system("cls");
					cout << "1. List rooms" << endl;
					cout << "2. Book a room" << endl;
					cout << "3. Check In" << endl;
					cout << "4. Check Out" << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}
			} while (input > 4 || input < 1);


			if (input == 1) {

				cout << "--------ROOMS--------" << endl;
				cout << endl;

				for (int i = 0; i < _totalRooms; i++) {

					cout << _rooms[i] << endl;
				}
			}
			else if (input == 2) {

				char roomChoice[5];


				cout << "--------ROOM BOOKING--------" << endl;
				cout << endl;

				if (booked) {

					cout << "you have already booked a room" << endl;
					system("pause>0");
					return;
				}
				
				cin.ignore();
				do {
					
					cout << "please input room number (ex 002)" << endl;
					cin.getline(roomChoice, 5);

				} while (strlen(roomChoice) != 3);

				this->bookRoom(roomChoice);
			}

			else if (input == 3) {

				cout << "--------CHECK IN--------" << endl;
				cout << endl;

				if (!booked) {
					cout << "You have not booked a room" << endl;
					system("pause>0");
					return;
				}

				if (checkedIn) {

					cout << "You have already checked in" << endl;
					system("pause>0");
					return;
				}

				char name[20];
				cin.ignore();
				cout << "Please input your name" << endl;
				cin.getline(name, 20);

				if (this->_fullName != nullptr) {

					delete[] _fullName;
					_fullName = nullptr;
				}

				this->_fullName = new char[strlen(name) + 1];
				strcpy_s(this->_fullName, strlen(name) + 1, name);

				regex regNumbers("^[0-9]{1,45}$");

				char contactNumber[20];
				do {
					cout << "Please input your contact number" << endl;
					cin.getline(contactNumber, 20);

				} while (regex_match(contactNumber, regNumbers) == false);

				if (this->_contactNumber != nullptr) {

					delete[] _contactNumber;
					_contactNumber = nullptr;
				}

				_contactNumber = new char[strlen(contactNumber) + 1];
				strcpy_s(_contactNumber, strlen(contactNumber) + 1, contactNumber);
				int d, m, y;
				cout << "Please input the check in date" << endl;
				do
				{
					cout << "Day: " << endl;
					cin >> d;

				} while (d < 0);

				do
				{
					cout << "Month: " << endl;
					cin >> m;

				} while (m < 0);

				do
				{
					cout << "Year: " << endl;
					cin >> y;

				} while (y < 0);


				Date checkInDate(d, m, y);

				this->checkIn(checkInDate);

				for (int i = 0; i < _totalRooms; i++) {

					if (strcmp(_rooms[i].getRoomNumber(), this->_roomNumber) == 0)
						_rooms[i].setRoomOccupied();
				}

				checkedIn = true;
			}

			else if (input == 4) {

				cout << "--------CHECK OUT--------" << endl;
				cout << endl;

				if (!checkedIn) {

					cout << "You have not checked in" << endl;
					return;
				}

				cout << "Please input the check out date" << endl;
				int d, m, y;

				do
				{
					cout << "Day: " << endl;
					cin >> d;

				} while (d < 0);

				do
				{
					cout << "Month: " << endl;
					cin >> m;

				} while (m < 0);

				do
				{
					cout << "Year: " << endl;
					cin >> y;

				} while (y < 0);


				Date checkOutDate(d, m, y);

				this->checkOut(checkOutDate);

				for (int i = 0; i < _totalRooms; i++) {

					if (strcmp(_rooms[i].getRoomNumber(), this->_roomNumber) == 0)
						_rooms[i].setRoomVacant();
				}

				booked = false;
				checkedOut = true;
				checkedIn = false;
			}

			cout << "(X=Exit, C=Continue)" << endl;
			cin >> inpt;


		} while (inpt != 'x');
	}

	friend ostream &operator <<(ostream &COUT, Guest &G) {

		COUT << "Name: " << G._fullName << endl;
		COUT << "Contact number: " << G._contactNumber << endl;
		COUT << "Room number: " << G._roomNumber << endl;
		COUT << "Check in date: " << G._checkInDate << endl;
		COUT << "Check out date: " << G._checkOutDate << endl;

		return COUT;
	}
};