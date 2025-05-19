#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename;

    cout << "Filename: ";
    getline(cin, filename);

    cout << filename;
}