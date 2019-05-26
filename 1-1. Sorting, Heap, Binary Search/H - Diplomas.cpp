#include <iostream>

using namespace std;

int main()
{
    long long w, h, n;
    cin >> w >> h >> n;

    long long l = min(w, h);
    long long r = max(w, h) * n;

    while (r - l > 1)
    {
        long long m = (l + r) / 2;
        long long k = (m / w) * (m / h);
        if (k < n)
            l = m;
        else
            r = m;
    }

    cout << r;
    return 0;
}