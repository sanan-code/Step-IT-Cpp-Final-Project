#pragma once
#include<iostream>
#include"Exception.h"
#include"Common.h"
#include<string>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Account {
	string username;
	string password;
	int accType;
public:
	Account() {
		this->username = "";
		this->password = "";
		this->accType = 0;
	}

	Account(string username, string password, int accType) : Account() {
		set_username(username);
		set_password(password);
		set_accType(accType);
	}

	virtual ~Account() {} //polimorfik olmasi ucun

#pragma region Setter and Getter
	void set_username(string username) {
		if (username.empty()) { throw MyException(et1("Username"), __LINE__); }
		if (!(5 <= username.length() and username.length() <= 20)) { throw MyException(et2("Username", "5", "20"), __LINE__); }
		this->username = username;
	}
	void set_password(string password) {
		if (password.empty()) { throw MyException(et1("Password"), __LINE__); }
		if (!(5 <= password.length() and password.length() <= 20)) { throw MyException(et2("Password", "5", "20"), __LINE__); }
		this->password = password;
	}
	void set_accType(int accType) {
		if (accType <= 0) { throw MyException(et4("Account type", "0"), __LINE__); }
		this->accType = accType;
	}

	string get_username() const { return username; }
	string get_password() const { return password; }
	int get_accType() const { return accType; }
#pragma endregion

};

class Admin : public Account {
public:
	Admin() : Account("admin", "admin", 3) {}
};

class User : public Account {
#pragma region Fields
	string name;
	string surname;
	string address;
	string email;
	string contact;
	bool gender; //true = male, false = female
	string birthDate;
#pragma endregion
public:
#pragma region Constructors
	User() {
		this->name = "";
		this->surname = "";
		this->address = "";
		this->email = "";
		this->contact = "";
		this->gender = false;
		this->birthDate = "";
	}

	User(string name, string surname, string address, string email, string contact, bool gender, string birthDate, string username, string password, int accType)
		: Account(username, password, accType)
	{
		set_name(name);
		set_surname(surname);
		set_address(address);
		set_email(email);
		set_contact(contact);
		set_gender(gender);
		set_birthdate(birthDate);
	}
#pragma endregion

#pragma region Setter and Getter
	void set_name(string name) {
		if (name.empty()) { throw MyException(et1("Name"), __LINE__); }
		if (!(3 <= name.length() and name.length() <= 20)) { throw MyException(et2("Name", "3", "20"), __LINE__); }
		this->name = name;
	}

	void set_surname(string surname) {
		if (surname.empty()) { throw MyException(et1("Surname"), __LINE__); }
		if (!(5 <= surname.length() and surname.length() <= 20)) { throw MyException(et2("Surname", "5", "20"), __LINE__); }
		this->surname = surname;
	}

	void set_address(string address) {
		if (address.empty()) { throw MyException(et1("Address"), __LINE__); }
		if (!(5 <= address.length() and address.length() <= 50)) { throw MyException(et2("Address", "5", "50"), __LINE__); }
		this->address = address;
	}

	void set_email(string email) {
		char notAllowedChr;
		notAllowedChr = notAllowedCharactersInEmail(email);

		if (email.empty()) { throw MyException(et1("Email"), __LINE__); }
		if (!(10 <= email.length() and email.length() <= 50)) { throw MyException(et2("Email", "10", "50"), __LINE__); }
		if (findChrInStr(email, '@') == -1) { throw MyException(string("Please enter email address correctly: test@mail.com"), __LINE__); }
		if (notAllowedChr != '0') { throw MyException(et3(notAllowedChr), __LINE__); }

		this->email = email;
	}

	void set_contact(string contact) {
		if (contact.empty()) { throw MyException(et1("Contact"), __LINE__); }
		this->contact = contact;
	}

	void set_gender(bool gender) { this->gender = gender; }

	void set_birthdate(string birthdate) {
		char notAllowedChr;
		notAllowedChr = notAllowedCharactersInBirthDate(birthdate);

		if (birthdate.empty()) { throw MyException(et1("Birth date"), __LINE__); }
		if (birthdate.length() != 10) { throw MyException(string("Birth date must be 10 characters: 01.01.2000"), __LINE__); }
		if (notAllowedChr != '0') { throw MyException(et3(notAllowedChr), __LINE__); }
		if (countOfChrsInStr(birthdate, '.') != 2) { throw MyException(string("Please enter birtdate correctly: 01.01.2000"), __LINE__); }
		if (calculcateAge(birthdate) < 15) { throw MyException("Minimum age must be 15", __LINE__); }

		this->birthDate = birthdate;
	}


	string get_name() const { return name; }
	string get_surname() const { return surname; }
	string get_address() const { return address; }
	string get_email() const { return email; }
	string get_contact() const { return contact; }
	bool get_gender() const { return gender; }
	string get_birthDate() const { return birthDate; }
#pragma endregion

#pragma region Methods
	virtual void show(int r = 0) = 0;

	int age() { return calculcateAge(birthDate); }
#pragma endregion
};

class Customer : public User {
	double balance;
public:
	Customer() { this->balance = 0; }

	Customer
	(
		string name, string surname, string address, string email, string contact, bool gender, string birthDate, string username, string password, int accType, //User
		double balance //self
	)
		:User(name, surname, address, email, contact, gender, birthDate, username, password, accType)
	{
		set_balance(balance);
	}

#pragma region Setter and Getter
	void set_balance(double balance) {
		if (balance < 0) { throw MyException(et4("Balance", "zero"), __LINE__); }
		this->balance = balance;
	}

	double get_balance() { return balance; }
#pragma endregion

#pragma region Methods
	void show(int r = 0) override {
		if (r != 0) { cout << r << ". User ------------------------------------" << endl; }
		cout << "Name: " << get_name() << endl;
		cout << "Surname: " << get_surname() << endl;
		cout << "Email: " << get_email() << endl;
		cout << "Contact: " << get_contact() << endl;
		cout << "Gender: " << convertBoolToString(get_gender(), 1) << endl;
		cout << "Birthdate: " << get_birthDate() << ", Age: " << age() << endl;
		cout << "Username: " << this->get_username() << endl;
		cout << "Password: " << this->get_password() << endl;
		cout << "Balance: " << balance << endl;
		cout << endl;
	}
#pragma endregion

};

class Employee : public User {
	double salary;
public:
	Employee() { this->salary = 0; }

	Employee
	(
		string name, string surname, string address, string email, string contact, bool gender, string birthDate, string username, string password, int accType, //User
		double salary //self
	)
		:User(name, surname, address, email, contact, gender, birthDate, username, password, accType)
	{
		set_salary(salary);
	}

#pragma region Setter and Getter
	void set_salary(double salary) {
		if (salary < 345) { throw MyException(et4("Salary", "345"), __LINE__); }
		this->salary = salary;
	}

	double get_salary() { return salary; }
#pragma endregion

#pragma region Methods
	double calculateTax() {
		if (345 <= salary and salary <= 500) { return salary * 0.1; }
		return salary * 0.14;
	}

	void show(int r = 0) {
		if (r != 0) { cout << r << ". User ------------------------------------" << endl; }
		cout << "Name: " << get_name() << endl;
		cout << "Surname: " << get_surname() << endl;
		cout << "Email: " << get_email() << endl;
		cout << "Contact: " << get_contact() << endl;
		cout << "Gender: " << convertBoolToString(get_gender(), 1) << endl;
		cout << "Birthdate: " << get_birthDate() << ", Age: " << age() << endl;
		cout << "Username: " << this->get_username() << endl;
		cout << "Password: " << this->get_password() << endl;
		cout << "Salary: " << salary << endl;
		cout << endl;
	}
#pragma endregion

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AccountsStorage {
	Account** accounts;
	int ind; //index
	int capacity;
	int incrementSize;

	AccountsStorage() {
		this->accounts = nullptr;
		this->ind = 0;
		this->capacity = 0;
		this->incrementSize = 0;
	}
public:
#pragma region Constructors
	AccountsStorage(int size, int incrementSize) : AccountsStorage() {
		set_capacity(size);
		set_incrementSize(incrementSize);
		this->accounts = new Account * [this->capacity] {};
	}

	~AccountsStorage() {
		for (size_t i = 0; i < ind; i++) { delete accounts[i]; }
		delete[] accounts;
	}
#pragma endregion

#pragma region Setter and Getter
	void set_capacity(int capacity) {
		if (capacity <= 0) { throw MyException(et4("Capacity", "zero"), __LINE__); }
		if (capacity >= 20) { throw MyException(et4("Capacity", "20", 2), __LINE__); }
		this->capacity = capacity;
	}
	void set_incrementSize(int incrementSize) {
		if (incrementSize <= 0) { throw MyException(et4("Increment size", "zero"), __LINE__); }
		if (capacity > 10) { throw MyException(et4("Increment size", "10", 2), __LINE__); }
		this->incrementSize = incrementSize;
	}

	Account**& get_accounts() { return accounts; }
	int get_capacity() { return capacity; }
	int get_ind() { return ind; }
#pragma endregion

#pragma region Methods

	void add(Account* account) {
		if (account == nullptr) { throw MyException(string("Parameter account can not be null pointer"), __LINE__); }
		if (findAccountByUsername(account->get_username()) != -1) { throw MyException(string(account->get_username() + ": this username is already exist..."), __LINE__); }

		//yoxlama - yer varmi?
		if (ind == capacity) {
			capacity += incrementSize;
			Account** temp = new Account * [capacity] {};
			for (size_t i = 0; i < ind; i++) { temp[i] = accounts[i]; }
			temp[ind] = account;
			delete[] accounts;
			accounts = temp;
		}

		accounts[ind] = account;
		ind++;
	}

	void removeAll() {
		if (ind == 0) { throw MyException(string("There is not any object in the Storage"), __LINE__); }

		for (size_t i = 0; i < ind; i++) {
			delete accounts[i];
			accounts[i] == nullptr;
		}
		ind = 0;
	}

	void removeByIndex(int index_, bool msg = false) {
		if (ind == 0) { throw MyException(string("There is not any object in the Storage"), __LINE__); }
		if (!(1 <= index_ and index_ <= ind)) { throw MyException(et2("Selection", "1", to_string(ind)), __LINE__); }
		index_--;
		string un = accounts[index_]->get_username();

		//main
		Account** temp = new Account * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (i < index_) {
				temp[i] = accounts[i];
			}
			else {
				temp[i] = accounts[i + 1];
			}
		}

		delete[] accounts;
		accounts = temp;
		ind--;

		if (msg) { cout << un << " was deleted..." << endl; }
	}

	void removeByUsername(string un, bool msg = false) {
		if (findAccountByUsername(un) == -1) { throw MyException(string(un + ": this username is not exist..."), __LINE__); }
		if (un.empty()) { throw MyException(et1("Username"), __LINE__); }
		int r = 0;

		//main
		Account** temp = new Account * [capacity] {};
		for (size_t i = 0; i < ind; i++) {
			if (accounts[i]->get_username() != un) {
				temp[r] = accounts[i];
				r++;
			}
		}

		delete[] accounts;
		accounts = temp;
		ind--;

		if (msg) { cout << un << " was deleted..." << endl; }
	}

	void updatePassword(string un, string newPass, bool msg = false) {
		if (findAccountByUsername(un) == -1) { throw MyException(string(un + ": this username is not exist..."), __LINE__); }
		if (un.empty()) { if (un.empty()) { throw MyException(et1("Username"), __LINE__); } }
		if (newPass.empty()) { if (newPass.empty()) { throw MyException(et1("New password"), __LINE__); } }

		for (size_t i = 0; i < ind; i++) {
			if (accounts[i]->get_username() == un) {
				accounts[i]->set_password(newPass);
				break;
			}
		}

		if (msg) { cout << "Password was updated..."; }
	}

	void showAll() {
		int r = 0;

		for (size_t i = 0; i < ind; i++) {

			auto customer = dynamic_cast<Customer*>(accounts[i]);
			if (customer != nullptr) {
				r++;
				cout << r << ". customer ----------------------------------" << endl;
				cout << "Name: " << customer->get_name() << endl;
				cout << "Surname: " << customer->get_surname() << endl;
				cout << "Address: " << customer->get_address() << endl;
				cout << "Email: " << customer->get_email() << endl;
				cout << "Contact: " << customer->get_contact() << endl;
				cout << "Gender: " << convertBoolToString(customer->get_gender(), 1) << endl;
				cout << "Birth date: " << customer->get_birthDate() << ", " << calculcateAge(customer->get_birthDate()) << endl;
				cout << "Balance: " << customer->get_balance() << endl;
				cout << endl;
			}

			auto employee = dynamic_cast<Employee*>(accounts[i]);
			if (employee != nullptr) {
				r++;
				cout << r << ". employee ----------------------------------" << endl;
				cout << "Name: " << employee->get_name() << endl;
				cout << "Surname: " << employee->get_surname() << endl;
				cout << "Address: " << employee->get_address() << endl;
				cout << "Email: " << employee->get_email() << endl;
				cout << "Contact: " << employee->get_contact() << endl;
				cout << "Gender: " << convertBoolToString(employee->get_gender(), 1) << endl;
				cout << "Birth date: " << employee->get_birthDate() << ", " << calculcateAge(employee->get_birthDate()) << endl;
				cout << "Salary: " << employee->get_salary() << endl;
				cout << endl;
			}

		}
	}

	void showUsernames() {
		int r = 1;

		for (size_t i = 0; i < ind; i++) {
			cout << r << ") " << accounts[i]->get_username() << endl;
			r++;
		}
	}

	int findAccountByUsername(string un) {
		//arraydeki indeks nomresini return edir
		for (size_t i = 0; i < ind; i++) { if (accounts[i]->get_username() == un) { return i; } }
		return -1;
	}

	int accountIsExist(string un, string pass, int accType = 1) {
		//arraydeki indeks nomresini return edir
		for (size_t i = 0; i < ind; i++) {
			if (accounts[i]->get_username() == un and accounts[i]->get_password() == pass and accounts[i]->get_accType() == accType) {
				return i;
			}
		}
		return -1;
	}

#pragma endregion

};


