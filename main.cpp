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
    bool withdraw(int);
    int balancechk();
    account();
    account(int);
    bool status;
    
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
bool account::withdraw(int withdrawcash){
    if (withdrawcash > balance){
        std::cout<<"Error: Insufficient funds, Withdrawing terminated. Your balance is: ";
        return 0;
    }
    else{
        balance = balance - withdrawcash;
        return 1;
        
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
    void chequingToSaving(int);
    void savingToChequing(int);
    client(int);
    int balanceSavingChk();
    int balanceChequingChk();
private:
    saving savingAccount;
    chequing chequingAccount;
};

int client::balanceSavingChk(){
    return savingAccount.balancechk();
}
int client::balanceChequingChk(){
    return chequingAccount.balancechk();
}
void client::chequingToSaving(int transfer){
    if(chequingAccount.withdraw(transfer)==1){
        savingAccount.deposit(transfer);
    }
    else{
        std::cout<<"Cannot transfer due to insufficient funds in chequing";
    }
}
void client::savingToChequing(int transfer){
    if(savingAccount.withdraw(transfer)==1){
        chequingAccount.deposit(transfer);
    }
    else{
        std::cout<<"Cannot transfer due to insufficient funds in savings";
    }
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
    albert.savingToChequing(500);
    std::cout<<albert.balanceSavingChk()<<std::endl;
    std::cout<<albert.balanceChequingChk()<<std::endl;
    
    return 0;
}

