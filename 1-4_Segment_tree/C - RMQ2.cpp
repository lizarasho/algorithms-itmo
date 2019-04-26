#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1 << 17;
struct node
{
    long long min;
    long long add;
    bool set;
};
vector<node> s(2 * N - 1);

void push(int i)
{
    if (s[i].set)
    {
        s[2 * i + 1] = s[2 * i + 2] = { s[i].min, 0, true };
        s[i].set = false;
        return;
    }
    if (s[i].add)
    {
        s[2 * i + 1].min += s[i].add;
        s[2 * i + 2].min += s[i].add;
        s[2 * i + 1].add += (1 - s[2 * i + 1].set) * s[i].add;
        s[2 * i + 2].add += (1 - s[2 * i + 2].set) * s[i].add;
        s[i].add = 0;
        return;
    }
}

void update_add(int L, int R, int v, int l, int r, long long x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
    {
        s[v].min += x;
        if (!s[v].set)
            s[v].add += x;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update_add(L, R, 2 * v + 1, l, m, x);
    update_add(L, R, 2 * v + 2, m, r, x);
    s[v].min = min(s[2 * v + 1].min, s[2 * v + 2].min);
}

void update_set(int L, int R, int v, int l, int r, long long x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
    {
        s[v] = { x, 0, true };
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update_set(L, R, 2 * v + 1, l, m, x);
    update_set(L, R, 2 * v + 2, m, r, x);
    s[v].min = min(s[2 * v + 1].min, s[2 * v + 2].min);
}

long long result(int L, int R, int v, int l, int r)
{
    if (R <= l || r <= L)
        return LONG_LONG_MAX;
    if (l >= L && r <= R)
        return s[v].min;
    push(v);
    int m = (l + r) / 2;
    long long minl = result(L, R, 2 * v + 1, l, m);
    long long minr = result(L, R, 2 * v + 2, m, r);
    return min(minl, minr);
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
        s[i] = { t, 0, false };
    }
    for (int i = full + n - 1; i < 2 * full - 1; i++)
        s[i] = { LONG_LONG_MAX, 0, false };

    for (int i = full - 2; i >= 0; i--)
        s[i] = { min(s[2 * i + 1].min, s[2 * i + 2].min), 0, false };

    string str;
    int x1, x2;
    long long val;
    while (cin >> str)
    {
        if (str[0] == 's')
        {
            cin >> x1 >> x2 >> val;
            update_set(x1 + full - 2, x2 + 1 + full - 2, 0, full - 1, 2 * full - 1, val);
        }
        if (str[0] == 'a')
        {
            cin >> x1 >> x2 >> val;
            update_add(x1 + full - 2, x2 + 1 + full - 2, 0, full - 1, 2 * full - 1, val);
        }
        if (str[0] == 'm')
        {
            cin >> x1 >> x2;
            cout << result(x1 + full - 2, x2 + 1 + full - 2, 0, full - 1, 2 * full - 1) << endl;
        }
    }

    return 0;
}