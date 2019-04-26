#include <iostream>
#include <vector>

using namespace std;
const int N = 1 << 19;
vector<long long> s(2 * N - 1);

void set (int i, long long x, int v, int l, int r)
{
    if (r - l == 1)
    {
        s[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (i < m)
        set(i, x, 2 * v + 1, l, m);
    else
        set(i, x, 2 * v+2, m, r);
    s[v] = s[2 * v + 1] + s[2 * v + 2];
}

long long sum(int L, int R, int v, int l, int r)
{
    if (R <= l || r <= L)
        return 0;
    if (l >= L && r <= R)
        return s[v];
    int m = (l + r) / 2;
    long long sl = sum(L, R, 2 * v + 1, l, m);
    long long sr = sum(L, R, 2 * v + 2, m, r);
    return sl + sr;
}


int main()
{
    int n;
    cin >> n;

    int full = 1;
    while (full < n)
        full *= 2;

    long long t;
    for (int i = full - 1; i < full + n - 1; i++)
    {
        cin >> t;
        s[i] = t;
    }
    for (int i = full + n - 1; i < 2 * full - 1; i++)
        s[i] = 0;

    for (int i = full - 2; i >= 0; i--)
        s[i] = s[2 * i + 1] + s[2 * i + 2];

    string s;
    int x1, x2;
    int x;
    long long val;
    while (cin >> s)
    {
        if (s[1] == 'u')
        {
            cin >> x1 >> x2;
            cout << sum(x1 + full - 2, x2 + 1 + full - 2, 0, full - 1, 2 * full - 1) << endl;
        } else
        {
            cin >> x >> val;
            set(x + full - 2, val, 0, full - 1, 2 * full - 1);
        }
    }

    return 0;
}