#include <iostream>
#include <string>

using namespace std;

int main() {
    struct Contact {
        string first_name, last_name, email, phone_number;
        int age;
    };

    Contact contact1;

    cout << "Enter first name, last name, email, age, and phone number for new contact: ";
    cin >> contact1.first_name >> contact1.last_name >> contact1.email >> contact1.age >> contact1.phone_number;

    cout << "\033[2J" << "\033[1;1H";
    cout << "Name: " << contact1.first_name << " " << contact1.last_name << "\nEmail: " << contact1.email << "\nAge: " << contact1.age << "\nPhone number: " << contact1.phone_number;
    return 0;
}