#include <iostream>
#include <fstream>
#include "users.cpp"

using namespace std;

void selectSaving(Customer customer) {
    string options[2] = {"Make a deposit", "Make a withdrawl."};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i];
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "How much would you like to deposit?" << endl;
            int amount;
            cin >> amount;

            customer.depositSaving(amount);

            cout << "Your new balance is $" << customer.getSavingBalance() << endl;
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << endl;
            int amount;
            cin >> amount;
            int diff = customer.getChequingBalance() - amount;
            if (diff < 0) {
                cout << "Insufficient funds." << endl;
            } else {
                customer.withdrawSaving(amount);
            }

            cout << "Your current balance is " << customer.getSavingBalance() << endl;
        } else if (choice == 3) {
            cout << "Your balance is " << customer.getSavingBalance() << endl;
        }
    }
}

void selectChequing(Customer customer) {
    string options[3] = {"Make a deposit.", "Make a withdrawl.", "Check Balance."};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl;
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i];
        }
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "How much would you like to deposit?" << endl;
            int amount;
            cin >> amount;

            customer.depositChequing(amount);

            cout << "Your new balance is $" << customer.getChequingBalance() << endl;
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << endl;
            int amount;
            cin >> amount;

            int diff = customer.getChequingBalance() - amount - 2;
            if (diff < 1000 && diff > 0) {
                cout << "Your balance will be " << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << endl;
                string ans;
                cin >> ans;

                if (ans.compare("yes") == 0) {
                    customer.withdrawChequing(amount + 2);
                }
            } else if (diff < 0) {
                cout << "Insufficient funds." << endl;
            } else {
                customer.withdrawChequing(amount);
            }

            cout << "Your current balance is " << customer.getChequingBalance() << endl;
        } else if (choice == 3) {
            cout << "Your balance is " << customer.getChequingBalance() << endl;
        }
    }
}

void transaction(Customer customer) {
    bool performingTransaction = true;
    string options[3] = {"Select Chequing", "Select Saving", "Exit"};
    while (performingTransaction) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl;
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
                transaction();
            }
        }
    }
}

int main() {

    Customer bowen("Bowen", "Jiang", 400, 200);

    cout << "Chequing Account: " << bowen.getChequingBalance() << endl;
    cout << "Savings Account: " << bowen.getSavingBalance() << endl;

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