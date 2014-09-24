//
//  main.cpp
//  cs3307asn1
//
//  Created by Albert on 2014-09-08.
//  Copyright (c) 2014 ttai3. All rights reserved.
//

#include <iostream>

class Account{
public:
    void deposit(int);
    void setBalance(int);
    bool withdraw(int);
    int balancechk();
    Account();
    Account(int);
    int status();

    
private:
    //std::string username;
    //std::string password;
    int balance;
};
Account::Account(int balanceset){ //set the balance it is the constructor
    balance = balanceset;
}
Account::Account(){
    
}
void Account::setBalance(int balanceAmount){
    balance = balanceAmount;
}
int Account::status(){
    if (balance > 0){
        return 3; //account open
    }
    else if (balance == 0){
        return 2; //account can be closed
    }
    else{
        return 1; //account is closed
    }
}
void Account::deposit(int depositcash){
    balance = balance + depositcash;
    
    
}
bool Account::withdraw(int withdrawcash){
    if (withdrawcash > balance){
        std::cout<<"Error: Insufficient funds, Withdrawing terminated. Your balance is: ";
        return 0;
    }
    else{
        balance = balance - withdrawcash;
        return 1;
        
    }
    
}
int Account::balancechk(){
    return balance;
}

class Chequing : public Account{

};
class Saving : public Account{

};
class Client{
public:
    void depositSaving(int);
    void chequingToSaving(int);
    void savingToChequing(int);
    Client(int);
    int balanceSavingChk();
    int balanceChequingChk();
    void closeAccount(Account);
private:
    Saving savingAccount;
    Chequing chequingAccount;
};

int Client::balanceSavingChk(){
    return savingAccount.balancechk();
}
int Client::balanceChequingChk(){
    return chequingAccount.balancechk();
}
void closeAccount(Account accountToClose){
    if (accountToClose.status() == 2){
        accountToClose.setBalance(-1);
        std::cout<<"Account is closed"<<std::endl;
    }
    else if (accountToClose.status()==3){
        std::cout<<"Account cannot be close as the balance is not 0"<<std::endl;
    }
    else{
        std::cout<<"Account cannot be closed as it is already closed"<<std::endl;
    }
}
void Client::chequingToSaving(int transfer){
    if(chequingAccount.withdraw(transfer)==1){
        savingAccount.deposit(transfer);
    }
    else{
        std::cout<<"Cannot transfer due to insufficient funds in chequing";
    }
}
void Client::savingToChequing(int transfer){
    if(savingAccount.withdraw(transfer)==1){
        chequingAccount.deposit(transfer);
    }
    else{
        std::cout<<"Cannot transfer due to insufficient funds in savings";
    }
}
void Client::depositSaving(int moneysavings){
    savingAccount.deposit(moneysavings);
    
}
Client::Client(int startingcash){
    savingAccount.deposit(startingcash);
    chequingAccount.deposit(0);
}
int main(int argc, const char * argv[])
{
    // login for permission
   
    Client albert(5090);
    std::cout<<albert.balanceSavingChk()<<std::endl;
    albert.depositSaving(8);
    std::cout<<albert.balanceSavingChk()<<std::endl;
    albert.savingToChequing(500);
    std::cout<<albert.balanceSavingChk()<<std::endl;
    std::cout<<albert.balanceChequingChk()<<std::endl;
    
    return 0;
}

