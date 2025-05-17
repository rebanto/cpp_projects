#include <iostream>

using namespace std;

void swapNums(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

int main() {
    int x = 3;
    int y = 5;

    cout << x << ' ' << y << "\n";

    swapNums(x, y);

    cout << x << ' ' << y << "\n";
    return 0;
}

/*
POINTER EQUIVALENT:

#include <iostream>
#include <string>
#include <iterator>

using namespace std;

void swapNums(int* x, int* y) {
    int z = *x;
    *x = *y;
    *y = z;
}

int main() {
    int x = 3;
    int y = 5;

    cout << x << ' ' << y << "\n";

    swapNums(&x, &y);

    cout << x << ' ' << y << "\n";
    return 0;
}

*/