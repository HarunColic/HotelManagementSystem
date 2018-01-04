#include<iostream>
#include<cmath>
#include<regex>
#include"Room.h"
#include"Date.h"
#include"User.h"
#include"Employee.h"
#include"Guest.h"
using namespace std;

//this function is called when the employee chooses to add a new room
Room generateRoom() {

	char roomDesc[25];
	float roomPrice;
	RoomType roomType;
	RoomStatus roomStatus;
	int choice;

	cin.ignore();
	cout << "Please input the room description" << endl;
	cin.getline(roomDesc, 25);
	cin.ignore();

	cout << "Please enter the room price" << endl;
	cin >> roomPrice;

	cout << "Chose the room type" << endl;
	cout << "1. AC" << endl;
	cout << "2. NoAC" << endl;

	do
	{
		cin >> choice;

	} while (choice < 1 || choice>2);

	if (choice == 1)
		roomType = AC;
	else
		roomType = NoAC;

	roomStatus = Vacant;

	Room room(roomDesc, roomPrice, roomType, roomStatus);

	return room;
}

int main() {

	Room room1("2 beds", 19.99, AC, Vacant);
	Room room2("3 beds", 29.99, AC, Vacant);
	Room room3(" beach view", 119.99, AC, Vacant);

	User *users[2];

	users[0] = new Employee;
	users[1] = new Guest;

	Employee *emp = dynamic_cast<Employee *>(users[0]);
	Guest * gst = dynamic_cast<Guest *>(users[1]);

	emp->addRoom(room1);
	emp->addRoom(room2);
	emp->addRoom(room3);

	system("cls");

	char input;

	do
	{

		cout << "1. Employee menu" << endl;
		cout << "2. Guest menu" << endl;

		int inputMenu;
	
		do {

			while (!(cin >> inputMenu)) {

				system("cls");
				cout << "1. Employee menu" << endl;
				cout << "2. Guest menu" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
		} while (inputMenu < 1 || inputMenu > 2);

		if (inputMenu == 1) {

			char submenuInput;

			do
			{

				emp->generateMenu();

				int choice;

				do {
					
					while (!(cin >> choice)) {
						system("cls");
						emp->generateMenu();
						cin >> choice;
						cin.clear();
						cin.ignore(100, '\n');

					}
				} while (choice < 1 || choice > 4);

				if (choice == 1) {

					if (_totalRooms == 0)
						cout << "No rooms added yet" << endl;
					else {

						for (int i = 0; i < _totalRooms; i++) {

							cout << _rooms[i] << endl;
						}
					}
				}
				else if (choice == 2) {

					if (_totalRooms == 0) {

						cout << "No rooms to modify" << endl;
						system("pause>0");
						break;
					}
					char roomNoInput[5];
					bool checkRoom = false;

					try
					{
						cin.ignore();
						cout << "Input the number of the room you wish to modify" << endl;
						cin.getline(roomNoInput, 5);

						for (int i = 0; i < _totalRooms; i++) {

							if (strcmp(_rooms[i].getRoomNumber(), roomNoInput) == 0)
								checkRoom = true;
						}

						if (!checkRoom) {
							throw exception("Room doesnt exist");
						}

						emp->modifyRoom(roomNoInput);
					}
					catch (exception &e)
					{
						cout << e.what() << endl;
					}
				}
				else if (choice == 3) {

					emp->addRoom(generateRoom());
				}
				else if (choice == 4) {


					if (_totalRooms > 0 && checkedOut == true)
						emp->generateBill(*gst);
					else
						cout << "Can't generate bill at this moment" << endl;
				}

				cout << "(X=Exit, C=Continue)" << endl;
				cin >> submenuInput;

			} while (submenuInput != 'x');
		}

		else {
			gst->generateMenu();
		}

		system("cls");
		cout << "1. employee menu" << endl;
		cout << "2. guest menu" << endl;

		cout << "  (X=Exit, C = Continue)" << endl;

		cin >> input;
	} while (input != 'x');

	delete[] _rooms;
	_rooms = nullptr;

	return 0;
}