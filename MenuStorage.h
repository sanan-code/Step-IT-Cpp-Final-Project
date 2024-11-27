#pragma once
#include<iostream>
#include"Exception.h"
#include"Common.h"
#include"MealStorage.h"

class Menu {
	int mealId;
	int ingId;
	int ingCount;

public:

	Menu() {
		this->mealId = 0;
		this->ingId = 0;
		this->ingCount = 0;
	}

	Menu(int mealId, int ingId, int ingCount) {
		set_mealId(mealId);
		set_ingId(ingId);
		set_ingCount(ingCount);
	}

#pragma region Setter and Getter
	void set_mealId(int mealId) {
		if (mealId <= 0) { throw MyException(et4("Meal id", "0"), __LINE__); }
		this->mealId = mealId;
	}

	void set_ingId(int ingId) {
		if (mealId <= 0) { throw MyException(et4("Ingredient id", "0"), __LINE__); }
		this->ingId = ingId;
	}

	void set_ingCount(int ingCount) {
		if (mealId <= 0) { throw MyException(et4("Ingredient count", "0"), __LINE__); }
		this->ingCount = ingCount;
	}

	int get_mealId()const { return mealId; }
	int get_ingId()const { return ingId; }
	int get_ingCount()const { return ingCount; }
#pragma endregion

#pragma region Methods

	void show(int r) {
		cout << r << " -----" << endl;
		cout << "Meal ID: " << mealId << endl;
		cout << "Ingredient ID: " << ingId << endl;
		cout << "Ingredient count: " << ingCount << endl;
		cout << endl;
	}

#pragma endregion

};

class MenuStorage {
	Menu** menus;
	int ind;
	int capacity;
	int incrementSize = 0;

public:
	MenuStorage() {
		this->menus = nullptr;
		this->ind = 0;
		this->capacity = 0;
		this->incrementSize = 0;
	}

	MenuStorage(int capacity, int incrementSize) {
		set_capacity(capacity);
		set_incrementSize(incrementSize);
		this->menus = new Menu * [capacity] {};
	}

#pragma region Setter and Getter
	void set_capacity(int capacity) {
		if (capacity < 5) { throw MyException(et4("Capacity", to_string(capacity), 1), __LINE__); }
		this->capacity = capacity;
	}

	void set_incrementSize(int incrementSize) {
		if (incrementSize < 3) { throw MyException(et4("Increment size", to_string(incrementSize), 1), __LINE__); }
		this->incrementSize = incrementSize;
	}

	Menu**& get_menus() { return menus; }
	int get_capacity() { return capacity; }
	int get_ind() { return ind; }
#pragma endregion

#pragma region Methods

	void add(Menu*& menu) {
		if (menu == nullptr) { throw MyException(string("Parameter ingredient can not be null pointer"), __LINE__); }

		//yer varmi?
		if (ind == capacity) {
			capacity += incrementSize;
			Menu** temp = new Menu * [capacity] {};
			for (size_t i = 0; i < ind; i++) { temp[i] = menus[i]; }
			temp[ind] = menu;
			delete[] menus;
			menus = temp;
		}

		menus[ind] = menu;
		ind++;
	}

	void removeById(int id, bool msg = false) {
		if (id <= 0) { throw MyException(et4("Menu id", "0"), __LINE__); }
		int r = 0;

		//main
		Menu** temp = new Menu * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (menus[i]->get_mealId() != id) {
				temp[r] = menus[i];
				r++;
			}
		}

		delete[] menus;
		menus = temp;
		ind -= (ind - r);

		if (msg) { cout << id << ": id was deleted..." << endl; }
	}

	//gonderilen meal idnin melumatlarini gosterir
	void show1(int mealId, MealStorage& ms, IngredientStorage& is) {
		int ingId = 0;

		cout << "Meal name: " << ms.get_meals()[ms.findMealById(mealId)]->get_name() << endl;

		for (size_t i = 0; i < ind; i++) { //menu uzerinde addimlama
			if (menus[i]->get_mealId() == mealId) {
				ingId = menus[i]->get_ingId();

				cout << is.get_ingredients()[is.findIngredientById(ingId)]->get_name();
				cout << " (" << menus[i]->get_ingCount() << ")";
				cout << ", ";

			}
		}

	}

#pragma endregion

};
