#include<iostream>
#include<sstream> //string stream
#include<fstream> //file stream (ifstream and ofstream getirir)
#include"Exception.h"
#include"UserManagement.h"
#include"Common.h"
#include<Windows.h>
#include"Menus.h"
#include"IngredientsStorage.h"
#include<string>
#include"IngredientsHistory.h"
#include"MealStorage.h"
#include"MenuStorage.h"
using namespace std;

#pragma region Globals

//Variables
double restaurantBalance = 0;

int logInaccountType = 0;
//1 - customer
//2 - employee
//3 - admin
string currentUsername = "";

//ingredient history
string name_ih;
int count_ih;

//Stack - data structure

//class MyStack_Int {
//	int* data = nullptr;
//	int ind = 0;
//	int capacity = 5;
//public:
//	MyStack_Int() {
//		this->data = new int[capacity] {};
//	}
//
//#pragma region Setter and Getter
//	int* get_data() { return data; }
//	int get_ind() { return ind; }
//	int get_capacity() { return capacity; }
//#pragma endregion
//
//#pragma region Methods
//	void add(int t) {
//
//		//yoxlama
//		if (ind == capacity) { //yer yoxdu
//			capacity += 3;
//			int* temp = new int [capacity] {};
//			for (size_t i = 0; i < ind; i++) { temp[i] = data[i]; }
//			temp[ind] = t;
//			delete[] data;
//			data = temp;
//		}
//
//		data[ind] = t;
//		ind++;
//	}
//#pragma endregion
//
//}

#pragma endregion

#pragma region Files

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

//mealda olub da menu-da olmayanlari return edur (yeni obyektde)
MealStorage*& getMenu_notEnteredMeals(MenuStorage& menus, MealStorage& ms) {
	MealStorage* meals = new MealStorage(5, 3);
	bool flag;

	for (size_t i = 0; i < ms.get_ind(); i++) { //meals

		for (size_t j = 0; j < menus.get_ind(); j++) { //menus
			//qarsilasdirma
			if (ms.get_meals()[i]->get_id() == menus.get_menus()[j]->get_mealId()) { flag = true; break; }
			else { flag = false; }
		}

		if (!flag) {
			Meal* meal = ms.get_meals()[i];
			meals->add(meal);
		}
	}

	return meals;
}

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

void addNewMenu(MenuStorage& menuS, MealStorage& ms, IngredientStorage& is) {
	system("cls");
	bool menu = true;
	int notExistMeals_selection = 0, ingSeletion = 0, ingCountSeletion = 0;
	double selectedIngPrice = 0, currentIngCount = 0, totalPrice = 0;
	string selectedMealName = "";

	MealStorage* notExistMeals = getMenu_notEnteredMeals(menuS, ms); //mealda olub da menu-da olmayanlar
	if (notExistMeals->get_ind() == 0) {
		cout << "There is not any meal that have not been added to menu" << endl;
		cout << "If you want to new ingredients to meal please select <update menu> in the menu" << endl;
		return;
	}

	notExistMeals->show();
	notExistMeals_selection = getMenuSelection(1, notExistMeals->get_ind()); //gelen siyahidan secim etmek - meal (indeks)
	selectedMealName = notExistMeals->get_meals()[notExistMeals_selection - 1]->get_name();
	cout << endl;

	//main
	while (menu) {
		cout << endl;

		//cari elave edilmis ingredientlerin sirasi
		menuS.show1(notExistMeals->get_meals()[notExistMeals_selection - 1]->get_id(), ms, is);
		cout << "\n\nRestaurant balance: " << restaurantBalance;
		cout << "\nTotal price: " << totalPrice;
		cout << endl << endl;

		//ingredient secimi
		cout << "row number, ingredient name, (count), [price]" << endl;
		is.show(3);
		cout << "To complete please select: " << (is.get_ind() + 1) << endl;
		ingSeletion = getMenuSelection(1, is.get_ind() + 1); //ingredient secimi

		if (ingSeletion != is.get_ind() + 1) {
			//count secimi
			cout << "Count: ";
			cin >> ingCountSeletion;

			//yeteri qeder ingredient listinde ingredient varmi?
			currentIngCount = is.get_ingredients()[ingSeletion - 1]->get_count();
			if (currentIngCount >= ingCountSeletion) {

				//restoran balansi yoxlamasi
				selectedIngPrice = is.get_ingredients()[ingSeletion - 1]->get_price();

				//secilen ing id-ler toplanir
				if (restaurantBalance >= (selectedIngPrice * ingCountSeletion)) { //eger balans varsa

					Menu* menu = new Menu();
					menu->set_mealId(notExistMeals->get_meals()[notExistMeals_selection - 1]->get_id());
					menu->set_ingId(is.get_ingredients()[ingSeletion - 1]->get_id());
					menu->set_ingCount(ingCountSeletion);
					menuS.add(menu);

					(is.get_ingredients()[ingSeletion - 1])->set_count(currentIngCount - ingCountSeletion);
					restaurantBalance -= (selectedIngPrice * ingCountSeletion);
					totalPrice += selectedIngPrice * ingCountSeletion;
				}
				else { cout << "Restaurant balance is not enough" << endl; sleep_dots(3, 1000); }

			}
			else { cout << "Current ingredient count is not enough" << endl; sleep_dots(3, 1000); }
		}
		else { menu = false; }

		system("cls");
		cout << "Ingredient added to meal: " << selectedMealName << endl;
	}

	lmenustf(menuS);
	litf(is);
	lbtf(restaurantBalance);
	system("cls");
	cout << "New menu added successfully..." << endl;
}

#pragma endregion

#pragma endregion



void main() {

#pragma region Variables
	bool program = true;
	bool login, signin, enterance, afterEntr;

	//ae->after enterance
	bool ae_admin, ae_employee, ae_customer;

	bool ae_admin_ingredients, ae_admin_meals, ae_admin_others, ae_admin_menus;

	int menu1_select = 0;
	int menu2_select = 0;
	int menu3_select = 0;
	int menu2_1_select = 0, menu2_2_select = 0, menu2_3_select = 0;
	int menu2_3_1_select = 0, menu2_3_2_select = 0, menu2_3_3_select = 0, menu2_3_4_select = 0;
#pragma endregion

#pragma region Load datas from files
	restaurantBalance = lbff();

	//accounts
	AccountsStorage as(5, 3);
	try { lsaff_all(as); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

	//ingredients
	IngredientStorage is(5, 3);
	try { liff(is); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

	// meals
	MealStorage ms(5, 3);
	try { lmff(ms); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }

	//menus
	MenuStorage menuSto(5, 3);
	try { lmenusff(menuSto); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }


	//ingredients history
	IngredientsHistoryStorage ihs(10, 3);
	try { lihff(ihs); }
	catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
#pragma endregion

	programHeader();

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
						try { menu2_1_select = menu2_1(); }
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						system("cls");

						switch (menu2_1_select) {
						case 1: //Order a meal
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
				case 2: //employee - ok

					while (ae_employee) { //ok
						try { menu2_2_select = menu2_2(); }
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						system("cls");
						Employee* data;

						switch (menu2_2_select) {
						case 1: //show info - ok
							cout << "Your info: " << endl;
							data = dynamic_cast<Employee*>(as.get_accounts()[as.findAccountByUsername(currentUsername)]);
							data->show();
							break;
						case 2: //go back - ok
							ae_employee = false;
							afterEntr = false;
							break;
						}
					}

					break;
				case 3: //admin

					while (ae_admin) {
						try { menu2_3_select = menu2_3(); }
						catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
						system("cls");

						switch (menu2_3_select) {
						case 1: //Ingredients
							ae_admin_ingredients = true;

							//ok
							while (ae_admin_ingredients) {
								try { menu2_3_1_select = menu2_3_1(); }
								catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
								system("cls");

								switch (menu2_3_1_select) {
								case 1: //add ingredient - ok
									try {
										addNewIngredients(is);
										addNewIngredientsHistory(ihs);
									}
									catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
									break;
								case 2: //update ingredient name - ok
									try {
										string ingNewName;
										int updateIngIndex;
										cout << "Select from Ingredient list" << endl;
										is.show(2);
										updateIngIndex = getMenuSelection(1, is.get_ind());
										cout << "New ingredient name: ";
										cin >> ingNewName;
										is.updateNameById(is.get_ingredients()[updateIngIndex - 1]->get_id(), ingNewName);
										litf(is);
										cout << "Ingredient name updated.." << endl;
									}
									catch (MyException& ex) { cout << "Error: " << ex.get_txt() << "\n\n"; }
									break;
								case 3: //update count of ingredient - ok
									try {
										int uic_newCount, updateIngIndex;
										cout << "Select from Ingredient list" << endl;
										cout << "Row number. [id] ingredient name, count, price" << endl << endl;
										is.show(1);
										updateIngIndex = getMenuSelection(1, is.get_ind());
										cout << "New count: ";
										cin >> uic_newCount;
										is.updateCount1(is.get_ingredients()[updateIngIndex - 1]->get_id(), uic_newCount);

										//azalir coxalir?
										if (uic_newCount - is.get_ingredients()[updateIngIndex - 1]->get_count() >= 0) { // coxalir
											updateRestaurantBalance1(uic_newCount, is.get_ingredients()[updateIngIndex - 1]->get_price(), '+');
										}
										else {
											updateRestaurantBalance1(uic_newCount, is.get_ingredients()[updateIngIndex - 1]->get_price(), '-');
										}

										litf(is);
										cout << "Ingredient count updated.." << endl;
									}
									catch (MyException& ex) { cout << "Error: " << ex.get_txt() << "\n\n"; }
									break;
								case 4: //remove ingredient - ok
									try {
										int removeIngIndex;
										is.show(2);
										removeIngIndex = getMenuSelection(1, is.get_ind());
										updateRestaurantBalance1(is.get_ingredients()[removeIngIndex - 1]->get_count(), is.get_ingredients()[removeIngIndex - 1]->get_price(), '+');
										is.removeByIndex(removeIngIndex, true);
										litf(is);
									}
									catch (MyException& ex) { cout << "Error: " << ex.get_txt() << "\n\n"; }
									cout << "Ingredient removed..." << endl;
									break;
								case 5: //show all ingredients - ok
									cout << "All ingredients in stock" << endl;
									cout << "Row number. [id] ingredient name, count, price" << endl;
									is.show(1);
									break;
								case 6: //go back-ok
									ae_admin_ingredients = false;
									break;
								}

							}

							break;
						case 2: //Meals
							ae_admin_meals = true;

							//ok
							while (ae_admin_meals) {
								try { menu2_3_2_select = menu2_3_2(); }
								catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
								system("cls");

								switch (menu2_3_2_select) {
								case 1: //add meal - ok
									cout << "Add new meal to menu" << endl;
									try { addNewMeal(ms); }
									catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
									break;
								case 2: //update meal name - ok
									try {
										string updatemealNewName;
										int updateMealNameIndex;
										ms.show();
										updateMealNameIndex = getMenuSelection(1, ms.get_ind());
										cout << "New meal name: ";
										cin >> updatemealNewName;
										ms.updateMealNameById(ms.get_meals()[updateMealNameIndex - 1]->get_id(), updatemealNewName, true);
										lmtf(ms);
									}
									catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
									break;
								case 3: //update meal price - ok
									try {
										int selectedMealIndex;
										double newPrice;
										ms.show();
										selectedMealIndex = getMenuSelection(1, ms.get_ind());
										cout << "New meal price: ";
										cin >> newPrice;
										ms.get_meals()[selectedMealIndex - 1]->set_price(newPrice);
										lmtf(ms);
										cout << "Meal price updated..." << endl;
									}
									catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
									break;
								case 4: //remove meal - ok
									try {
										int selectedMealIndex;
										ms.show();
										selectedMealIndex = getMenuSelection(1, ms.get_ind());
										ms.removeById(selectedMealIndex - 1);
										lmtf(ms);
										cout << "Meal removed..." << endl;
									}
									catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
									break;
								case 5: //show all meals - ok
									cout << "All meals in menu" << endl;
									cout << "[id] meal name (price)" << endl << endl;
									ms.show();
									break;
								case 6: //go back - ok
									ae_admin_meals = false;
									break;
								}
							}

							break;
						case 3: //Menus
							ae_admin_menus = true;

							while (ae_admin_menus) {
								try { menu2_3_3_select = menu2_3_3(); }
								catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
								system("cls");

								switch (menu2_3_3_select) {
								case 1: //add menu
									cout << "Add new menu" << endl;
									try { addNewMenu(menuSto, ms, is); }
									catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
									break;
								case 2: //update menu
									break;
								case 3: //remove menu
									break;
								case 4: //show all menus
									break;
								case 5: //go back
									ae_admin_menus = false;
									break;
								}
							}

							break;
						case 4: //Other
							ae_admin_others = true;

							while (ae_admin_others) {
								try { menu2_3_4_select = menu2_3_4(); }
								catch (MyException& ex) { cout << ex.get_txt() << "\n\n"; }
								system("cls");

								switch (menu2_3_4_select) {
								case 1: //Restaurant balance
									cout << "Restaurant balance: " << restaurantBalance << endl;
									break;
								case 2: //Show all users
									break;
								case 3: //Ingredient history
									cout << "Total buy count: " << ihs.get_total_count() << endl;
									cout << "Total transaction: " << ihs.get_ind() << endl;
									ihs.make_history_table();
									break;
								case 4: //go back
									ae_admin_others = false;
									break;
								}
							}

							break;
						case 5: //go back - ok
							ae_admin = false;
							afterEntr = false;
							break;
						}

					}

					break;
				}
			}

		}
	}
#pragma endregion

}
