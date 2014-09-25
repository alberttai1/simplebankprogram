#include <iostream>
#include "accounts.cpp"
#include "User.cpp"

using namespace std;

class Customer: public User {
	friend class Manager; //friend class with teh manager. so manager has access to all methods and variables of Customer class.
	Chequing chequing = NULL;
	Saving saving = NULL;
	bool canCheque = false; //keeps track whether the chequing and saving accounts have been initialized.
	bool canSave = false;

public: //declares all public methods.
	Customer(string, string); //constructors.
	Customer(string, string, int);
	Customer(string, string, int, int);
	void depositChequing(int);
	void depositSaving(int);
	void withdrawChequing(int);
	void withdrawSaving(int);
	bool isChequing();
	bool isSaving(); //returns whether the savings and chequing accounts have been initialized.
	void openChequing();
	void openSaving();
	void closeChequing(); //closes open chequing and saving accounts.
	void closeSaving();
	int getChequingBalance();//returns the balance of chequing and saving accounts.
	int getSavingBalance();

};


Customer::Customer(string firstName, string lastName): User(firstName, lastName) {}

Customer::Customer(string firstName, string lastName, int camount): User(firstName, lastName) {
	openChequing();
	chequing = Chequing(camount);
}

Customer::Customer(string firstName, string lastName, int camount, int samount): User(firstName, lastName) {
	if (camount > 0)
		openChequing();
	if (samount > 0)
		openSaving();
	chequing = Chequing(camount);
	saving = Saving(samount);
}

void Customer::depositChequing(int amount) {
	chequing.deposit(amount);
}

void Customer::depositSaving(int amount) {
	saving.deposit(amount);
}

void Customer::withdrawChequing(int amount) {
	chequing.withdraw(amount);
}

void Customer::withdrawSaving(int amount) {
	saving.withdraw(amount);
}

bool Customer::isChequing(){return canCheque;}

bool Customer::isSaving(){return canSave;}

void Customer::openChequing() {
	canCheque = true;
}

void Customer::openSaving() {
	canSave = true;
}

void Customer::closeChequing() {
	canCheque = false;
}

void Customer::closeSaving() {
	canSave = false;
}

int Customer::getChequingBalance() {return chequing.getBalance();}

int Customer::getSavingBalance() {return saving.getBalance();}



class Manager: public User { //manager class. inherits from User class

public:
	Manager(string, string);
	void closeChequing(Customer);
	void closeSaving(Customer);
	void openChequing(Customer);
	void openSaving(Customer);
	void getChequingBalance(Customer);
	void getSavingBalance(Customer);
};

Manager::Manager(string firstName, string lastName): User(firstName, lastName) {}

void Manager::closeChequing(Customer customer) {

}