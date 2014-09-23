//
//  main.cpp
//  cs3307asn1
//
//  Created by Albert on 2014-09-08.
//  Copyright (c) 2014 ttai3. All rights reserved.
//

#include <iostream>

class account{
public:
    void deposit(int);
    void withdraw(int);
    int balancechk();
    account();
    account(int);

    
private:
    //std::string username;
    //std::string password;
    int balance;
};
account::account(int balanceset){
    balance = balanceset;
}
account::account(){
    
}
void account::deposit(int depositcash){
    balance = balance + depositcash;
    
    
}
void account::withdraw(int withdrawcash){
    if (withdrawcash > balance){
        std::cout<<"Error: Insufficient funds, Withdrawing terminated. Your balance is: ";
        
    }
    else{
        balance = balance - withdrawcash;
        
    }
    
}
int account::balancechk(){
    return balance;
}

class chequing : public account{

};
class saving : public account{

};
class client{
public:
    void depositSaving(int);
    client(int);
    int balanceSavingChk();
private:
    saving savingAccount;
    chequing chequingAccount;
};
int client::balanceSavingChk(){
    return savingAccount.balancechk();
}
void client::depositSaving(int moneysavings){
    savingAccount.deposit(moneysavings);
    
}
client::client(int startingcash){
    savingAccount.deposit(startingcash);
    chequingAccount.deposit(0);
}
int main(int argc, const char * argv[])
{
    // login for permission
   
    client albert(5090);
    std::cout<<albert.balanceSavingChk()<<std::endl;
    albert.depositSaving(8);
    std::cout<<albert.balanceSavingChk()<<std::endl;
    
    return 0;
}

