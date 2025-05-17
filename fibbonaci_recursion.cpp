#include <iostream>

using namespace std;

int fibbonaci(int x, int y, int count = 10) {
    if (count == 0) return 0;
    
    cout << x + y << "\n";
    return fibbonaci(y, x + y, count - 1);
};

int main() {
    int x = 0, y = 1;

    fibbonaci(x, y);

    return 0;
}