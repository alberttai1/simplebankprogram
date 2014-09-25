#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "users.cpp" //include the users.cpp

using namespace std;

bool tracking = false; //tells you whether tracking is on...default is off
ofstream trackFile; //track file we store our tracking into

void closeAccount(Customer *customer) {
    cout << "Which account would you like to close? (1-2)" << endl; //asks users which accounts wants to be closed
    cout << "1. Chequing" << endl;
    cout << "2. Saving" << endl;

    int choice;
    cin >> choice;
    if (choice == 1) { //choose to close chequeing account
        if (customer->getChequingBalance() == 0) { //checks if balance is zero or not
            customer->closeChequing(); //call method to close
        } else {
            cout << "Account cannot be closed. Balance is not $0." << endl; //account can't be closed as balance isn't zero
            if (tracking) { //if tracking is on
                trackFile << "Account cannot be closed. Balance is not $0." << endl; //store same output into the tracking file
            }
        }
    } else if (choice == 2) { //choose to close savings account
        if (customer->getSavingBalance() == 0) { //checks if balance is zero or not
            customer->closeSaving(); //call method to close saving
        } else {
            cout << "Account cannot be closed. Balance is not $0." << endl; //let user know account can't be closed as balance isn't zero
            if (tracking) { //if tracking is on
                trackFile << "Account cannot be closed. Balance is not $0." << endl; //store same output into the tracking file
            }
        }
        
    }
}

void openAccount(Customer *customer) { //open account for customer
    cout << "Which account would you like to open? (1-2)" << endl; //asks which one the customer wants to open
    cout << "1. Chequing" << endl;
    cout << "2. Saving" << endl;

    int choice; //choice the customer makes
    cin >> choice; //save it into the variable
    if (choice == 1) { //customer chose to open a chequing account
        if (!(customer->isChequing())) {
            customer->openChequing(); //open chequing
        } else {
            cout << "Account already exists. Balance is $" << customer->getChequingBalance() << endl;
            if (tracking) {
                trackFile << "Account already exists. Balance is $" << customer->getChequingBalance() << endl;
            }
        }
    } else if (choice == 2) {
        if (!(customer->isSaving())) {
            customer->openSaving();
        } else {
            cout << "Account already exists. Balance is $" << customer->getSavingBalance() << endl;
            if (tracking) {
                trackFile << "Account already exists. Balance is $" << customer->getSavingBalance() << endl;
            }
        }
        
    } 
}

void selectSaving(Customer *customer) {
    string options[5] = {"Make a deposit", "Make a withdrawl.", "Transfer to chequing", "Check Balance", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        if (tracking) {
            trackFile << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl;
        }
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl;
            }
        }
        int choice;
        cin >> choice;
        if (tracking) {
            trackFile << choice << endl;
        }

        if (choice == 1) {
            cout << "How much would you like to deposit?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to deposit?" << endl;
            }
            int amount;
            cin >> amount;
            if (tracking) {
                trackFile << amount << endl;
            }

            customer->depositSaving(amount);

            cout << "Your new balance is $" << customer->getSavingBalance() << "\n";
            if (tracking) {
                trackFile << "Your new balance is $" << customer->getSavingBalance() << endl;
            }
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to withdraw?" << endl;
            }
            int amount;
            cin >> amount;
            if (tracking) {
                trackFile << amount << endl;
            }
            int diff = customer->getSavingBalance() - amount;
            if (diff < 0) {
                cout << "Insufficient funds." << "\n";
                if (tracking) {
                    trackFile << "Insufficient funds." << endl;
                }
            } else {
                customer->withdrawSaving(amount);
            }

            cout << "Your current balance is " << customer->getSavingBalance() << "\n";
            if (tracking) {
                trackFile << "Your current balance is " << customer->getSavingBalance() << endl;
            }
        } else if (choice == 3) {
            cout << "How much would you like to transfer?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to transfer?" << endl;
            }
            int tamount;
            cin >> tamount;
            if (tracking) {
                trackFile << tamount << endl;
            }

            int diff = customer->getSavingBalance() - tamount;
            if (diff < 0) {
                cout << "Insufficient funds." << "\n";
                if (tracking) {
                    trackFile << "Insufficient funds." << endl;
                }
            } else {
                customer->withdrawSaving(tamount);
                customer->depositChequing(tamount);
                cout << "Chequing Balance: $" << customer->getChequingBalance() << "\n";
                if (tracking) {
                    trackFile << "Chequing Balance: $" << customer->getChequingBalance() << endl;
                }
            }

            cout << "Savings Balance: $" << customer->getSavingBalance() << "\n";
            if (tracking) {
                trackFile << "Savings Balance: $" << customer->getSavingBalance() << endl;
            }
        } else if (choice == 4) {
            cout << "Your balance is $" << customer->getSavingBalance() << "\n";
            if (tracking) {
                trackFile << "Your balance is $" << customer->getSavingBalance() << endl;
            }
        } else if (choice == 5) {
            break;
        }
    }
}

void selectChequing(Customer *customer) {
    string options[5] = {"Make a deposit.", "Make a withdrawl.", "Transfer to savings.", "Check Balance.", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        if (tracking) {
            trackFile << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl;
        }
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i]  << endl;
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl;
            }
        }
        int choice;
        cin >> choice;
        if (tracking) {
            trackFile << choice << endl;
        }

        if (choice == 1) {
            cout << "How much would you like to deposit?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to deposit?" << endl;
            }
            int amount;
            cin >> amount;
            if (tracking) {
                trackFile << amount << endl;
            }

            customer->depositChequing(amount);

            cout << "Your new balance is $" << customer->getChequingBalance() << "\n";
            if (tracking) {
                trackFile << "Your new balance is $" << customer->getChequingBalance() << endl;
            }
        } else if (choice == 2) {
            cout << "How much would you like to withdraw?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to withdraw?" << endl;
            }
            int amount;
            cin >> amount;
            if (tracking) {
                trackFile << amount << endl;
            }

            int diff = customer->getChequingBalance() - amount - 2;
            if (diff < 1000 && diff > 0) {
                cout << "Your balance will be $" << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << "\n";
                if (tracking) {
                    trackFile << "Your balance will be $" << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << endl;
                }

                string ans;
                cin >> ans;
                if (tracking) {
                    trackFile << ans << endl;
                }


                if (ans.compare("yes") == 0) {
                    customer->withdrawChequing(amount + 2);
                }
            } else if (diff < 0) {
                cout << "Insufficient funds." << "\n";
                if (tracking) {
                    trackFile << "Insufficient funds." << endl;
                }
            } else {
                customer->withdrawChequing(amount);
            }

            cout << "Your current balance is $" << customer->getChequingBalance() << "\n";
            if (tracking) {
                trackFile << "Your current balance is $" << customer->getChequingBalance() << endl;
            }
        } else if (choice == 3) {
            cout << "How much would you like to transfer?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to transfer?" << endl;
            }
            int tamount;
            cin >> tamount;
            if (tracking) {
                trackFile << tamount << endl;
            }

            int diff = customer->getChequingBalance() - tamount;
            if (diff < 0) {
                cout << "Insufficient funds." << "\n";
                if (tracking) {
                    trackFile << "Insufficient funds." << endl;
                }
            } else {
                customer->withdrawChequing(tamount);
                customer->depositSaving(tamount);
                cout << "Saving Balance: $" << customer->getSavingBalance() << "\n";
                if (tracking) {
                    trackFile << "Saving Balance: $" << customer->getSavingBalance() << endl;
                }
            }

            cout << "Chequing Balance: $" << customer->getChequingBalance() << "\n";
            if (tracking) {
                trackFile << "Chequing Balance: $" << customer->getChequingBalance() << endl;
            }
            
        } else if (choice == 4) {
            cout << "Your balance is $" << customer->getChequingBalance() << "\n";
            if (tracking) {
                trackFile << "Your balance is $" << customer->getChequingBalance() << endl;
            }
        } else if (choice == 5) {
            break;
        }
    }
}

void transaction(Customer *customer, string username) {
    bool performingTransaction = true;
    string options[5] = {"Select Chequing", "Select Saving", "Close Account", "Open Account", "Exit"};
    while (performingTransaction) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl;
            }
        }
        int choice;
        cin >> choice;
        if (tracking) {
            trackFile << choice << endl;
        }

        if (choice == 1) {
            selectChequing(customer);
        } else if (choice == 2) {
            selectSaving(customer);
        } else if (choice == 3) {
            closeAccount(customer);
        } else if (choice == 4) {
            openAccount(customer);
        }
        else if (choice == 5) {
            ofstream file;
            string filename = username + ".txt";
            file.open(filename.c_str(), ios::out);
            if (tracking) {
                trackFile << "User file opened." << endl;
            }
            file << customer->getFirstName() << "\n" << customer->getLastName() << "\n" << customer->getChequingBalance() << "\n" << customer->getSavingBalance() << "\n";
            if (tracking) {
                trackFile << customer->getFirstName() << "\n" << customer->getLastName() << "\n" << customer->getChequingBalance() << "\n" << customer->getSavingBalance() << "\n";
            }
            file.close();
            if (tracking) {
                trackFile << "User file closed." << endl;
            }
            performingTransaction = false;
        }
    }
}

bool checkForExistingAccount(string username) {
    if (tracking) {
        trackFile << "Checking for existing account for " << username << endl;
    }
    ifstream accounts;
    accounts.open("accounts.txt");
    if (tracking) {
        trackFile << "Opened file \"accounts.txt\"." << endl;
    }

    string user;
    while (getline(accounts, user)) {
        user = user.substr(0, user.find(","));

        if (user.compare(username) == 0) {
            accounts.close();
            if (tracking) {
                trackFile << "User found." << endl;
                trackFile << "Closing file \"accounts.txt\"." << endl;
            }
            return true;
        }
    }
    accounts.close();
    if (tracking) {
        trackFile << "Closing file \"accounts.txt\"." << endl;
    }

    return false;
}

void signup() {
    ofstream accounts;
    accounts.open("accounts.txt", ios::out | ios::app);
    if (tracking) {
        trackFile << "File \"accounts.txt\" was opened for append." << endl;
    }

    bool signingup = true;
    while (signingup) { 
        string username;
        string password;
        string secPass;
        cout << "Username: ";
        cin >> username;
        if (tracking) {
            trackFile << username << endl;
        }
        if (tracking) {
            trackFile << "Obtained username from user." << endl;
            trackFile << "Username: " << username << endl;
        }
        cout << "Password: ";
        cin >> password;
        if (tracking) {
            trackFile << "**********" << endl;
        }

        cout << "Re-Enter Password: ";
        cin >> secPass;

        if (tracking) {
            trackFile << "Obtained password from user." << endl;
            trackFile << "Asked for password confirmation." << endl;
        }

        if (checkForExistingAccount(username)) {
            cout << "Username already exists!" << endl;
            if (tracking) {
                trackFile << "Sign up attempt with already existing username." << endl;
            }
        } else if (secPass == password) {
            if (tracking) {
                trackFile << "Username and password confirmed." << endl;
            }
            accounts << username << "," << password << "\n";
            if (tracking) {
                trackFile << "Writing user username and password to \"accounts.txt\"" << endl;
            }
            string fname;
            string lname;
            cout << "What is your first name?" << endl;
            cin >> fname;
            if (tracking) {
                trackFile << "Acquired first name from user." << endl;
            }
            cout << "What is your last name?" << endl;
            cin >> lname;
            if (tracking) {
                trackFile << "Acquired last name from user." << endl;
            }
            ofstream newAccount;
            string newFile = username + ".txt";
            newAccount.open(newFile.c_str());
            if (tracking) {
                trackFile << "Creating new file for user." << endl;
            }
            newAccount << fname << "\n" << lname << "\n" << 0 << "\n" << 0 << "\n";
            if (tracking) {
                trackFile << "Writing user info to file: firstName, lastName, chequing balance, and saving balance" << endl;
            }
            newAccount.close();
            if (tracking) {
                trackFile << "User file closed." << endl;
            }
            signingup = false;
        } else {
            cout << "Passwords did not match." << endl;
            if (tracking) {
                trackFile << "User password did not match." << endl;
            }
        }
    }

    accounts.close();
    if (tracking) {
        trackFile << "Sign up attempt with already existing username." << endl;
    }
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
            openAccount(customer);
        } else if (choice == 2) {
            closeAccount(customer);
            // cout << "Which account would you like to close? (1-2)" << endl;
            // cout << "1. Chequing" << endl;
            // cout << "2. Saving" << endl;

            // cin >> choice;
            // if (choice == 1) {
            //     if (customer->getChequingBalance() == 0) {
            //         customer->closeChequing();
            //     } else {
            //         cout << "Account cannot be closed. Balance is not $0." << endl;
            //         if (tracking) {
            //             trackFile << "Account cannot be closed. Balance is not $0." << endl;
            //         }
            //     }
            // } else if (choice == 2) {
            //     if (customer->getSavingBalance() == 0) {
            //         customer->closeSaving();
            //     } else {
            //         cout << "Account cannot be closed. Balance is not $0." << endl;
            //         if (tracking) {
            //             trackFile << "Account cannot be closed. Balance is not $0." << endl;
            //         }
            //     }
                
            // }
        } else if (choice == 3) {
            if (customer->isChequing()) {
                cout << "Chequing Balance: $" << customer->getChequingBalance() << endl;
                if (tracking) {
                    trackFile << "Chequing Balance: $" << customer->getChequingBalance() << endl;
                }
            }
            if (customer->isSaving()) {
                cout << "Saving Balance: $" << customer->getSavingBalance() << endl;
                if (tracking) {
                    trackFile << "Saving Balance: $" << customer->getSavingBalance() << endl;
                }
            }
        } else if (choice == 4) {
            break;
        }
    }
}

void maintenance() {
    cout << "Would you like to turn on the execution trace?" << endl;

    string choice;
    cin >> choice;

    if (choice.compare("yes") == 0 || choice.compare("Yes") == 0) {
        tracking = true;
        cout << "Tracking is now turned on." << endl;
        trackFile << "Tracking is now turned on." << endl;
    } else if (choice.compare("no") == 0 || choice.compare("No") == 0) {
        tracking = false;
        cout << "Tracking is now turned off." << endl;
        trackFile << "Tracking is now turned off." << endl;
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

    string options[4] = {"Select Customers", "Display All Balances", "Open an account", "Exit"};
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
            if (tracking) {
                trackFile << "Name\t\t\t\tChequing\t\tSaving" << endl;
            }
            int i = 0;
            for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it, i++) {
                printf("%s %s\t\t\t%d\t\t\t%d\n", (it->getFirstName()).c_str(), (it->getLastName()).c_str(), it->isChequing() == true ? (it->getChequingBalance() + ""):"Closed", it->isSaving() == true ? (it->getSavingBalance() + ""):"Closed");

                if (tracking) {
                    trackFile << it->getFirstName() << " " << it->getLastName() << "\t\t\t";
                    if (it->isChequing()) {
                        trackFile << it->getChequingBalance();
                    } else {
                        trackFile << "Closed";
                    }
                    trackFile << "\t\t\t";

                    if (it->isSaving()) {
                        trackFile << it->getSavingBalance() << endl;
                    } else {
                        trackFile << "Closed" << endl;
                    }
                }
                // cout << (i + 1) << ". " << it->getFirstName() << " " << it->getLastName() << endl;
                // cout << "Chequing Balance: "
            }
        } else if (choice == 3) {
            signup();
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
                    maintenance();
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
    trackFile.open(".tracking.txt", ios::out | ios::app);
    printf("Welcome to the Bank!\n");
    string options[2] = {"Login", "Exit"};

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
            break;
        }
    }

    trackFile.close();

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