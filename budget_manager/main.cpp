#include <iostream>
#include "auth.h"

using namespace std;

int main() {
    pair<User, bool> result;
    do {
        result = auth();
    } while (!result.second);

    User current_user = result.first;
    cout << "Welcome, " << current_user.username << "! Your user ID is " << current_user.id << "." << endl;
}