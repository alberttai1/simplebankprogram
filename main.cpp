#include <iostream>
#include "account.cpp"

using namespace std;

int main() {

    Account umar(100);
    cout << umar.getBalance() << "\n";

    umar.withdraw(10);
    cout << umar.getBalance() << "\n";

    umar.deposit(200);
    cout << umar.getBalance() << "\n";

    return 0;
}
