#pragma once
#include<iostream>
#include"Exception.h"
#include"Common.h"
#include<string>
using namespace std;

class Ingredient {
	int id;
	string name;
	int count;
	double price;

public:
	Ingredient() {
		this->id = 0;
		this->name = "";
		this->count = 0;
		this->price = 0;
	}

	Ingredient(int id, string name, int count, double price) : Ingredient() {
		set_id(id);
		set_name(name);
		set_count(count);
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

	void set_count(int count) {
		if (count <= 0) { throw MyException(et4("Count", to_string(count), 1), __LINE__); }
		this->count = count;
	}

	void set_price(double price) {
		if (price <= 0) { throw MyException(et4("Price", to_string(price), 1), __LINE__); }
		this->price = price;
	}

	int get_id() const { return id; }
	string get_name() const { return name; }
	int get_count() const { return count; }
	double get_price() const { return price; }
#pragma endregion

#pragma region Methods
	void show(int r) {
		cout << r << ". ";
		cout << "[" << id << "] ";
		cout << name << ", " << count << ", " << price;
	}

	void show2(int r, int ind) {
		//ancaq adlari gosterir
		cout << r << ". ";
		cout << name;
		if (r != ind) { cout << ", "; }
	}

	double total() { return count * price; }
#pragma endregion

};

class IngredientStorage {
	Ingredient** ingredients;
	int ind;
	int capacity;
	int incrementSize;

public:
	IngredientStorage() {
		this->ingredients = nullptr;
		this->ind = 0;
		this->capacity = 0;
		this->incrementSize = 0;
	}

	IngredientStorage(int capacity, int incrementSize) {
		set_capacity(capacity);
		set_incrementSize(incrementSize);
		this->ingredients = new Ingredient * [capacity] {};
	}

	~IngredientStorage() {
		for (size_t i = 0; i < ind; i++) { delete ingredients[i]; }
		delete[] ingredients;
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

	Ingredient**& get_ingredients() { return ingredients; }
	int get_capacity() { return capacity; }
	int get_ind() { return ind; }
#pragma endregion

#pragma region Methods

	void add(Ingredient* ingredient) {
		bool flag = false;
		if (ingredient == nullptr) { throw MyException(string("Parameter ingredient can not be null pointer"), __LINE__); }

		//eger eyni adli ingredient varsa count update edilsin
		if (findIngredientByName(ingredient->get_name()) != -1) { flag = true; }

		if (flag) {
			updateCount2(ingredient->get_id(), ingredient->get_count(), '+');
		}
		else {
			//yer varmi?
			if (ind == capacity) {
				capacity += incrementSize;
				Ingredient** temp = new Ingredient * [capacity] {};
				for (size_t i = 0; i < ind; i++) { temp[i] = ingredients[i]; }
				temp[ind] = ingredient;
				delete[] ingredients;
				ingredients = temp;
			}

			ingredients[ind] = ingredient;
			ind++;
		}
	}

	void add2(Ingredient* ingredient) {
		//updateCount2 etmeden
		if (ingredient == nullptr) { throw MyException(string("Parameter ingredient can not be null pointer"), __LINE__); }

		//yer varmi?
		if (ind == capacity) {
			capacity += incrementSize;
			Ingredient** temp = new Ingredient * [capacity] {};
			for (size_t i = 0; i < ind; i++) { temp[i] = ingredients[i]; }
			temp[ind] = ingredient;
			delete[] ingredients;
			ingredients = temp;
		}

		ingredients[ind] = ingredient;
		ind++;
	}

	void removeByIndex(int index_, bool msg = false) {
		if (ind == 0) { throw MyException(string("There is not any object in the Storage"), __LINE__); }
		if (ind < 0) { throw MyException(et4("Index", "0"), __LINE__); }
		index_--;
		string n = ingredients[index_]->get_name();

		Ingredient** temp = new Ingredient * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (i < index_) { temp[i] = ingredients[i]; }
			else { temp[i] = ingredients[i + 1]; }
		}

		delete[] ingredients;
		ingredients = temp;
		ind--;

		if (msg) { cout << n << " was deleted..." << endl; }
	}

	void removeByName(string n, bool msg = false) {
		if (findIngredientByName(n) == -1) { throw MyException(string(n + ": this ingredient is not exist..."), __LINE__); }
		if (n.empty()) { throw MyException(et1("Ingredient"), __LINE__); }
		int r = 0;

		//main
		Ingredient** temp = new Ingredient * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_name() != n) {
				temp[r] = ingredients[i];
				r++;
			}
		}

		delete[] ingredients;
		ingredients = temp;
		ind--;

		if (msg) { cout << n << " was deleted..." << endl; }
	}

	void updateCount1(int id, int c) {
		//count deyisdirir (kokden)
		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_id() == id) {
				ingredients[i]->set_count(c);
				break;
			}
		}
	}

	void updateCount2(int id, int c, char oper) {
		if (c <= 0) { throw MyException(et4("Operator", "0"), __LINE__); }
		if (!(oper == '+' or oper == '-')) { throw MyException(string("Please use + or - operators"), __LINE__); }

		//sadece count artirir
		int tempCount = 0;

		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_id() == id) {
				tempCount = ingredients[i]->get_count();

				if (oper == '+') { tempCount += c; }
				else if (oper == '-') { tempCount += c; }

				ingredients[i]->set_count(tempCount);
				break;
			}
		}
	}

	void updateNameById(int id, string name) {
		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_id() == id) {
				ingredients[i]->set_name(name);
				break;
			}
		}
	}

	void updatePriceById(int id, double p) {
		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_id() == id) {
				ingredients[i]->set_price(p);
				break;
			}
		}
	}

	void updatePriceByName(string name, double p) {
		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_name() == name) {
				ingredients[i]->set_price(p);
				break;
			}
		}
	}

	int findIngredientByName(string name) {
		//indeks nomresini return edir
		for (size_t i = 0; i < ind; i++) { if (name == ingredients[i]->get_name()) { return i; } }
		return -1;
	}

	int findIngredientById(int id) {
		//indeks return edir
		for (size_t i = 0; i < ind; i++) {
			if (ingredients[i]->get_id() == id) {
				return i;
			}
		}
		return -1;
	}

	void show(int t) {
		if (ingredients == nullptr) { throw MyException(string("There is not any ingredients in the Stock"), __LINE__); }

		for (size_t i = 0; i < ind; i++) {

			//show
			if (t == 1) {
				ingredients[i]->show(i + 1);
				cout << endl;
			}

			//show2
			if (t == 2) {
				ingredients[i]->show2(i + 1, ind);
				if ((i + 1) % 3 == 0) { cout << endl; } //i+1 % 3 (3-3 duzmek)
			}

		}

		cout << endl << endl;
	}

#pragma endregion

};


