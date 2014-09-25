#include <iostream>
#include "Account.cpp"

using namespace std;

//----------------------------------------------------------------------------------------
class Chequing: public Account { //chequing account has access to all variables and functions of the Account class.

public:
	Chequing(int amount): Account(amount) {} //initializes the chequing account with the specified param.

};
//----------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------
class Saving: public Account { //saving account has access to all variables and functions of the account class.
	double interest;

public:	//declares all public methods.
	Saving(int amount); //initializes savings account with the specified param
	Saving(int, double); //initializes savings account with the spcified amount and interest.
	double getInterest();

};

Saving::Saving(int amount): Account(amount) {} //constructor.

Saving::Saving(int amount, double i) { //constructor
	balance = amount;
	interest = i;
}


//----------------------------------------------------------------------------------------