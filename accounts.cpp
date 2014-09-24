#include <iostream>
#include "Account.cpp"

using namespace std;

//----------------------------------------------------------------------------------------
class Chequing: public Account {

public:
	Chequing(int amount): Account(amount) {}

};
//----------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------
class Saving: public Account {
	double interest;

public:
	Saving(int amount);
	Saving(int, double);
	double getInterest();

};

Saving::Saving(int amount): Account(amount) {}

Saving::Saving(int amount, double i) {
	balance = amount;
	interest = i;
}


//----------------------------------------------------------------------------------------