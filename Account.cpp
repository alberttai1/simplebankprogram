#include <iostream>

class Account{
protected:
	int balance;

public:
	Account();
	Account(int);
	void withdraw(int);
	void deposit(int);
	int getBalance();
};

Account::Account() : balance(0) {}

Account::Account(int amount) : balance(amount) {}

void Account::withdraw(int amount) {balance -= amount;}

void Account::deposit(int amount) {balance += amount;}

int Account::getBalance() {return balance;}