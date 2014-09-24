#include <iostream>
#include "Account.cpp"

using namespace std;

class Saving: public Account {
	double interest;

public:
	Saving(int);
	Saving(int, double);
	double getInterest();

};

Saving::Saving(int amount, double i) {
	balance = amount;
	interest = i;
}

Saving::Saving(int amount) {
	balance = amount;
}