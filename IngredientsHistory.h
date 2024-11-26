#pragma once
#include<iostream>
#include"Exception.h"
#include<string>
using namespace std;

class IngredientsHistory {
	string name;
	int count;
	string date;
public:
	IngredientsHistory() {
		this->name = "";
		this->count = count;
		this->date = "";
	}

	IngredientsHistory(string name, int count) : IngredientsHistory() {
		set_name(name);
		this->count = count;
		this->date = __DATE__;
	}

#pragma region Setter and Getter
	void set_name(string name) {
		if (name.empty()) { throw MyException(et1("Name"), __LINE__); }
		this->name = name;
	}

	void set_count(int count) {
		if (count <= 0) { throw MyException(et4("Count", "0"), __LINE__); }
		this->count = count;
	}

	void set_date(string date) {
		if (name.empty()) { throw MyException(et1("Date"), __LINE__); }
		this->date = date;
	}

	string get_name() { return name; }
	int get_count() { return count; }
	string get_date() { return date; }
#pragma endregion

};

class IngredientsHistoryStorage {
	IngredientsHistory** ingredientshistories;
	int ind;
	int capacity;
	int incrementSize;

	IngredientsHistoryStorage() {
		this->ingredientshistories = nullptr;
		this->ind = 0;
		this->capacity = 0;
		this->incrementSize = 0;
	}
public:
	IngredientsHistoryStorage(int capacity, int incrementSize) {
		set_capacity(capacity);
		set_incrementSize(incrementSize);
		this->ingredientshistories = new IngredientsHistory * [capacity] {};
	}

	~IngredientsHistoryStorage() {
		for (size_t i = 0; i < ind; i++) { delete ingredientshistories[i]; }
		delete[] ingredientshistories;
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

	IngredientsHistory**& get_ingredientshistories() { return ingredientshistories; }
	int get_capacity() { return capacity; }
	int get_ind() { return ind; }
#pragma endregion

#pragma region Methods
	void add(IngredientsHistory* ingredienthistory) {
		if (ingredienthistory == nullptr) { throw MyException(string("Parameter ingredient can not be null pointer"), __LINE__); }

		//yer varmi?
		if (ind == capacity) {
			capacity += incrementSize;
			IngredientsHistory** temp = new IngredientsHistory * [capacity] {};
			for (size_t i = 0; i < ind; i++) { temp[i] = ingredientshistories[i]; }
			temp[ind] = ingredienthistory;
			delete[] ingredientshistories;
			ingredientshistories = temp;
		}

		ingredientshistories[ind] = ingredienthistory;
		ind++;
	}

	int get_total_count() {
		int result = 0;
		for (size_t i = 0; i < ind; i++) {
			result += ingredientshistories[i]->get_count();
		}
		return result;
	}

	void make_history_table() {
		//butun arrayi cedvel seklinde cixarir
		for (size_t i = 0; i < ind; i++) {
			cout << i + 1 << ". ";
			cout << ingredientshistories[i]->get_name() << " | ";
			cout << ingredientshistories[i]->get_count() << " | ";
			cout << ingredientshistories[i]->get_date();
			cout << endl;
		}
	}
#pragma endregion

};

