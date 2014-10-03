#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "users.cpp" //include the users.cpp

using namespace std;

bool tracking = false; //tells you whether tracking is on...default is off
ofstream trackFile; //track file we store our tracking into

string encrypt(string value) {
    string toReturn = "";
    for (int i = 0; i < value.size(); i++) {
        char tmp = value.at(i);

        toReturn += (tmp + 3) % 128;
    }

    return toReturn;
}

string decrypt(string value) {
    string toReturn = "";
    for (int i = 0; i < value.size(); i++) {
        char tmp = value.at(i);

        toReturn += (tmp - 3) % 128;
    }

    return toReturn;
}

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
            cout << "Account already exists. Balance is $" << customer->getChequingBalance() << endl; //chequing account already exist 
            if (tracking) { //tracking is on 
                trackFile << "Account already exists. Balance is $" << customer->getChequingBalance() << endl; //store it in the file  
            }
        } 
    } else if (choice == 2) { //if customer wants to open a savings account 
        if (!(customer->isSaving())) { //check if there is a savings acocunt 
            customer->openSaving(); //open savings 
        } else {
            cout << "Account already exists. Balance is $" << customer->getSavingBalance() << endl; //saving account already exist 
            if (tracking) {
                trackFile << "Account already exists. Balance is $" << customer->getSavingBalance() << endl; //save output into savings account 
            }
        }
        
    } 
}

void selectSaving(Customer *customer) {
    string options[5] = {"Make a deposit", "Make a withdrawal.", "Transfer to chequing", "Check Balance", "Exit"};
    while (true) {
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        if (tracking) { //if tracking is on output how many options were there 
            trackFile << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl;
        }
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) { 
            cout << (i + 1) << ". " << options[i] << endl; //print out the options possible 
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl; //tracking is on copy it to the tracking file 
            }
        }
        int choice; 
        cin >> choice; //user inputs a choice 
        if (tracking) { //if tracking is on 
            trackFile << choice << endl; 
        }

        if (choice == 1) { //if choice selected is make a deposit 
            cout << "How much would you like to deposit?" << "\n"; 
            if (tracking) { //if tracking is on 
                trackFile << "How much would you like to deposit?" << endl; 
            }
            int amount; 
            cin >> amount; //user inputs the amount to deposit 
            if (tracking) { //if tracking is on 
                trackFile << amount << endl; //input it into the tracking file about the deposit amount 
            }

            customer->depositSaving(amount); //deposit the saving of the money 

            cout << "Your new balance is $" << customer->getSavingBalance() << "\n"; //output the new balance back to the users 
            if (tracking) { //if tracking is on 
                trackFile << "Your new balance is $" << customer->getSavingBalance() << endl; //write into tracking file 
            }
        } else if (choice == 2) { //making a withdrawal 
            cout << "How much would you like to withdraw?" << "\n"; //ask how much 
            if (tracking) { //if tracking on 
                trackFile << "How much would you like to withdraw?" << endl; //input it into tracking file 
            }
            int amount;
            cin >> amount; //user input the amount to withdraw
            if (tracking) { //if tracking is on 
                trackFile << amount << endl; //put the amount of money the user tracks into track file 
            }
            int diff = customer->getSavingBalance() - amount; //the difference between user ask to withdraw and the balance 
            if (diff < 0) { //if difference is bigger than zero 
                cout << "Insufficient funds." << "\n"; //can't withdraw as insufficient funds and let user know 
                if (tracking) { //if tracking is on 
                    trackFile << "Insufficient funds." << endl; //put that into the tracking file 
                }
            } else {
                customer->withdrawSaving(amount); //now withdraw the amount of money 
            }

            cout << "Your current balance is " << customer->getSavingBalance() << "\n"; //let the user know how much balance you have 
            if (tracking) {
                trackFile << "Your current balance is " << customer->getSavingBalance() << endl; //tracking is on then put the balance on the tracking file 
            }

        } else if (choice == 3) {
            if (!(customer->isChequing())) {
                cout << "Chequing account is closed." << endl;
                if (tracking) {
                    trackFile << "Chequing account is closed." << endl;
                }
                continue;
            }
            cout << "How much would you like to transfer?" << "\n";
            if (tracking) {
                trackFile << "How much would you like to transfer?" << endl;
            }
            int tamount;
            cin >> tamount; //take the input of the transfer amount 
            if (tracking) { //if tracking is on 
                trackFile << tamount << endl; //put the transfer amount into the track file 
            }

            int diff = customer->getSavingBalance() - tamount; //look at the difference between balance and transfer amount 
            if (diff < 0) { //if difference is below zero 
                cout << "Insufficient funds." << "\n"; //that means not enough funds and let user know 
                if (tracking) { //tracking is on 
                    trackFile << "Insufficient funds." << endl; //put the insufficient funds output into tracking file 
                }
            } else {
                customer->withdrawSaving(tamount); //withdraw savings of the transfer amounts 
                customer->depositChequing(tamount); //deposit transfer amounts into chequing 
                cout << "Chequing Balance: $" << customer->getChequingBalance() << "\n"; 
                if (tracking) { //if tracking is on 
                    trackFile << "Chequing Balance: $" << customer->getChequingBalance() << endl; //put the chequing balance into tracking file 
                }
            }

            cout << "Savings Balance: $" << customer->getSavingBalance() << "\n"; 
            if (tracking) {
                trackFile << "Savings Balance: $" << customer->getSavingBalance() << endl; //if tracking is on then put the savings balance into tracking file 
            }
        } else if (choice == 4) {//if user chose to check balance
            cout << "Your balance is $" << customer->getSavingBalance() << "\n"; //output the balance to user 
            if (tracking) {
                trackFile << "Your balance is $" << customer->getSavingBalance() << endl; //put the output into the tracking file if tracking file is on 
            }
        } else if (choice == 5) { //if user chose to exit 
            break; 
        }
    }
}

void selectChequing(Customer *customer) { //if customer select chequing 
    string options[5] = {"Make a deposit.", "Make a withdrawl.", "Transfer to savings.", "Check Balance.", "Exit"}; 
    while (true) { 
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n"; 
        if (tracking) { //if tracking is on 
            trackFile << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << endl; //output this into tracking file 
        }
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) { 
            cout << (i + 1) << ". " << options[i]  << endl; //show the options 
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl; //put the options into tracking file 
            }
        }
        int choice;
        cin >> choice; //take the input of the users for choices 
        if (tracking) { //if tracking is on 
            trackFile << choice << endl; //put that into tracking file 
        }

        if (choice == 1) { //if user chose make a deposit 
            cout << "How much would you like to deposit?" << "\n";
            if (tracking) { //if tracking is on 
                trackFile << "How much would you like to deposit?" << endl; //put the output file into tracking file 
            }
            int amount; 
            cin >> amount; //take the input of the clients choosing the amount 
            if (tracking) {
                trackFile << amount << endl; //put it into tracking file if tracking is on 
            }

            customer->depositChequing(amount); //deposit into chequing 

            cout << "Your new balance is $" << customer->getChequingBalance() << "\n"; //your new balance of chequing account returned 
            if (tracking) {
                trackFile << "Your new balance is $" << customer->getChequingBalance() << endl; //put into tracking file 
            }
        } else if (choice == 2) { //if the user choose make a withdrawal 
            cout << "How much would you like to withdraw?" << "\n"; 
            if (tracking) { //if tracking is on 
                trackFile << "How much would you like to withdraw?" << endl; //put it into the tracking file 
            }
            int amount;
            cin >> amount; //take the input amount 
            if (tracking) { //check if tracking is on 
                trackFile << amount << endl; //put the amount into the tracking file 
            }

            int diff = customer->getChequingBalance() - amount - 2; //the difference of the chequing balance and the amount
            if (diff < 1000 && diff > 0) { //if difference less than zero and difference is still above zero 
                //warn the users that there will be surcharge of $2 if they continue due to their balance is below 1k. 
                cout << "Your balance will be $" << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << "\n";
                if (tracking) { //if tracking is on
                    //put it into tracking file 
                    trackFile << "Your balance will be $" << diff << ". If you continue a surcharge fee of $2.00 will apply. Would you like to continue? (yes or no)" << endl;
                }

                string ans;
                cin >> ans; //take the input the answer whether or not to continue 
                if (tracking) { //if tracking is on 
                    trackFile << ans << endl; // take the input the answer whether or not to continue into tracking file  
                }


                if (ans.compare("yes") == 0) { //if you chose yes then 
                    customer->withdrawChequing(amount + 2); //withdraw the amount then subtract 2 for service charge 
                }
            } else if (diff < 0) { //if the difference is smaller than zero 
                cout << "Insufficient funds." << "\n"; 
                if (tracking) { //if tracking is on 
                    trackFile << "Insufficient funds." << endl; //just put that into the tracking file 
                }
            } else {
                customer->withdrawChequing(amount); //withdraw chequing 
            }

            cout << "Your current balance is $" << customer->getChequingBalance() << "\n"; //update client on the balance 
            if (tracking) { //if tracking is on 
                trackFile << "Your current balance is $" << customer->getChequingBalance() << endl; //the current balance is this and update on tracking file 
            }
        } else if (choice == 3) { //if they chose to transfer to savings 
            if (!(customer->isSaving())) { //check if savings is opened 
                cout << "Saving account is closed." << endl; //if so then tell them 
                if (tracking) {
                    trackFile << "Saving account is closed." << endl; //write in tracking file that is closed 
                }
                continue; 
            }
            cout << "How much would you like to transfer?" << "\n"; //ask them how much they like to transfer 
            if (tracking) {
                trackFile << "How much would you like to transfer?" << endl; //write in tracking file if tracking is on about how much they are transfering 
            }
            int tamount;
            cin >> tamount; //get the amount of transfer they want from user 
            if (tracking) {
                trackFile << tamount << endl; //write in tracking file if on 
            }

            int diff = customer->getChequingBalance() - tamount; //check the difference between balanace and transfer amount to see if there is enough left 
            if (diff < 0) { //if difference is less than zero 
                cout << "Insufficient funds." << "\n";  //let user know not enough funds 
                if (tracking) {
                    trackFile << "Insufficient funds." << endl;
                }
            } else {
                customer->withdrawChequing(tamount); //withdraw chequing the amount 
                customer->depositSaving(tamount); //deposit it back into savings 
                cout << "Saving Balance: $" << customer->getSavingBalance() << "\n"; //update balnace amount of savings 
                if (tracking) {
                    trackFile << "Saving Balance: $" << customer->getSavingBalance() << endl; //update balance amounts of savings in tracking file 
                }
            }

            cout << "Chequing Balance: $" << customer->getChequingBalance() << "\n"; //update user on balance of chequing 
            if (tracking) {
                trackFile << "Chequing Balance: $" << customer->getChequingBalance() << endl; //put in tracking file of balance of cheque 
            }
            
        } else if (choice == 4) { //if user chose to ccheck  balance 
            cout << "Your balance is $" << customer->getChequingBalance() << "\n"; //your balanace of chequing 
            if (tracking) {
                trackFile << "Your balance is $" << customer->getChequingBalance() << endl;
            }
        } else if (choice == 5) { //if user choose to exit 
            break; //break 
        }
    }
}

void transaction(Customer *customer, string username) { //transcations using customer and username 
    bool performingTransaction = true; //we are performing transcation 
    string options[5] = {"Select Chequing", "Select Saving", "Close Account", "Open Account", "Exit"}; //options you can do with transaction 
    while (performingTransaction) { //
        cout << "What would you like to do? (Enter number between 1-" << sizeof(options)/sizeof(options[0]) << "     " << "\n";
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) { //cycle through options 
            cout << (i + 1) << ". " << options[i] << endl;
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl;
            }
        }
        int choice;
        cin >> choice; //save the choice the person made 
        if (tracking) {
            trackFile << choice << endl; //put into tracker what choice they made 
        }

        if (choice == 1) {
            if (customer->isChequing()){ //check if chequing is not closed 
                selectChequing(customer); //select it 
            } else {
                cout << "Account is closed." << endl;
                if (tracking) {
                    trackFile << "Account is closed." << endl;
                }
            }
        } else if (choice == 2) {
            if (customer->isSaving()) { //check if savings is opened 
                selectSaving(customer); //select it 
            } else {
                cout << "Account is closed." << endl;
                if (tracking) {
                    trackFile << "Account is closed." << endl;
                }
            }
        } else if (choice == 3) {
            closeAccount(customer); //close account 
        } else if (choice == 4) {
            openAccount(customer); //open account 
        }
        else if (choice == 5) { //exit 
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
                time_t rawtime;
                struct tm * timeinfo;

                time (&rawtime);
                timeinfo = localtime (&rawtime);

                trackFile << "Logged out: " << asctime(timeinfo) << endl;
            }
            performingTransaction = false;
        }
    }
}

bool checkForExistingAccount(string username) { //checkin for existing account 
    if (tracking) {
        trackFile << "Checking for existing account for " << username << endl; //put in tracker if tracking is enabled 
    }
    ifstream accounts;
    accounts.open("accounts.txt"); //open it 
    if (tracking) {
        trackFile << "Opened file \"accounts.txt\"." << endl; //let tracker know 
    }

    string user;
    while (getline(accounts, user)) {
        user = user.substr(0, user.find(",")); //check each line for usernames 

        if (user.compare(username) == 0) { //check if same 
            accounts.close();
            if (tracking) {
                trackFile << "User found." << endl; //if so let tracker know user name is found 
                trackFile << "Closing file \"accounts.txt\"." << endl;
            }
            return true;
        }
    }
    accounts.close(); //close 
    if (tracking) {
        trackFile << "Closing file \"accounts.txt\"." << endl; //let tracker know we are closing it 
    }

    return false;
}

Customer signup() { //how to singup 
    ofstream accounts;
    accounts.open("accounts.txt", ios::out | ios::app); //open the file that stores user and passwrod 
    if (tracking) {
        trackFile << "File \"accounts.txt\" was opened for append." << endl; //list it under track file 
    }

    bool signingup = true;
    while (signingup) { 
        string username;
        string password;
        string secPass;
        cout << "Username: "; //ask the user to input username 
        cin >> username; //save it as variable 
        if (tracking) {
            trackFile << username << endl; //put it under tracking info 
        }
        if (tracking) {
            trackFile << "Obtained username from user." << endl;
            trackFile << "Username: " << username << endl;
        }
        cout << "Password: "; //ask user to input password they want 
        cin >> password; //save it as variable 
        if (tracking) {
            trackFile << "**********" << endl; //add it to trackfile 
        }

        cout << "Re-Enter Password: "; //ask them to reenter 
        cin >> secPass; //save it as sec pass 

        if (tracking) {
            trackFile << "Obtained password from user." << endl;
            trackFile << "Asked for password confirmation." << endl;
        }

        if (checkForExistingAccount(username)) { //check if the username is taken 
            cout << "Username already exists!" << endl; //if so tell them they cannot use it 
            if (tracking) {
                trackFile << "Sign up attempt with already existing username." << endl; //let them know username is taken 
            }
        } else if (secPass == password) { //if password and password confirmation is same then go on to second part 
            if (tracking) {
                trackFile << "Username and password confirmed." << endl; //put it into tracking file 
            }
            accounts << username << "," << (encrypt(password)).c_str() << "\n"; //put username,password format into accounts 
            if (tracking) {
                trackFile << "Writing user username and password to \"accounts.txt\"" << endl; //put into tracking file we are writing it to file 
            }
            string fname;
            string lname;
            cout << "What is your first name?" << endl; //ask user to input name 
            cin >> fname; //store it 
            if (tracking) {
                trackFile << "Acquired first name from user." << endl; //put into tracking file if tracking is enabled 
            }
            cout << "What is your last name?" << endl; //what is your last name 
            cin >> lname; //write into it 
            if (tracking) { //if tracking is enabled 
                trackFile << "Acquired last name from user." << endl; //put that we acquired last name as well 
            }
            ofstream newAccount; //creating new file name for customer 
            string newFile = username + ".txt"; //will be named username.txt 
            newAccount.open(newFile.c_str());
            if (tracking) {
                trackFile << "Creating new file for user." << endl;
            }
            newAccount << fname << "\n" << lname << "\n" << 0 << "\n" << 0 << "\n"; //put first name then last name on a new line then 0 for chequing balance and 0 for saving balnace 
            if (tracking) {
                trackFile << "Writing user info to file: firstName, lastName, chequing balance, and saving balance" << endl;
            }
            newAccount.close();
            if (tracking) {
                trackFile << "User file closed." << endl;
            }
            Customer tmp(fname, lname);
            return tmp;
        } else {
            cout << "Passwords did not match." << endl;
            if (tracking) {
                trackFile << "User password did not match." << endl;
            }
        }
    }

    accounts.close();
    if (tracking) {
        trackFile << "Closing accounts file." << endl;
    }

    throw -1;
}

Customer loadCustomer(string username) { //loading customer from username 
    ifstream user;
    string filename = username + ".txt"; //get the filename of username which is username.txt 
    user.open(filename.c_str()); //open it 

    string firstname;
    string lastname;
    string chequingStr;
    string savingsStr;

    getline(user, firstname); //first line is first name 
    getline(user, lastname); //second line is last name 
    getline(user, chequingStr); //third line is chequing info 
    getline(user, savingsStr); //fourth line is saving info 

    user.close(); //user close 

    int chequing = atoi(chequingStr.c_str()); //converts the sring to integer value 
    int saving = atoi(savingsStr.c_str());

    Customer tmp(firstname, lastname, chequing, saving); //create temp customer 

    return tmp; //return the customer obj 

}

void manageCustomer(Customer *customer) { //managing console for managers  
    string options[4] = {"Open an account", "Close an account", "View details", "Exit"}; //give them options 
    while (true) {
        cout << "What would you like to do? (Enter a number from 1-" << sizeof(options)/sizeof(options[0]) << ")" << endl; //option number 
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) { //cycle through 
            cout << (i + 1) << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice; //take input 

        if (choice == 1) { //if they want to open an account 
            openAccount(customer); //open the account for them 
        } else if (choice == 2) { //if they want to close account 
            closeAccount(customer); //close account for them 

        } else if (choice == 3) { //if they want to view details 
            if (customer->isChequing()) { //get their chequing info 
                cout << "Chequing Balance: $" << customer->getChequingBalance() << endl;
                if (tracking) {
                    trackFile << "Chequing Balance: $" << customer->getChequingBalance() << endl;
                }
            }
            if (customer->isSaving()) { //get their saving info 
                cout << "Saving Balance: $" << customer->getSavingBalance() << endl;
                if (tracking) {
                    trackFile << "Saving Balance: $" << customer->getSavingBalance() << endl;
                }
            }
        } else if (choice == 4) { //if they want to exit 
            break; //exit 
        }
    }
}

void maintenance() { //maintenance console 
    cout << "Would you like to turn on the execution trace?" << endl; //asking if you want to run the execution trace 

    string choice;
    cin >> choice; //take the choice 

    if (choice.compare("yes") == 0 || choice.compare("Yes") == 0) { //if choice is yes then 
        tracking = true; //start tracking 
        cout << "Tracking is now turned on." << endl; //let users know tracking is starting 
        trackFile << "Tracking is now turned on." << endl; //put the first line in trackign that tracking got turned on 
    } else if (choice.compare("no") == 0 || choice.compare("No") == 0) { //if tracking isn't turned on 
        tracking = false; //put tracking as false 
        cout << "Tracking is now turned off." << endl; //tracking is turned off let the users know 
        trackFile << "Tracking is now turned off." << endl; //put it into the tracking file as well 
    }
}

void manager() { //managing console 
    vector<Customer> customers; //initalize a vecotr of customers 

    ifstream accounts;
    accounts.open("accounts.txt"); //open the accounts.txt that contains user and apssword 

    string line;
    while (getline(accounts, line)) { //read line per line 
        int cpos = line.find(","); //find the , 
        string username = line.substr(0, cpos); //get the username 
        if (username.compare("manager") == 0 || username.compare("maintenance") == 0) //see if it is a manger 
            continue; //if so continue 

        Customer tmp = loadCustomer(username); //get the customer 
        customers.insert(customers.end(), tmp); //adds customers to the end of the vector 
    }

    accounts.close(); //close the account 

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
            printf("%s\t\t\t\t%s\t\t%s\t\t%s\n", "Name", "Chequing" ,"Saving", "Total");
            if (tracking) {
                trackFile << "Name\t\t\t\tChequing\t\tSaving\t\tTotal" << endl;
            }
            int i = 0;
            for (vector<Customer>::iterator it = customers.begin(); it != customers.end(); ++it, i++) {
                int total = (it->isChequing() == true ? it->getChequingBalance():0) + (it->isSaving() == true ? it->getSavingBalance():0);
                printf("%s %s\t\t\t%d\t\t\t%d\t\t%d\n", (it->getFirstName()).c_str(), (it->getLastName()).c_str(), it->isChequing() == true ? ((it->getChequingBalance())):0, it->isSaving() == true ? ((it->getSavingBalance())):0, total);

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
  
            }
        } else if (choice == 3) {
            try {
                Customer newCustomer = signup();
                customers.insert(customers.end(), newCustomer);
            } catch (int e) {}
        } else if (choice == 4) {
            break;
        }
    }
}

void login() { 
    ifstream accounts; //initalize a ifstream variable 
    accounts.open("accounts.txt"); //open accounts.txt where we store all the user and password 

    string username;
    string password;

    cout << "Username: "; //let users know to type their username 
    cin >> username; //take the input for username 

    cout << "Password: "; //let users know to type their password 
    cin >> password; //take their input for password 

    string line;
    while (getline(accounts, line)) { //get the line from text file and cycle through it 
        int pos = line.find(',', 0); //find the pos where there is , as thats how we seperated user and password 
        string name = line.substr(0, pos); //look from starting to the , that's username 

        if (username.compare(name) == 0) { //if the username is correct or not  
            string pass = decrypt(line.substr(pos + 1, line.max_size())); //then look for the passwor from the end of the position of , to end of the thing 
            if (pass.compare(password) == 0) {//compare to the password if its right if it is then 
                cout << "Welcome " << username << "!" << "\n"; //welcome the user 
                if (username.compare("manager") == 0) { //if the username is manager 
                    manager(); //open manager console 
                } else if (username.compare("maintenance") == 0) { //if the username is maintenance 
                    maintenance(); //open maintenance 
                } else { 
                    Customer tmp = (loadCustomer(username)); //make the customer by loading the username
                    accounts.close(); //close the file
                    
                    if (tracking) {
                        time_t rawtime;
                        struct tm * timeinfo;

                        time (&rawtime);
                        timeinfo = localtime (&rawtime);
                        trackFile << "Login at: " << asctime(timeinfo) << " by " << tmp.getFirstName() << " " << tmp.getLastName() << endl;
                    }


                    transaction(&tmp, username); //open up the field for transcations 
                }
            }
        }
    }
}

int main() { 
    trackFile.open(".tracking.txt", ios::out | ios::app); //open the tracking file 

    ifstream infoFile;
    infoFile.open(".infofile");
    string shouldTrack;
    getline(infoFile, shouldTrack);

    if (shouldTrack.compare("true"))
        tracking = true;

    infoFile.close();

    printf("Welcome to the Bank!\n");
    if (tracking) {
        trackFile << "Welcome to the Bank!" << endl;
    }
    string options[2] = {"Login", "Exit"}; //make an array of string that has two fields 

    while (true) {
        cout << "What would you like to do? (Enter a number from 1-" << sizeof(options)/sizeof(options[0]) << endl; //let the users know how many options to pick from 
        if (tracking) {
            trackFile << "What would you like to do? (Enter a number from 1-" << sizeof(options)/sizeof(options[0]) << endl;
        }
        for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) { //cycle through it 
            cout << (i + 1) << ". " << options[i] << endl;
            if (tracking) {
                trackFile << (i + 1) << ". " << options[i] << endl;
            }
        }
        int choice;
        cin >> choice; //take the users choice 
        if (choice == 1) { //if user chose login 
            login(); //login 
        } else if (choice == 2) { //if user chose exit
            ofstream file;
            file.open(".infofile", ios::out | ios::app);
            file << tracking << endl;
            file.close();
            break; //break it 
        }
    }

    trackFile.close(); //close the tracking file we are writing too if we are tracking 

  

    return 0;
}