#include <iostream>
#include <string>

using namespace std;

class User {
	string fname, lname;

public:
	User(string, string);
	string getFirstName();
	string getLastName();
};


User::User(string firstName, string lastName): fname(firstName), lname(lastName) {}

string User::getFirstName() {return fname;}

string User::getLastName() {return lname;}