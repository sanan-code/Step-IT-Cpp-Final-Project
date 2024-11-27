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

int menu2_1() {
	//girisden sonra customer

	cout << "\n1. Order a meal" << endl;
	cout << "2. Show menu" << endl;
	cout << "3. Show history" << endl;
	cout << "4. go back" << endl;

	int selection = getMenuSelection(1, 4);
	return selection;
}

int menu2_2() {
	//girisden sonra employee

	cout << "\n1. show info";
	cout << "\n2. go back" << endl;

	int selection = getMenuSelection(1, 2);
	return selection;
}

int menu2_3() {
	//girisden sonra admin
	cout << "\n1. Ingredients" << endl;
	cout << "2. Meals" << endl;
	cout << "3. Menus" << endl;
	cout << "4. Other" << endl;
	cout << "5. go back" << endl;

	int selection = getMenuSelection(1, 5);
	return selection;
}

int menu2_3_1() {
	//admin ingredients

	cout << "\n1. add ingredient" << endl;
	cout << "2. update ingredient name" << endl;
	cout << "3. update count of ingredient" << endl;
	cout << "4. remove ingredient" << endl;
	cout << "5. show all ingredients" << endl;
	cout << "6. go back" << endl;

	int selection = getMenuSelection(1, 6);
	return selection;
}

int menu2_3_2() {
	//admin meals

	cout << "\n1. add meal" << endl;
	cout << "2. update meal" << endl;
	cout << "3. remove meal" << endl;
	cout << "4. show all meals" << endl;
	cout << "5. go back" << endl;

	int selection = getMenuSelection(1, 5);
	return selection;
}

int menu2_3_3() {
	//admin menus

	cout << "\n1. add menu" << endl;
	cout << "2. update menu" << endl;
	cout << "3. remove menu" << endl;
	cout << "4. show all menus" << endl;
	cout << "5. go back" << endl;

	int selection = getMenuSelection(1, 5);
	return selection;
}

int menu2_3_4() {
	//admin others

	cout << "\n1. Restaurant balance" << endl;
	cout << "2. Show all users" << endl;
	cout << "3. Ingredient history" << endl;
	cout << "4. go back" << endl;

	//historyler artir

	int selection = getMenuSelection(1, 4);
	return selection;
}

int menu3() {
	//qeydiyyatdan kecme

	cout << "Sign in" << endl;
	cout << "1. As a customer" << endl;
	cout << "2. As an employee" << endl;
	cout << "3. go back" << endl;

	int selection = getMenuSelection(1, 3);
	return selection;
}

