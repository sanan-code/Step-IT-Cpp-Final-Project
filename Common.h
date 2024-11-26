#pragma once
#include<iostream>
#include<string>
#include <ctime>
#include<Windows.h>
using namespace std;

int getCurrentYear() {
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	if (localtime_s(&localTime, &now) != 0) {
		std::cerr << "Error retrieving local time!" << std::endl;
		return -1;
	}
	return 1900 + localTime.tm_year;
}

int extractFromDate(int t, string d) {
	//gonderilen tarixden gun ay il cixaris edir
	//default olaraq ili return edir

	switch (t) {
	case 1: //year
		return stoi(d.substr(6, 4));
	case 2: //month
		return stoi(d.substr(3, 2));
	case 3: //day
		return stoi(d.substr(0, 2));
	default:
		return stoi(d.substr(6, 4));
	}
}

int calculcateAge(string d) {
	//gonderilen tarixe esases yasi hesablayie
	return getCurrentYear() - extractFromDate(1, d);
}

string convertBoolToString(bool b, int t) {
	//b => deyer
	/*
	t =>> type
		1 - kisi(true), qadin(false)
		2 - True, False
	*/

	switch (t)
	{
	case 1:
		if (b) { return "Male"; }
		else if (!b) { return "Female"; }
	case 2:
		if (b) { return "True"; }
		else if (!b) { return "False"; }
	default:
		if (b) { return "True"; }
		else if (!b) { return "False"; }
		break;
	}
}

int findChrInStr(string str, char chr) {
	//string icinde gonderilmis karakteri axtarir
	//indeksini return edir
	//default -1;

	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == chr) { return i; }
	}
	return -1;
}

int countOfChrsInStr(string str, char chr) {
	int counter = 0;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == chr) { counter++; }
	}
	return counter;
}

int getMenuSelection(int min, int max) {
	int a;
	cout << "Select between " << min << " and " << max << ": ";
	cin >> a;
	cin.ignore();

	if (a < 10) { if (!(49 <= (a + 48) and (a + 48) <= 57)) { throw MyException(string("Invalid selection..."), __LINE__); } }
	if (!(min <= a and a <= max)) { throw MyException(et2("Selection", to_string(min), to_string(max)), __LINE__); }

	return a;
}

string getString(string t1) {
	string result = "";
	cout << "Enter " << t1 << ": ";
	cin >> result;
	return result;
}

void sleep_dots(int c, int ms) {
	cout << endl << endl;
	for (size_t i = 0; i < c; i++) {
		cout << ". ";
		Sleep(ms);
	}
}





/*
* loaf from file ucun
* 
	if (
	(48 <= int(ch) and int(ch) <= 57) or
	(65 <= int(ch) and int(ch) <= 90) or
	(97 <= int(ch) and int(ch) <= 122) or ch == '^')
*/


//Account read and write test
//void test1() {
//	AccountsStorage as(5, 3);
//
//	Account* ac1 = new Customer("Sanan", "Gambarov", "asdfdfd1", "afasgd@dgsd", "sdfasdg", true, "12.12.2008", "sananUser", "sanan123", 852);
//	Account* ac2 = new Customer("Kamran", "Gambarov", "asdfdfd2", "afasgd@dgsd", "sdfasdg", true, "12.12.2008", "kamranUser", "sanan123", 2345);
//	Account* ac3 = new Employee("sdfgsdsd", "sdsdsf", "asdfdfd3", "afasgd@dgsd", "sdfasdg", false, "12.12.2008", "tarlanUser", "sanan123", 777);
//	Account* ac4 = new Customer("dfhdfs", "sdsdsf", "asdfdfd4", "afasgsdfd@ds", "sdfasdg", false, "12.12.2008", "hamidUser1", "sanan123", 999);
//	Account* ac5 = new Employee("Test", "sdsdsf", "asdfdfd4", "afasgsdfd@ds", "sdfasdg", false, "12.12.2008", "hamidUser", "sanan123", 999);
//
//	as.add(ac1);
//	as.add(ac2);
//	as.add(ac3);
//	as.add(ac4);
//	as.add(ac5);
//
//	latf(as);
//}


//Ingredient read and write test
//void test1(IngredientStorage& is) {
//
//	Ingredient* i1 = new Ingredient("Kartof", 5, 0.5);
//	Ingredient* i2 = new Ingredient("Kok", 10, 0.7);
//	Ingredient* i3 = new Ingredient("Su", 10, 0.3);
//	Ingredient* i4 = new Ingredient("Alma", 20, 1.2);
//	is.add(i1);
//	is.add(i2);
//	is.add(i3);
//	is.add(i3);
//	litf(is);
//}


//IngredientsHistoryStorage ihs(10, 3);
//IngredientsHistory* ih1 = new IngredientsHistory("Name1", 5);
//IngredientsHistory* ih2 = new IngredientsHistory("Name2", 6);
//IngredientsHistory* ih3 = new IngredientsHistory("Name3", 7);
//ihs.add(ih1);
//ihs.add(ih2);
//ihs.add(ih3);
//lihtf(ihs);




//void test(MealStorage& ms) {
//	//m1
//	Ingredient* i1 = new Ingredient("Kartof m1", 5, 1);
//	Ingredient* i2 = new Ingredient("Kok m1", 10, 2);
//
//	IngredientStorage* is1 = new IngredientStorage(10, 3);
//	is1->add(i1);
//	is1->add(i2);
//
//	Meal* m1 = new Meal("Meal 1", 15, is1);
//
//	//m2
//	Ingredient* i5 = new Ingredient("Kartof m2", 5, 3);
//	Ingredient* i6 = new Ingredient("Kok m3", 10, 4);
//	Ingredient* i7 = new Ingredient("Su m4", 10, 5);
//	Ingredient* i8 = new Ingredient("Alma m5", 20, 6);
//
//	IngredientStorage* is2 = new IngredientStorage(10, 3);
//	is2->add(i5);
//	is2->add(i6);
//	is2->add(i7);
//	is2->add(i8);
//
//	Meal* m2 = new Meal("Meal 2", 12, is2);
//
//	//meal storage-e elave edir
//	ms.add(m1);
//	ms.add(m2);
//
//	lmtf(ms);
//}



/*

void test1(MenuStorage& menuS) {

	Meal* meal1 = new Meal(100, "Test", 541);

	Ingredient* i1 = new Ingredient(1, 5);
	Ingredient* i2 = new Ingredient(2, 10);
	Ingredient* i3 = new Ingredient(3, 8);
	Ingredient* i4 = new Ingredient(4, 9);

	IngredientStorage is(5, 3);
	is.add2(i1);
	is.add2(i2);
	is.add2(i3);
	is.add2(i4);

	Menu* menu = new Menu(meal1, is);

	MenuStorage ms(5, 3);
	ms.add(menu);

	lmenutf(ms);
}

*/



/*
MenuStorage menuS(5, 3);

	Menu* m1 = new Menu(2, 1, 3);
	Menu* m2 = new Menu(2, 2, 4);
	Menu* m3 = new Menu(2, 3, 5);

	menuS.add(m1);
	menuS.add(m2);
	menuS.add(m3);

	lmenustf(menuS);
*/