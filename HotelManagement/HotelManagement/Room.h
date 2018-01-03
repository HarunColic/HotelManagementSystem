#pragma once
#include<iostream>
using namespace std;

enum RoomType { AC, NoAC };
char *RoomTypechr[]{ "AC","NoAC" };
enum RoomStatus { Vacant, Reserved, Occupied };
char *RoomStatuschr[]{ "Vacant", "Reserved", "Occupied" };
int roomNo = 1;

//this functioin generates the next room number which restricts the user from adding random room numbers and possibly leaving a gap between them.
char *generateRoomNumber() {

	int temp = roomNo;
	int counter = 0;

	do
	{
		temp /= 10;
		counter++;

	} while (temp != 0);

	char *generatedNumber;

	char numberToChar[10];
	char roomNumber[10];

	_itoa_s(roomNo, numberToChar, 10, 10);

	strncpy_s(roomNumber, 10, "000", 3 - counter);

	strcat_s(roomNumber, 10, numberToChar);

	generatedNumber = new char[strlen(roomNumber) + 1];
	strcpy_s(generatedNumber, strlen(roomNumber) + 1, roomNumber);

	roomNo++;

	return generatedNumber;
}

class Room
{
	char * _roomNumber; //auto generated number (ex: 003)
	char * _roomDescription;
	float _dailyRoomPrice;
	RoomType _roomType;
	RoomStatus _roomStatus;

public:

	Room()
	{
		char * newRoomNumber = generateRoomNumber();

		int length = strlen(newRoomNumber) + 1;
		_roomNumber = new char[length];
		strcpy_s(_roomNumber, length, newRoomNumber);

		delete[] newRoomNumber;
		newRoomNumber = nullptr;

		_roomDescription = nullptr;
	}

	Room(char *roomDescripton, float dailyRoomPrice, RoomType roomType, RoomStatus roomStatus) {

		char * newRoomNumber = generateRoomNumber();

		int length = strlen(newRoomNumber) + 1;
		_roomNumber = new char[length];
		strcpy_s(_roomNumber, length, newRoomNumber);

		delete[] newRoomNumber;
		newRoomNumber = nullptr;


		_roomDescription = new char[strlen(roomDescripton) + 1];
		strcpy_s(_roomDescription, strlen(roomDescripton) + 1, roomDescripton);

		_dailyRoomPrice = dailyRoomPrice;

		_roomType = roomType;

		_roomStatus = roomStatus;
	}

	Room(Room &R) {

		cout << R._roomNumber << endl;
		/*
		if (_roomNumber != nullptr) {

		delete[] _roomNumber;
		_roomNumber = nullptr;

		if (_roomDescription != nullptr) {

		delete[] _roomDescription;
		_roomDescription = nullptr;
		}
		}*/

		_roomNumber = new char[strlen(R._roomNumber) + 1];
		strcpy_s(_roomNumber, strlen(R._roomNumber) + 1, R._roomNumber);

		_roomDescription = new char[strlen(R._roomDescription) + 1];
		strcpy_s(_roomDescription, strlen(R._roomDescription) + 1, R._roomDescription);

		_dailyRoomPrice = R._dailyRoomPrice;

		_roomType = R._roomType;

		_roomStatus = R._roomStatus;
	}

	~Room()
	{
		delete[] _roomNumber;
		_roomNumber = nullptr;

		delete[] _roomDescription;
		_roomDescription = nullptr;
	}

	char *getRoomNumber() {

		return _roomNumber;
	}

	float getRoomPrice() {

		return _dailyRoomPrice;
	}

	void operator =(Room &R) {

		if (_roomNumber != nullptr) {

			delete[] _roomNumber;
			_roomNumber = nullptr;

			if (_roomDescription != nullptr) {

				delete[] _roomDescription;
				_roomDescription = nullptr;
			}
		}

		_roomNumber = new char[strlen(R._roomNumber) + 1];
		strcpy_s(_roomNumber, strlen(R._roomNumber) + 1, R._roomNumber);

		_roomDescription = new char[strlen(R._roomDescription) + 1];
		strcpy_s(_roomDescription, strlen(R._roomDescription) + 1, R._roomDescription);

		_dailyRoomPrice = R._dailyRoomPrice;

		_roomType = R._roomType;

		_roomStatus = R._roomStatus;
	}

	void modifyRoomDescription() {

		char newDescription[50];

		cout << "Please enter a new description" << endl;
		cin.ignore();
		cin.getline(newDescription, 50);
		cin.ignore();

		if (_roomDescription != nullptr) {

			delete[] _roomDescription;
			_roomDescription = nullptr;
		}

		_roomDescription = new char[strlen(newDescription) + 1];
		strcpy_s(_roomDescription, strlen(newDescription) + 1, newDescription);

		cout << endl;
		cout << "New room description: " << _roomDescription << endl;
	}

	void modifyRoomPrice() {

		float newPrice;

		cout << "Please enter a new price" << endl;

		do
		{
			cin >> newPrice;

		} while (newPrice < 0);

		_dailyRoomPrice = newPrice;


		cout << "New room price: " << _dailyRoomPrice << endl;
	}

	void modifyRoomType() {

		cout << "Please enter a new tupe" << endl;
		cout << "1. AC" << endl;
		cout << "2. NoAC" << endl;

		int input;

		do
		{
			cin >> input;

		} while (input > 2 || input < 1);


		if (input == 1)
			_roomType = AC;
		else
			_roomType = NoAC;

		cout << "New room type: " << RoomTypechr[_roomType] << endl;
	}

	void modifyRoomStatus() {


		cout << "Please insert new Status" << endl;
		cout << "1. Vacant" << endl;
		cout << "2. Reserved" << endl;
		cout << "3. Occupied" << endl;

		int input;

		do
		{
			cin >> input;

		} while (input < 0 || input> 3);

		if (input == 1)
			_roomStatus = Vacant;
		else if (input == 2)
			_roomStatus = Reserved;
		else
			_roomStatus = Occupied;

		cout << "New room status: " << _roomStatus << endl;

	}

	void setRoomReserved() {

		_roomStatus = Reserved;
	}

	void setRoomOccupied() {

		_roomStatus = Occupied;
	}

	void setRoomVacant() {

		_roomStatus = Vacant;
	}

	friend ostream &operator <<(ostream &COUT, Room &R) {

		COUT << "Room number: " << R._roomNumber << endl;
		COUT << "Room Description: " << R._roomDescription << endl;
		COUT << "Room price (per day)" << R._dailyRoomPrice << endl;
		COUT << "Room type: " << RoomTypechr[R._roomType] << endl;
		COUT << "Room status: " << RoomStatuschr[R._roomStatus] << endl;
		return COUT;
	}
};
