#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;
int n;
const int N = 10000000;
vector<long long> a(N);
vector<int> b(2 * N);

int main()
{
    int x, y, k;
    cin >> n >> x >> y >> k;
    a[0] = k;
    int shift = (1 << 16) - 1;
    for (int i = 1; i < n; i++)
        a[i] = (x * a[i - 1] + y) & shift;

    int m, z, t;
    cin >> m >> z >> t >> k;
    b[0] = k;
    shift = (1 << 30) - 1;
    for (int i = 1; i < 2 * m; i++)
        b[i] = (z * b[i - 1] + t) & shift;

    for (int i = 0; i < 2 * m; i++)
    {
        b[i] %= n;
        b[i] = max(b[i], 0);
    }

    for (int i = 1; i < n; i++)
        a[i] += a[i - 1];

    long long sum = 0;
    int l, r;
    for (int i = 0; i < m; i++)
    {
        l = min(b[2 * i], b[2 * i + 1]);
        r = max(b[2 * i], b[2 * i + 1]);
        sum += l > 0 ? a[r] - a[l - 1] : a[r];
    }

    cout << sum;
    return 0;
}