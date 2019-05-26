#include <iostream>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    n--;

    int l = -1;
    int r = n * y + 1;

    while (r > l + 1)
    {
        int m = (r + l) / 2;
        if (m / x + m / y < n)
            l = m;
        else
            r = m;
    }

    cout << min(x, y) + r;
    return 0;
}