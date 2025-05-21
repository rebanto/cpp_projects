#include <iostream>
#include "auth.h"
#include <windows.h>
#include <iomanip>

using namespace std;

User current_user;

void deposit()
{
    double amount;

    cout << "\033[2J" << "\033[1;1H";
    cout << "Current Balance: " << current_user.balance << endl
         << "Enter amount to deposit:\t$";
    cin >> amount;

    if (amount < 0)
    {
        cout << "\nInvalid input.";
        Sleep(2000);
        return;
    }

    current_user.balance += amount;
    cout << "\nSuccessful!" << endl;

    Sleep(2000);
}

void withdraw()
{
    double amount;

    cout << "\033[2J" << "\033[1;1H";
    cout << "Current Balance: " << current_user.balance << endl
         << "Enter amount to withdraw:\t$";
    cin >> amount;

    if (amount < 0)
    {
        cout << "\nInvalid input.";
        Sleep(2000);
        return;
    }
    else if (amount > current_user.balance)
    {
        cout << "\nNot enough funds.";
        Sleep(2000);
        return;
    }

    current_user.balance -= amount;
    cout << "\nSuccessful!" << endl;

    Sleep(2000);
}

int main_loop()
{
    int choice;

    cout << fixed << setprecision(2);
    cout << "BALANCE: $" << current_user.balance << "\nACTIONS:\n1.\tDeposit\n2.\tWithdraw\n3.\tExit\nChoice:\t";
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
        save_user(current_user.id, current_user.balance);
        exit(0);
    default:
        cout << "\nInvalid Input.\n";
        Sleep(1500);
        return -1;
    }
}

int main()
{
    pair<User, bool> result;

    cout << "\033[2J" << "\033[1;1H";

    do
    {
        result = auth();
    } while (!result.second);

    cout << "\033[2J" << "\033[1;1H";

    current_user = result.first;
    cout << "Welcome, " << current_user.username << "!" << endl;

    do
    {
        main_loop();
        cout << "\033[2J" << "\033[1;1H";
    } while (true);
}