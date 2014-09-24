#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "users.cpp"

using namespace std;

void selectSaving(Customer *customer) {
    string options[5] = {"Make a deposit", "Make a withdrawl.", "Transfer to chequing", "Check Balance", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i];
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "How much would you like to deposit?" << endl;
            int amount;
            cin >> amount;

            customer->depositSaving(amount);

            cout << "Your new balance is $" << customer->getSavingBalance() << endl;
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << endl;
            int amount;
            cin >> amount;
            int diff = customer->getSavingBalance() - amount;
            if (diff < 0) {
                cout << "Insufficient funds." << endl;
            } else {
                customer->withdrawSaving(amount);
            }

            cout << "Your current balance is " << customer->getSavingBalance() << endl;
        } else if (choice == 3) {
            cout << "How much would you like to transfer?" << endl;
            int tamount;
            cin >> tamount;

            int diff = customer->getSavingBalance() - tamount;
            if (diff < 0) {
                cout << "Insufficient funds." << endl;
            } else {
                customer->withdrawSaving(tamount);
                customer->depositChequing(tamount);
                cout << "Chequing Balance: " << customer->getChequingBalance() << endl;
            }

            cout << "Savings Balance: " << customer->getSavingBalance() << endl;
        } else if (choice == 4) {
            cout << "Your balance is " << customer->getSavingBalance() << endl;
        }
    }
}

void selectChequing(Customer *customer) {
    string options[5] = {"Make a deposit.", "Make a withdrawl.", "Transfer to savings.", "Check Balance.", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i];
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "How much would you like to deposit?" << endl;
            int amount;
            cin >> amount;

            customer->depositChequing(amount);

            cout << "Your new balance is $" << customer->getChequingBalance() << endl;
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << endl;
            int amount;
            cin >> amount;

            int diff = customer->getChequingBalance() - amount - 2;
            if (diff < 1000 && diff > 0) {
                cout << "Your balance will be " << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << endl;
                string ans;
                cin >> ans;

                if (ans.compare("yes") == 0) {
                    customer->withdrawChequing(amount + 2);
                }
            } else if (diff < 0) {
                cout << "Insufficient funds." << endl;
            } else {
                customer->withdrawChequing(amount);
            }

            cout << "Your current balance is " << customer->getChequingBalance() << endl;
        } else if (choice == 3) {
            cout << "How much would you like to transfer?" << endl;
            int tamount;
            cin >> tamount;

            int diff = customer->getChequingBalance() - tamount;
            if (diff < 0) {
                cout << "Insufficient funds." << endl;
            } else {
                customer->withdrawChequing(tamount);
                customer->depositSaving(tamount);
                cout << "Saving Balance: " << customer->getSavingBalance() << endl;
            }

            cout << "Chequing Balance: " << customer->getChequingBalance() << endl;
            
        } else if (choice == 4) {
            cout << "Your balance is " << customer->getChequingBalance() << endl;
        }
    }
}

void transaction(Customer *customer) {
    bool performingTransaction = true;
    string options[3] = {"Select Chequing", "Select Saving", "Exit"};
    while (performingTransaction) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i];
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            selectChequing(customer);
        } else if (choice == 2) {
            selectSaving(customer);
        } else if (choice == 3) {
            performingTransaction = false;
        }
    }
}

void signUp() {
    ofstream accounts;
    accounts.open("accounts.txt", ios::out | ios::app);

    string username;
    string password;
    string secPass;
    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    cout << "Re-Enter Password: ";
    cin >> secPass;

    if (secPass == password) {
        accounts << username << "," << password << endl;
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
                cout << "Welcome " << username << "!" << endl;
                Customer tmp = (loadCustomer(username));
                transaction(&tmp);
            }
        }
    }
}

int main() {

    login();

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