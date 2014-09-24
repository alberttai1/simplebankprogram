#include <iostream>
#include "accounts.cpp"
#include "User.cpp"

using namespace std;

class Customer: public User {
	friend class Manager;
	Chequing chequing = NULL;
	Saving saving = NULL;

public:
	Customer(string, string);
	Customer(string, string, int);
	Customer(string, string, int, int);
	void depositChequing(int);
	void depositSaving(int);
	void withdrawChequing(int);
	void withdrawSaving(int);
	int getChequingBalance();
	int getSavingBalance();

};


Customer::Customer(string firstName, string lastName): User(firstName, lastName) {}

Customer::Customer(string firstName, string lastName, int camount): User(firstName, lastName) {
	chequing = Chequing(camount);
}

Customer::Customer(string firstName, string lastName, int camount, int samount): User(firstName, lastName) {
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

int Customer::getChequingBalance() {return chequing.getBalance();}

int Customer::getSavingBalance() {return saving.getBalance();}



class Manager: public User {

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