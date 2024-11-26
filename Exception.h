#pragma once
#include<iostream>
using namespace std;

class MyException {
	string txt;
	int line;
	string d; //date
	string t; //time
public:
	MyException() {
		this->txt = "";
		this->line = 0;
		this->d = __DATE__;
		this->t = __TIME__;
	}

	MyException(string txt, int line) : MyException() {
		set_txt(txt);
		set_line(line);
	}

#pragma region Setter and Getter
	void set_txt(string txt) { this->txt = txt; }
	void set_line(int line) { this->line = line; }
	void set_d(string d) { this->d = d; }
	void set_t(string t) { this->t = t; }

	string get_txt() { return txt; }
	int get_line() { return line; }
	string get_d() { return d; }
	string get_t() { return t; }
#pragma endregion

#pragma region Methods
	void show() {
		cout << "Error: " << get_txt() << ", ";
		cout << "Line: " << get_line() << ", ";
		cout << "Date: " << get_d() << ", ";
		cout << "Time: " << get_t() << endl;
	}
#pragma endregion

};

#pragma region Methods

char notAllowedCharactersInEmail(string email) {
	//email-da istifade edilmesine icaze verilmeyen karakter varsa hemin karakteri return edir
	//eger problemli karakter varsa '0' return edir (yoxlama da bu karakter uzerinden aparilir)

	int a;

	for (size_t i = 0; i < email.size(); i++) {
		a = int(email[i]);
		if (!(
			(64 <= a and a <= 90) or
			(97 <= a and a <= 122) or
			(48 <= a and a <= 57) or
			a == 95 or a == 45 or a == 46 or a == 32))
		{
			return email[i];
		}
	}

	return '0';
}

char notAllowedCharactersInBirthDate(string contact) {
	//birthdate-de istifade edilmesine icaze verilmeyen karakter varsa hemin karakteri return edir
	//eger problemli karakter varsa '0' return edir (yoxlama da bu karakter uzerinden aparilir)
	int a;

	for (size_t i = 0; i < contact.size(); i++) {
		a = int(contact[i]);
		if (!(
			(48 <= a and a <= 57) or
			a == 46
			))
		{
			return contact[i];
		}
	}

	return '0';
}

#pragma endregion

#pragma region Error Texts
//et -> error text
//error textlerinin formalasdirilmasi ucun

string et1(string txt) {
	//empty olmayan deyerler
	return string(txt + " can not be empty...");
}

string et2(string txt, string min, string max) {
	//araliq deyerleri
	return string(txt + " has to be between " + min + " and " + max);
}

string et3(char chr) {
	//gonderilen xarakterden istifade etmek olmaz
	return string(chr + " can not be used");
}

string et4(string txt1, string txt2, int t = 1) {
	//1 - az ola bilmez
	//2 - cox ola bilmez

	switch (t)
	{
	case 1:
		return string(txt1 + " can not be less than " + txt2);
	case 2:
		return string(txt1 + " can not be larger than " + txt2);
	default:
		return string(txt1 + " can not be less than " + txt2);
	}
}

#pragma endregion


