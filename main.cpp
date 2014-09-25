#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "users.cpp"

using namespace std;

void selectSaving(Customer *customer) {
    string options[5] = {"Make a deposit", "Make a withdrawl.", "Transfer to chequing", "Check Balance", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "How much would you like to deposit?" << "\n";
            int amount;
            cin >> amount;

            customer->depositSaving(amount);

            cout << "Your new balance is $" << customer->getSavingBalance() << "\n";
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << "\n";
            int amount;
            cin >> amount;
            int diff = customer->getSavingBalance() - amount;
            if (diff < 0) {
                cout << "Insufficient funds." << "\n";
            } else {
                customer->withdrawSaving(amount);
            }

            cout << "Your current balance is " << customer->getSavingBalance() << "\n";
        } else if (choice == 3) {
            cout << "How much would you like to transfer?" << "\n";
            int tamount;
            cin >> tamount;

            int diff = customer->getSavingBalance() - tamount;
            if (diff < 0) {
                cout << "Insufficient funds." << "\n";
            } else {
                customer->withdrawSaving(tamount);
                customer->depositChequing(tamount);
                cout << "Chequing Balance: $" << customer->getChequingBalance() << "\n";
            }

            cout << "Savings Balance: $" << customer->getSavingBalance() << "\n";
        } else if (choice == 4) {
            cout << "Your balance is $" << customer->getSavingBalance() << "\n";
        } else if (choice == 5) {
            break;
        }
    }
}

void selectChequing(Customer *customer) {
    string options[5] = {"Make a deposit.", "Make a withdrawl.", "Transfer to savings.", "Check Balance.", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i]  << endl;
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "How much would you like to deposit?" << "\n";
            int amount;
            cin >> amount;

            customer->depositChequing(amount);

            cout << "Your new balance is $" << customer->getChequingBalance() << "\n";
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << "\n";
            int amount;
            cin >> amount;

            int diff = customer->getChequingBalance() - amount - 2;
            if (diff < 1000 && diff > 0) {
                cout << "Your balance will be $" << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << "\n";
                string ans;
                cin >> ans;

                if (ans.compare("yes") == 0) {
                    customer->withdrawChequing(amount + 2);
                }
            } else if (diff < 0) {
                cout << "Insufficient funds." << "\n";
            } else {
                customer->withdrawChequing(amount);
            }

            cout << "Your current balance is $" << customer->getChequingBalance() << "\n";
        } else if (choice == 3) {
            cout << "How much would you like to transfer?" << "\n";
            int tamount;
            cin >> tamount;

            int diff = customer->getChequingBalance() - tamount;
            if (diff < 0) {
                cout << "Insufficient funds." << "\n";
            } else {
                customer->withdrawChequing(tamount);
                customer->depositSaving(tamount);
                cout << "Saving Balance: $" << customer->getSavingBalance() << "\n";
            }

            cout << "Chequing Balance: $" << customer->getChequingBalance() << "\n";
            
        } else if (choice == 4) {
            cout << "Your balance is $" << customer->getChequingBalance() << "\n";
        } else if (choice == 5) {
            break;
        }
    }
}

void transaction(Customer *customer, string username) {
    bool performingTransaction = true;
    string options[3] = {"Select Chequing", "Select Saving", "Exit"};
    while (performingTransaction) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            selectChequing(customer);
        } else if (choice == 2) {
            selectSaving(customer);
        } else if (choice == 3) {
            ofstream file;
            string filename = username + ".txt";
            file.open(filename.c_str(), ios::out);
            file << customer->getFirstName() << "\n" << customer->getLastName() << "\n" << customer->getChequingBalance() << "\n" << customer->getSavingBalance() << "\n";
            file.close();
            performingTransaction = false;
        }
    }
}

bool checkForExistingAccount(string username) {
    ifstream accounts;
    accounts.open("accounts.txt");

    string user;
    while (getline(accounts, user)) {
        user = user.substr(0, user.find(","));

        if (user.compare(username) == 0) {
            accounts.close();
            return true;
        }
    }
    accounts.close();

    return false;
}

void signup() {
    ofstream accounts;
    accounts.open("accounts.txt", ios::out | ios::app);

    bool signingup = true;
    while (signingup) { 
        string username;
        string password;
        string secPass;
        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        cout << "Re-Enter Password: ";
        cin >> secPass;

        if (checkForExistingAccount(username)) {
            cout << "Username already exists!" << endl;
        } else if (secPass == password) {
            accounts << username << "," << password << "\n";
            string fname;
            string lname;
            cout << "What is your first name?" << endl;
            cin >> fname;
            cout << "What is your last name?" << endl;
            cin >> lname;
            ofstream newAccount;
            string newFile = username + ".txt";
            newAccount.open(newFile.c_str());
            newAccount << fname << "\n" << lname << "\n" << 0 << "\n" << 0 << "\n";
            newAccount.close();
            signingup = false;
        } else {
            cout << "Passwords did not match." << endl;
        }
    }

    accounts.close();
}

Customer loadCustomer(string username) {
    ifstream user;
    string filename = username + ".txt";
    user.open(filename.c_str());

    string firstname;
    string lastname;
    string chequingStr;
    string savingsStr;

    getline(user, firstname);
    getline(user, lastname);
    getline(user, chequingStr);
    getline(user, savingsStr);

    user.close();

    int chequing = atoi(chequingStr.c_str());
    int saving = atoi(savingsStr.c_str());

    Customer tmp(firstname, lastname, chequing, saving);

    return tmp;

}

void manageCustomer(Customer *customer) {
    string options[4] = {"Open an account", "Close an account", "View details", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter a number from 1-" << sizeof(options)/sizeof(options[0]) << ")" << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice;

        if (choice == 1) {

        } else if (choice == 2) {
            cout << "Which account would you like to close? (1-2)" << endl;
            cout << "1. Chequing" << endl;
            cout << "2. Saving" << endl;

            cin >> choice;
            if (choice == 1) {
                customer->withdrawChequing(customer->getChequingBalance());
            } else if (choice == 2) {
                customer->withdrawSaving(customer->getSavingBalance());
            }
        } else if (choice == 3) {
            cout << "Chequing Balance: $" << customer->getChequingBalance() << endl;
            cout << "Saving Balance: $" << customer->getSavingBalance() << endl;
        } else if (choice == 4) {
            break;
        }
    }
}

void manager() {
    vector<Customer> customers;

    ifstream accounts;
    accounts.open("accounts.txt");

    string line;
    while (getline(accounts, line)) {
        int cpos = line.find(",");
        string username = line.substr(0, cpos);
        if (username.compare("manager") == 0 || username.compare("maintenance") == 0)
            continue;

        Customer tmp = loadCustomer(username);
        customers.insert(customers.end(), tmp);
    }

    accounts.close();

    string options[3] = {"Select Customers", "Display All Balances", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter a number from 1-" << sizeof(options)/sizeof(options[0]) << ")" << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Choose a customer:" << endl;
            int i = 0;
            for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it, i++) {
                cout << (i + 1) << ". " << it->getFirstName() << " " << it->getLastName() << endl;
            }

            cin >> choice;
            manageCustomer(&customers.at(choice - 1));

        } else if (choice == 2) {
            printf("%s\t\t\t\t%s\t\t%s\n", "Name", "Chequing" ,"Saving");
            int i = 0;
            for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it, i++) {
                printf("%s %s\t\t\t%d\t\t\t%d\n", (it->getFirstName()).c_str(), (it->getLastName()).c_str(), it->getChequingBalance(), it->getSavingBalance());
                // cout << (i + 1) << ". " << it->getFirstName() << " " << it->getLastName() << endl;
                // cout << "Chequing Balance: "
            }
        } else if (choice == 3) {
            break;
        }
    }
}

void login() {
    ifstream accounts;
    accounts.open("accounts.txt");

    string username;
    string password;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    string line;
    while (getline(accounts, line)) {
        int pos = line.find(',', 0);
        string name = line.substr(0, pos);

        if (username.compare(name) == 0) {
            string pass = line.substr(pos + 1, line.max_size());
            if (pass.compare(password) == 0) {
                cout << "Welcome " << username << "!" << "\n";
                if (username.compare("manager") == 0) {
                    manager();
                } else if (username.compare("maintenance") == 0) {

                } else {
                    Customer tmp = (loadCustomer(username));
                    accounts.close();
                    transaction(&tmp, username);
                }
            }
        }
    }
}

int main() {

    printf("Welcome to the Bank!\n");
    string options[3] = {"Login", "Sign up", "Exit"};

    while (true) {
        cout << "What would you like to do? (Enter a number from 1-" << sizeof(options)/sizeof(options[0]) << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice;
        if (choice == 1) {
            login();
        } else if (choice == 2) {
            signup();
        } else if (choice == 3) {
            break;
        }
    }

    // login();

    // Customer bowen("Bowen", "Jiang", 400, 200);

    // cout << "Chequing Account: " << bowen.getChequingBalance() << endl;
    // cout << "Savings Account: " << bowen.getSavingBalance() << endl;

    // User albert("albert", "tai");
    // cout << albert.getFirstName() << "\n";

    // Chequing umar(100);
    // cout << umar.getBalance() << "\n";

    // umar.withdraw(80);
    // cout << umar.getBalance() << "\n";

    // umar.deposit(300);
    // cout << umar.getBalance() << "\n";

    return 0;
}