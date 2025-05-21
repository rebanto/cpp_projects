#include <iostream>
#include "auth.h"

using namespace std;

int main() {
    pair<User, bool> result;
    do {
        result = auth();
    } while (!result.second);

    cout << "\033[2J\033[1;1H";

    User current_user = result.first;
    cout << "Welcome, " << current_user.username << "!" << current_user.balance << endl;
}

void deposit() {
    
}

void withdraw() {

}

int main_loop() {
    int choice;

    cout << "\nACTIONS:\n1.\tDeposit\n2.\tWithdraw\n3.\tExit\nChoice:\t";
    cin >> choice;

    switch (choice)
    {
    case 1:
        deposit();
        break;
    case 2:
        withdraw();
        break;
    case 3:
        exit(0);
    default:
        cout << "\nInvalid Input.\n";
        return -1;
    }
}