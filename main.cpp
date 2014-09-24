#include <iostream>
#include "Saving.cpp"

using namespace std;

int main() {

    Saving umar(100);
    cout << umar.getBalance() << "\n";

    umar.withdraw(80);
    cout << umar.getBalance() << "\n";

    umar.deposit(300);
    cout << umar.getBalance() << "\n";

    return 0;
}