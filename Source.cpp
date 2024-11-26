#include<iostream>
#include<sstream> //string stream
#include<fstream> //file stream (ifstream and ofstream getirir)
#include"Exception.h"
#include"UserManagement.h"
#include"Common.h"
#include<Windows.h>
#include"Menus.h"
#include"IngredientsManagement.h"
#include<string>
#include"IngredientsHistory.h"
#include"MealStorage.h"
#include"MenuStorage.h"
using namespace std;

#pragma region Global Variables

double restaurantBalance = 0;

int logInaccountType = 0;
//1 - customer
//2 - employee
//3 - admin
string currentUsername = "";

//ingredient history
string name_ih;
int count_ih;

#pragma endregion

#pragma region Restaurant balance file

//load balance to file
void lbtf(double balance, const string filePath = "restaurantbalance") {
	if (balance <= 0) { throw MyException(et4("Balance", "0"), __LINE__); }
	fstream fs(filePath, ios::out);

	if (fs.is_open()) {
		fs << balance << "\n";
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//load balance from file
double lbff(const string filePath = "restaurantbalance") {
	fstream fs(filePath, ios::in);

	if (fs.is_open()) {

		while (!fs.eof()) {
			string row; //faylda setir setir goturmek ucun
			getline(fs, row); //setiri row-a yazir
			return stod(row);
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }

	return -1;
}

void updateRestaurantBalance1(int count, double price, char oper) {
	//gonderilen reqemler uzre update edir
	if (!(oper == '+' or oper == '-')) { throw MyException(string("Operator has to be + or -"), __LINE__); }

	if (oper == '-') { restaurantBalance -= count * price; }
	else { restaurantBalance += count * price; }

	lbtf(restaurantBalance);
}

void updateRestaurantBalance2(IngredientStorage& is) {
	double result = 0;
	for (size_t i = 0; i < is.get_ind(); i++) {
		result += (is.get_ingredients()[i]->get_count() * is.get_ingredients()[i]->get_price());
	}
	restaurantBalance = result;
	lbtf(restaurantBalance);
}

#pragma endregion

#pragma region Accounts file

//load accounts to file
void latf(AccountsStorage& as, const string filePath = "accounts") {
	fstream fs(filePath, ios::out);

	if (fs.is_open()) {
		for (size_t i = 0; i < as.get_ind(); i++) { //array uzerinde addimlama
			//Customer
			auto c = dynamic_cast<Customer*>(as.get_accounts()[i]);
			if (c != nullptr) {
				fs << c->get_username() << "^" << c->get_password() << "^"
					<< c->get_name() << "^" << c->get_surname() << "^" << c->get_address() << "^" << c->get_email() << "^"
					<< c->get_contact() << "^" << c->get_gender() << "^" << c->get_birthDate() << "^" << c->get_balance() << "^" << c->get_accType() << "\n";
			}
			//Employee
			auto e = dynamic_cast<Employee*>(as.get_accounts()[i]);
			if (e != nullptr) {
				fs << e->get_username() << "^" << e->get_password() << "^"
					<< e->get_name() << "^" << e->get_surname() << "^" << e->get_address() << "^" << e->get_email() << "^"
					<< e->get_contact() << "^" << e->get_gender() << "^" << e->get_birthDate() << "^" << e->get_salary() << "^" << e->get_accType() << "\n";
			}
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//load selected accounts from file
void lsaff(AccountsStorage& as, char accT, const string filePath = "accounts") {
	fstream fs(filePath, ios::in);

	if (fs.is_open()) {
		while (!fs.eof()) {
			string row;
			getline(fs, row);

			//account novunu teyin edir
			char accType = '0';
			if (row.size() != 0) { accType = row[row.size() - 1]; }

			//main ---

			//Customer
			if (accType == accT and accType == '1') {
				int counter = 1;
				Customer* customer = new Customer();
				string un = "", p = "", n = "", s = "", a = "", e = "", c = "", g = "", b = "", ba = "";

				for (auto ch : row) {
					if (ch != '^' and counter == 1) { un += ch; }
					else if (ch != '^' and counter == 2) { p += ch; }
					else if (ch != '^' and counter == 3) { n += ch; }
					else if (ch != '^' and counter == 4) { s += ch; }
					else if (ch != '^' and counter == 5) { a += ch; }
					else if (ch != '^' and counter == 6) { e += ch; }
					else if (ch != '^' and counter == 7) { c += ch; }
					else if (ch != '^' and counter == 8) { g += ch; }
					else if (ch != '^' and counter == 9) { b += ch; }
					else if (ch != '^' and counter == 10) { ba += ch; }
					else { counter++; }
				}

				customer->set_name(n);
				customer->set_surname(s);
				customer->set_address(a);
				customer->set_email(e);
				customer->set_contact(c);
				customer->set_gender(stoi(g));
				customer->set_birthdate(b);
				customer->set_username(un);
				customer->set_password(p);
				customer->set_accType(1);
				customer->set_balance(stod(ba));

				as.add(customer);
			}

			//Employee
			if (accType == accT and accType == '2') {
				int counter = 1;
				Employee* employee = new Employee();
				string un = "", p = "", n = "", s = "", a = "", e = "", c = "", g = "", b = "", ba = "";

				for (auto ch : row) {
					if (ch != '^' and counter == 1) { un += ch; }
					else if (ch != '^' and counter == 2) { p += ch; }
					else if (ch != '^' and counter == 3) { n += ch; }
					else if (ch != '^' and counter == 4) { s += ch; }
					else if (ch != '^' and counter == 5) { a += ch; }
					else if (ch != '^' and counter == 6) { e += ch; }
					else if (ch != '^' and counter == 7) { c += ch; }
					else if (ch != '^' and counter == 8) { g += ch; }
					else if (ch != '^' and counter == 9) { b += ch; }
					else if (ch != '^' and counter == 10) { ba += ch; }
					else { counter++; }
				}

				employee->set_name(n);
				employee->set_surname(s);
				employee->set_address(a);
				employee->set_email(e);
				employee->set_contact(c);
				employee->set_gender(stoi(g));
				employee->set_birthdate(b);
				employee->set_username(un);
				employee->set_password(p);
				employee->set_accType(2);
				employee->set_salary(stod(ba));

				as.add(employee);
			}

			accType = '0';
		}
		fs.close();
	}
	else { throw MyException("File not found", __LINE__); }
}

//load all accounts from file
void lsaff_all(AccountsStorage& as) {
	lsaff(as, '1');
	lsaff(as, '2');
}

void registerNewCustomer(AccountsStorage& as) {
	string name, surname, address, email, contact, birthdate, username, password, gender;
	bool gender_b;
	double balance;

	cout << "Please all sections\n\n";

	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	cout << "Name: ";
	cin >> name;
	cout << "Surname: ";
	cin >> surname;
	cout << "Address: ";
	cin >> address;
	cout << "Email: ";
	cin >> email;
	cout << "Contact: ";
	cin >> contact;
	cout << "Gender (M/F): ";
	cin >> gender;
	cout << "Birth date (01.01.2000): ";
	cin >> birthdate;
	cout << "Balance: ";
	cin >> balance;

	if (gender == "M") { gender_b = true; }
	else { gender_b = false; }

	Customer* customer = new Customer(name, surname, address, email, contact, gender_b, birthdate, username, password, 1, balance);
	as.add(customer);
	latf(as);
	cout << "New customer created...\n\n";
	sleep_dots(4, 750);
}

void registerNewEmployee(AccountsStorage& as) {
	string name, surname, address, email, contact, birthdate, username, password, gender;
	bool gender_b;
	double salary;

	cout << "Please all sections\n\n";

	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	cout << "Name: ";
	cin >> name;
	cout << "Surname: ";
	cin >> surname;
	cout << "Address: ";
	cin >> address;
	cout << "Email: ";
	cin >> email;
	cout << "Contact: ";
	cin >> contact;
	cout << "Gender (M/F): ";
	cin >> gender;
	cout << "Birth date (01.01.2000): ";
	cin >> birthdate;
	cout << "Salary: ";
	cin >> salary;

	if (gender == "M") { gender_b = true; }
	else { gender_b = false; }

	Employee* employee = new Employee(name, surname, address, email, contact, gender_b, birthdate, username, password, 2, salary);
	as.add(employee);
	latf(as);
	cout << "New employee created...\n\n";
	sleep_dots(4, 750);
}

#pragma endregion

#pragma region Ingredients file

//load ingredients from file
void liff(IngredientStorage& is, const string filePath = "ingredients") {
	fstream fs(filePath, ios::in);
	string id_ = "";
	string name = "";
	string count = "";
	string price = "";

	if (fs.is_open()) {

		while (!fs.eof()) {
			string row; //faylda setir setir goturmek ucun
			getline(fs, row); //setiri row-a yazir

			Ingredient* ingredient = new Ingredient();
			int counter = 0; //^ isarelerini ayirmaq ucun

			for (auto ch : row) { //row-dan ox

				if (
					(48 <= int(ch) and int(ch) <= 57) or
					(65 <= int(ch) and int(ch) <= 90) or
					(97 <= int(ch) and int(ch) <= 122) or ch == '^')
				{
					if (ch != '^' and counter == 0) { id_ += ch; }
					else if (ch != '^' and counter == 1) { name += ch; }
					else if (ch != '^' and counter == 2) { count += ch; }
					else if (ch != '^' and counter == 3) { price += ch; }
					else { counter++; }
				}
			}

			if (name != "") {
				ingredient->set_id(stoi(id_));
				ingredient->set_name(name);
				ingredient->set_count(stoi(count));
				ingredient->set_price(stod(price));

				is.add(ingredient);
			}

			id_ = "";
			name = "";
			count = "";
			price = "";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//load ingredients to file
void litf(IngredientStorage& is, const string filePath = "ingredients") {
	fstream fs(filePath, ios::out);

	if (fs.is_open()) {
		for (size_t i = 0; i < is.get_ind(); i++) {
			fs << is.get_ingredients()[i]->get_id() << "^"
				<< is.get_ingredients()[i]->get_name() << "^"
				<< is.get_ingredients()[i]->get_count() << "^"
				<< is.get_ingredients()[i]->get_price() << "\n";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

void addNewIngredients(IngredientStorage& is) {
	system("cls");
	int id;
	double price;

	cout << "New ingredients informations: " << endl;

	cout << "ID: ";
	cin >> id;
	cout << "Ingredient name: ";
	cin >> name_ih;
	cout << "Count: ";
	cin >> count_ih;
	cout << "Price: ";
	cin >> price;

	//yoxlama - restoranin balansini asir?
	if (count_ih * price > restaurantBalance) { throw MyException(string("Restaurant balance is not enough, Balance: " + to_string(restaurantBalance)), __LINE__); }

	Ingredient* ingredient = new Ingredient(id, name_ih, count_ih, price);
	is.add(ingredient);
	litf(is);

	//restaurant balance
	updateRestaurantBalance1(count_ih, price, '-');

	cout << "New ingredient created...\n\n";
	sleep_dots(4, 750);
}

#pragma endregion

#pragma region Ingredients history file

//load ingredients history to file
void lihtf(IngredientsHistoryStorage& ihs, const string filePath = "ingredientshistory") {
	fstream fs(filePath, ios::out);

	if (fs.is_open()) {
		for (size_t i = 0; i < ihs.get_ind(); i++) {
			fs << ihs.get_ingredientshistories()[i]->get_name() << "^"
				<< ihs.get_ingredientshistories()[i]->get_count() << "^"
				<< ihs.get_ingredientshistories()[i]->get_date() << "\n";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//load ingredients history from file
void lihff(IngredientsHistoryStorage& ihs, const string filePath = "ingredientshistory") {
	fstream fs(filePath, ios::in);
	string name = "";
	string count = "";
	string date = "";

	if (fs.is_open()) {

		while (!fs.eof()) {
			string row; //faylda setir setir goturmek ucun
			getline(fs, row); //setiri row-a yazir

			IngredientsHistory* ingredienthistory = new IngredientsHistory();
			int counter = 0; //^ isarelerini ayirmaq ucun

			for (auto ch : row) { //row-dan ox
				if (ch != '^' and counter == 0) { name += ch; }
				else if (ch != '^' and counter == 1) { count += ch; }
				else if (ch != '^' and counter == 2) { date += ch; }
				else { counter++; }
			}

			if (name != "") {
				ingredienthistory->set_name(name);
				ingredienthistory->set_count(stoi(count));
				ingredienthistory->set_date(date);

				ihs.add(ingredienthistory);
			}

			name = "";
			count = "";
			date = "";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

void addNewIngredientsHistory(IngredientsHistoryStorage& ihs) {
	system("cls");

	IngredientsHistory* ih = new IngredientsHistory(name_ih, count_ih);
	ihs.add(ih);
	lihtf(ihs);
}

#pragma endregion 

#pragma region Meals file

//load meal to file
void lmtf(MealStorage& ms, const string filePath = "meals") {
	fstream fs(filePath, ios::out);

	if (fs.is_open()) {
		for (size_t i = 0; i < ms.get_ind(); i++) {
			fs << ms.get_meals()[i]->get_id() << "^"
				<< ms.get_meals()[i]->get_name() << "^"
				<< ms.get_meals()[i]->get_price() << "\n";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//load meal from file
void lmff(MealStorage& ms, const string filePath = "meals") {
	fstream fs(filePath, ios::in);

	string id = "";
	string name = "";
	string price = "";

	if (fs.is_open()) {

		while (!fs.eof()) {
			string row; //faylda setir setir goturmek ucun
			getline(fs, row); //setiri row-a yazir

			Meal* meal = new Meal();

			int counter = 0; //^ isarelerini ayirmaq ucun

			for (auto ch : row) { //row-dan ox
				if (
					(48 <= int(ch) and int(ch) <= 57) or
					(65 <= int(ch) and int(ch) <= 90) or
					(97 <= int(ch) and int(ch) <= 122) or ch == '^')
				{
					if (ch != '^' and counter == 0) { id += ch; }
					else if (ch != '^' and counter == 1) { name += ch; }
					else if (ch != '^' and counter == 2) { price += ch; }
					else { counter++; }
				}
			}

			if (name != "") {
				meal->set_id(stoi(id));
				meal->set_name(name);
				meal->set_price(stod(price));

				ms.add(meal);
			}

			id = "";
			name = "";
			price = "";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

void addNewMeal(MealStorage& ms) {
	system("cls");
	int id;
	string name;
	double price;

	cout << "New meal informations: " << endl;

	cout << "ID: ";
	cin >> id;
	cout << "Meal name: ";
	cin >> name;
	cout << "Price: ";
	cin >> price;

	Meal* meal = new Meal(id, name, price);
	ms.add(meal);
	lmtf(ms);

	cout << "New meal created...\n\n";
	sleep_dots(4, 750);
}

#pragma endregion

#pragma region Menus file

//load menus to file
void lmenustf(MenuStorage& menuS, const string filePath = "menus") {
	fstream fs(filePath, ios::out);

	if (fs.is_open()) {
		for (size_t i = 0; i < menuS.get_ind(); i++) {
			fs << menuS.get_menus()[i]->get_mealId() << "^"
				<< menuS.get_menus()[i]->get_ingId() << "^"
				<< menuS.get_menus()[i]->get_ingCount() << "\n";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//load menus from file
void lmenusff(MenuStorage& menuS, const string filePath = "menus") {
	fstream fs(filePath, ios::in);

	string mealId = "";
	string ingId = "";
	string ingCount = "";

	if (fs.is_open()) {
		while (!fs.eof()) {
			string row; //faylda setir setir goturmek ucun
			getline(fs, row); //setiri row-a yazir

			int counter = 0; //^ isarelerini ayirmaq ucun

			for (auto ch : row) { //row-dan ox
				if (
					(48 <= int(ch) and int(ch) <= 57) or
					(65 <= int(ch) and int(ch) <= 90) or
					(97 <= int(ch) and int(ch) <= 122) or ch == '^')
				{
					if (ch != '^' and counter == 0) { mealId += ch; }
					else if (ch != '^' and counter == 1) { ingId += ch; }
					else if (ch != '^' and counter == 2) { ingCount += ch; }
					else { counter++; }
				}
			}

			if (mealId != "") {
				Menu* menu = new Menu(stoi(mealId), stoi(ingId), stoi(ingCount));
				menuS.add(menu);
			}

			mealId = "";
			ingId = "";
			ingCount = "";
		}
		fs.close();
	}
	else { throw MyException(string("File not found..."), __LINE__); }
}

//burada qaldin

#pragma endregion



void main() {

#pragma region Variables
	bool program = true;
	bool login, signin, enterance, afterEntr;
	bool ae_admin, ae_employee, ae_customer; //ae->after enterance
	bool ae_admin_history, ae_customer_orderameal;

	int menu1_select = 0, menu2_select = 0, menu3_select = 0;
	int menu4_1_select = 0, menu4_2_select = 0, menu4_3_select = 0;
	int menu4_1_1_select = 0;

	int removeIngIndex = 0, updateIngIndex = 0;
	int deleteMealSelection = 0; //admin terefden meal silinmesi secimi
	int uic_newCount = 0; //admin update ingredient count
#pragma endregion

#pragma region Load datas from files
	restaurantBalance = lbff();

	AccountsStorage as(5, 3);
	try { lsaff_all(as); } //accounts
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

	IngredientStorage is(5, 3);
	try { liff(is); } //ingredients
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

	MealStorage ms(5, 3); //meals faylindan
	try { lmff(ms); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

	MenuStorage menuSto(5, 3); //menus faylindan
	try { lmenusff(menuSto); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }



	IngredientsHistoryStorage ihs(10, 3);
	try { lihff(ihs); } //ingredients history
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
#pragma endregion

	programHeader(); //header

	while (program)
	{
#pragma region Enterance
		enterance = true;
		while (enterance) {
			try { menu1_select = menu1(); }
			catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

			switch (menu1_select) {
			case 1: //Log in
				login = true;
				system("cls");

				while (login) {
					try { menu2_select = menu2(); }
					catch (MyException& ex) { system("cls"); cout << ex.get_txt() << "\n\n"; }
					system("cls");

					string password = "";

					switch (menu2_select) {
					case 1: // as a customer
						try {
							currentUsername = getString("Username");
							password = getString("Password");
							if (as.accountIsExist(currentUsername, password) == -1) { throw MyException(string("This customer account is not exist"), __LINE__); };
							cout << "Entered" << endl;
							logInaccountType = 1;
							login = false;
							enterance = false;
						}
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						break;
					case 2: //as an employee
						try {
							currentUsername = getString("Username");
							password = getString("Password");
							if (as.accountIsExist(currentUsername, password) == -1) { throw MyException(string("This employee account is not exist"), __LINE__); };
							cout << "Entered" << endl;
							logInaccountType = 2;
							login = false;
							enterance = false;
						}
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						break;
					case 3: //as an admin
						try {
							currentUsername = getString("Username");
							password = getString("Password");
							if (!(currentUsername == "admin" and password == "admin")) { throw MyException(string("Invalid enterance"), __LINE__); }
							cout << "Entered" << endl;
							logInaccountType = 3;
							login = false;
							enterance = false;
						}
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						break;
					case 4:
						login = false;
						break;
					}
				}

				break;
			case 2: //Sign in
				signin = true;
				system("cls");

				while (signin) {
					try { menu3_select = menu3(); }
					catch (MyException& ex) { system("cls"); cout << ex.get_txt() << "\n\n"; }
					system("cls");

					string name, surname, address, email, contact, gender, birthdate; //common
					double balance, salary;

					switch (menu3_select) {
					case 1: //as a customer
						try { registerNewCustomer(as); signin = false; }
						catch (MyException& ex) { cout << "\nERRORRRRRRRR: " << ex.get_txt() << "\nAgain..." << "\n\n"; }
						break;
					case 2: //as an employee
						try { registerNewEmployee(as); signin = false; }
						catch (MyException& ex) { cout << "\nERRORRRRRRRR: " << ex.get_txt() << "\nAgain..." << "\n\n"; }
						break;
					case 3: //go back
						signin = false;
						break;
					}
				}

				break;
			case 3: //exitig the system
				program = false;
				enterance = false;
				cout << "Exiting the system...\n\n";
				break;
			}
		}
#pragma endregion

#pragma region After enterance
		if (program and !enterance) {
			sleep_dots(3, 500);
			afterEntr = true;

			while (afterEntr) {
				ae_customer = true;
				ae_employee = true;
				ae_admin = true;

				switch (logInaccountType) { //kim daxil olubsa ona uygun menyu acilmasi ucun
				case 1: //customer

					while (ae_customer) {
						try { menu4_2_select = menu4_2(); }
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						system("cls");

						switch (menu4_2_select) {
						case 1: //Order a meal
							ae_customer_orderameal = true;

							while (ae_customer_orderameal) {
								cout << "\t\t---Menu---" << endl;
								cout << "Only available meals according to ingredient storage\n\n";
								//burada qaldin
							}

							break;
						case 2: //Show menu
							break;
						case 3: //Show history
							break;
						case 4: //go back
							ae_customer = false;
							afterEntr = false;
							break;
						}
					}

					break;
				case 2: //employee

					while (ae_employee) {
						try { menu4_3_select = menu4_3(); }
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						system("cls");
						Employee* data;

						switch (menu4_3_select) {
						case 1:
							cout << "Your info: " << endl;
							data = dynamic_cast<Employee*>(as.get_accounts()[as.findAccountByUsername(currentUsername)]);
							data->show();
							break;
						case 2:
							ae_employee = false;
							afterEntr = false;
							break;
						}
					}

					break;
				case 3: //admin

					while (ae_admin) {
						try { menu4_1_select = menu4_1(); }
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						system("cls");

						switch (menu4_1_select) {
						case 1: //add ingredient - ok
							try {
								addNewIngredients(is);
								addNewIngredientsHistory(ihs);
							}
							catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
							break;
						case 2: //remove ingredient - ok
							is.show();
							try {
								removeIngIndex = getMenuSelection(1, is.get_ind());
								updateRestaurantBalance1(is.get_ingredients()[removeIngIndex - 1]->get_count(), is.get_ingredients()[removeIngIndex - 1]->get_price(), '+');
								is.removeByIndex(removeIngIndex, true);
								litf(is);
							}
							catch (MyException& ex) { cout << "Error: " << ex.get_txt() << "\n\n"; }
							cout << "Ingredient removed..." << endl;
							break;
						case 3: //update count of ingredient - ok
							is.show();
							try {
								updateIngIndex = getMenuSelection(1, is.get_ind());
								cout << "New count: ";
								cin >> uic_newCount;
								is.updateCount1(is.get_ingredients()[updateIngIndex - 1]->get_name(), uic_newCount);
								updateRestaurantBalance2(is);
								litf(is);
							}
							catch (MyException& ex) { cout << "Error: " << ex.get_txt() << "\n\n"; }
							cout << "Ingredient updated..." << endl;
							break;
						case 4: //show all ingredients - ok
							cout << "All ingredients in stock" << endl;
							is.show();
							break;
						case 5: //show restaurant balance - ok
							cout << "Restaurant balance: " << restaurantBalance << endl;
							break;
						case 6: //history - ok
							ae_admin_history = true;

							while (ae_admin_history) {
								try { menu4_1_1_select = menu4_1_1(); }
								catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
								system("cls");

								switch (menu4_1_1_select) {
								case 1: //ingredients history
									cout << "Total buy count: " << ihs.get_total_count() << endl;
									cout << "Total transaction: " << ihs.get_ind() << endl;
									ihs.make_history_table();
									break;
								case 2: //go back
									ae_admin_history = false;
									break;
								}
							}

							break;
						case 7: //add new meal
							cout << "Add new meal to menu" << endl;
							try { addNewMeal(ms); }
							catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
							break;
						case 8: //delete meal
							cout << "Delete meal" << endl;

							//

							break;
						case 9: //show menu - menyuya daxil etmek ucun gozleyenler
							cout << "Waiting for add to menu" << endl;
							menuSto.show2(ms);
							break;
						case 10: //show full menu
							cout << "Full menu" << endl;

							menuSto.show3(ms, is);

							break;
						case 11: //complete menu
							cout << "Complete menu" << endl;

							//

							break;
						case 12: //show all users
							as.showAll();
							break;
						case 13: //go back
							ae_admin = false;
							afterEntr = false;
							break;
						}
					}

					break;
				}

			}
		}
#pragma endregion

	}

}