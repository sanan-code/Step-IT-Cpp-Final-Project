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
	int get_incrementSize() { return incrementSize; }

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

	void show() {
		for (size_t i = 0; i < ind; i++) {
			menus[i]->show(i + 1);
		}
	}

	void show2(MealStorage& ms) {
		//ancaq olmayanlari goster
		//meqsed ingredientleri elave etmekdi (ad ve sayini)

		bool flag = false;
		int r = 1;

		for (size_t i = 0; i < ms.get_ind(); i++) { //MealStorage
			for (size_t j = 0; j < ind; j++) { //MenuStorage
				if (ms.get_meals()[i]->get_id() == menus[j]->get_mealId()) { flag = true; }
			}

			//olmayanlari goster
			if (!flag) {
				ms.get_meals()[i]->show(r);
				r++;
			}

			flag = false;
		}

	}

	void show3(MealStorage& ms, IngredientStorage& is) {
		//adi, qiymeti ve ingredient siyahisi olan

		int mealId;
		int ingId;

		for (size_t i = 0; i < ms.get_ind(); i++) { //meals
			mealId = ms.get_meals()[i]->get_id();
			ms.get_meals()[ms.findById(mealId)]->show(i + 1);

			for (size_t j = 0; j < ind; j++) { //menus
				if (mealId == menus[j]->get_mealId()) {
					ingId = menus[j]->get_ingId();

					is.get_ingredients()[is.getIngredientById(ingId)]->show2(j + 1);
				}
			}

		}

	}

#pragma endregion

};
