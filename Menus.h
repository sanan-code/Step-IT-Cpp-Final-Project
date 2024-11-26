#pragma once
#include<iostream>
#include<Windows.h>
#include"Common.h"
using namespace std;

void programHeader() {
	cout << "\tFood Order Management Program" << endl;
	cout << "\nWait please. We are working on it ";
	for (size_t i = 0; i < 4; i++) {
		cout << ". ";
		Sleep(500);
	}
	system("cls");
}

int menu1() {
	//girisdeki esas menyu

	system("cls");
	cout << "1. Log in" << endl;
	cout << "2. Sign in" << endl;
	cout << "3. Exit" << endl;

	int selection = getMenuSelection(1, 3);
	return selection;
}

int menu2() {
	//istifadecilerin sisteme daxil olmasi

	cout << "Log in" << endl;
	cout << "1. As a customer" << endl;
	cout << "2. As an employee" << endl;
	cout << "3. As an admin" << endl;
	cout << "4. go back" << endl;

	int selection = getMenuSelection(1, 4);
	return selection;
}

int menu3() {
	//istifadecilerin qeydiyyatdan kecmesi

	cout << "Sign in" << endl;
	cout << "1. As a customer" << endl;
	cout << "2. As an employee" << endl;
	cout << "3. go back" << endl;

	int selection = getMenuSelection(1, 3);
	return selection;
}

int menu4_1() {
	//girisden sonra (after enterance) admin

	cout << "\nAfter entrance admin menu" << endl;
	cout << "1. add ingredient" << endl;
	cout << "2. remove ingredient" << endl;
	cout << "3. update count of ingredient" << endl;
	cout << "4. show all ingredients" << endl;
	cout << "5. show restaurant balance" << endl;
	cout << "6. history" << endl;
	cout << "7. add new meal" << endl;
	cout << "8. delete meal" << endl;
	cout << "9. show menu" << endl;
	cout << "10. show full menu" << endl;
	cout << "11. complete menu" << endl;
	cout << "12. show all users" << endl;
	cout << "13. go back" << endl;

	int selection = getMenuSelection(1, 11);
	return selection;
}

int menu4_1_1() {
	//history secimleri (admin)

	cout << "\n1. ingredients buy history" << endl;
	cout << "2. go back" << endl;

	int selection = getMenuSelection(1, 2);
	return selection;
}

int menu4_2() {
	//girisden sonra customer

	cout << "\n1. Order a meal" << endl;
	cout << "2. Show menu" << endl;
	cout << "3. Show history" << endl;
	cout << "4. go back" << endl;

	int selection = getMenuSelection(1, 4);
	return selection;
}

int menu4_3() {
	//girisden sonra employee

	cout << "\n1. show info";
	cout << "\n2. go back" << endl;

	int selection = getMenuSelection(1, 2);
	return selection;
}