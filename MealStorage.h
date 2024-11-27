#pragma once
#include<iostream>
#include"Exception.h"
#include"string"
#include"IngredientsManagement.h"
#include"Common.h"
using namespace std;

class Meal {
	int id;
	string name;
	double price;

public:
	Meal() {
		int id = 0;
		this->name = "";
		this->price = 0;
	}

	Meal(int id, string name, double price) {
		set_id(id);
		set_name(name);
		set_price(price);
	}

#pragma region Setter and Getter
	void set_id(int id) {
		if (id <= 0) { throw MyException(et4("ID", "0"), __LINE__); }
		this->id = id;
	}

	void set_name(string name) {
		if (name.empty()) { throw MyException(et1("Name"), __LINE__); }
		if (name.length() < 2) { throw MyException(string("Name can not be less than 3 characters"), __LINE__); }
		this->name = name;
	}

	void set_price(double price) {
		if (price <= 0) { throw MyException(et4("Price", "0"), __LINE__); }
		this->price = price;
	}

	int get_id() const { return id; }
	string get_name() const { return name; }
	double get_price() { return price; }
#pragma endregion

#pragma region Methods
	void show(int r) {
		cout << r << ". ";
		cout << "[" << id << "] ";
		cout << name;
		cout << " (" << price << ")";
	}

#pragma endregion

};

class MealStorage {
	Meal** meals;
	int ind;
	int capacity;
	int incrementSize = 0;

public:
	MealStorage() {
		this->meals = nullptr;
		this->ind = 0;
		this->capacity = 0;
		this->incrementSize = 0;
	}

	MealStorage(int capacity, int incrementSize) {
		set_capacity(capacity);
		set_incrementSize(incrementSize);
		this->meals = new Meal * [capacity] {};
	}

	~MealStorage() {
		for (size_t i = 0; i < ind; i++) { delete meals[i]; }
		delete[] meals;
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

	Meal**& get_meals() { return meals; }
	int get_capacity() { return capacity; }
	int get_ind() { return ind; }
	int get_incrementSize() { return incrementSize; }
#pragma endregion

#pragma region Methods
	void add(Meal*& meal) {
		if (meal == nullptr) { throw MyException(string("Parameter ingredient can not be null pointer"), __LINE__); }

		//yer varmi?
		if (ind == capacity) {
			capacity += incrementSize;
			Meal** temp = new Meal * [capacity] {};
			for (size_t i = 0; i < ind; i++) { temp[i] = meals[i]; }
			temp[ind] = meal;
			delete[] meals;
			meals = temp;
		}

		meals[ind] = meal;
		ind++;
	}

	void removeById(int id, bool msg = false) {
		if (id <= 0) { throw MyException(et4("Meal", "0"), __LINE__); }
		int r = 0;

		//main
		Meal** temp = new Meal * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (meals[i]->get_id() != id) {
				temp[r] = meals[i];
				r++;
			}
		}

		delete[] meals;
		meals = temp;
		ind -= (ind - r);

		if (msg) { cout << id << ": id was deleted..." << endl; }
	}

	void removeByName(string n, bool msg = false) {
		if (n.empty()) { throw MyException(et1("Meal"), __LINE__); }
		int r = 0;

		//main
		Meal** temp = new Meal * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (meals[i]->get_name() != n) {
				temp[r] = meals[i];
				r++;
			}
		}

		delete[] meals;
		meals = temp;
		ind -= (ind - r);

		if (msg) { cout << n << " was deleted..." << endl; }
	}

	void updateMealNameById(int id, string newName, bool msg = false) {
		for (size_t i = 0; i < ind; i++) {
			if (meals[i]->get_id() == id) {
				meals[i]->set_name(newName);
				break;
			}
		}

		if (msg) { cout << newName << " updated" << endl; }
	}

	void updateMealPriceById(int id, double price, bool msg = false) {
		for (size_t i = 0; i < ind; i++) {
			if (meals[i]->get_id() == id) {
				meals[i]->set_price(price);
				break;
			}
		}

		if (msg) { cout << price << " updated"; }
	}

	int findMealById(int id) {
		//indeks nomresini qaytarir

		for (size_t i = 0; i < ind; i++) {
			if (meals[i]->get_id() == id) {
				return i;
			}
		}

		return -1;
	}

	int findMealByName(string name) {
		//indeks nomresini qaytarir

		for (size_t i = 0; i < ind; i++) {
			if (meals[i]->get_name() == name) {
				return i;
			}
		}

		return -1;
	}

	void show() {
		for (size_t i = 0; i < ind; i++) {
			meals[i]->show(i + 1);
			cout << endl;
		}
	}

#pragma endregion

};


