#include <iostream>

class Account{
protected:
	int balance; 

public:
	Account(); //constructor without parameters 
	Account(int); //constructor with parameter of starting balance 
	void withdraw(int); //withdraw method 
	void deposit(int); //deposit method 
	int getBalance(); //get the balance and return it 
};

Account::Account() : balance(0) {} //initalize the balance to zero 

Account::Account(int amount) : balance(amount) {} //constructor initalize the balance to same amount as parameter you set 

void Account::withdraw(int amount) {balance -= amount;} //withdraw amount and set balance equal after subtracting 

void Account::deposit(int amount) {balance += amount;} //deposit amount and set balance equal after plusing 

int Account::getBalance() {return balance;} //return balnace of it