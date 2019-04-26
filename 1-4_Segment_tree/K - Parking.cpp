#include <iostream>
#include <vector>

using namespace std;
const int N = 1 << 17;
vector<int> s(2 * N - 1);
int full, n;

int sum(int L, int R, int v, int l, int r)
{
    if (R <= l || r <= L)
        return 0;
    if (l >= L && r <= R)
        return s[v];
    int m = (l + r) / 2;
    int sl = sum(L, R, 2 * v + 1, l, m);
    int sr = sum(L, R, 2 * v + 2, m, r);
    return sl + sr;
}

int find(int k)
{
    int len = full / 2;
    int v = 0;
    while (v < full - 1)
    {
        int left_zeroes = len - s[2 * v + 1];
        if (left_zeroes >= k)
            v = 2 * v + 1;
        else
        {
            v = 2 * v + 2;
            k -= left_zeroes;
        }
        len /= 2;
    }
    return v;
}

void fill(int i, int x)
{
    while (i != 0)
    {
        s[i] = (x == 1) ? s[i] + 1 : s[i] - 1;
        i = (i - 1) / 2;
    }
    s[i] = (x == 1) ? s[i] + 1 : s[i] - 1;
}

int set(int i)
{
    if (s[i] == 0)
    {
        fill(i, 1);
        return i - full + 2;
    }
    int end = sum(i + 1, full + n - 1, 0, full - 1, 2 * full - 1);
    if (end == full + n - i - 2)
    {
        int temp = find(1);
        fill(temp, 1);
        return temp - full + 2;
    } else {
        int begin = sum(full - 1, i + 1, 0, full - 1, 2 * full - 1);
        int pos = i + 1 - full + 1;
        int temp = find(pos - begin + 1);
        fill(temp, 1);
        return temp - full + 2;
    }
}

int main()
{
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);

    int m;
    cin >> n >> m;

    full = 1;
    while (full < n)
        full *= 2;

    for (int i = full - 1; i < full + n - 1; i++)
        s[i] = 0;
    for (int i = full + n - 1; i < 2 * full - 1; i++)
        s[i] = 1;

    for (int i = full - 2; i >= 0; i--)
        s[i] = s[2 * i + 1] + s[2 * i + 2];

    string str;
    int pos;
    for (int i = 0; i < m; i++)
    {
        cin >> str >> pos;
        if (str[1] == 'n')
            cout << set(pos + full - 2) << endl;
        else
            fill(pos + full - 2, 0);
    }

    return 0;
}