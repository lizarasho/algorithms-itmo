#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;
const int N = 1 << 17;
struct query
{
    int l, r;
    long long res;
};

bool cmp(query a, query b)
{
    return a.res < b.res;
}

vector<query> arr;
vector<long long> tree(2 * N - 1);
int full;

void update_set(int L, int R, int v, int l, int r, long long x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
    {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    update_set(L, R, 2 * v + 1, l, m, x);
    update_set(L, R, 2 * v + 2, m, r, x);
}

long long result(int L, int R, int v, int l, int r)
{
    if (R <= l || r <= L)
        return LONG_LONG_MAX;
    if (l >= L && r <= R)
        return tree[v];
    int m = (l + r) / 2;
    long long minl = result(L, R, 2 * v + 1, l, m);
    long long minr = result(L, R, 2 * v + 2, m, r);
    return min(minl, minr);
}

void check(int v)
{
    if (tree[v] == LONG_LONG_MAX)
        tree[v] = tree[(v - 1) / 2];
    if (tree[v] < tree[(v - 1) / 2])
        tree[v]  = tree[(v - 1) / 2];
}

void build(int v)
{
    if (v >= full - 1)
        return;
    if (tree[v] != LONG_LONG_MAX)
    {
        check(2 * v + 1);
        check(2 * v + 2);
    }
    build(2 * v + 1);
    build (2 * v + 2);
}


int main()
{
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    full = 1;
    while (full < n)
        full *= 2;
    for (int i = 0; i < 2 * full - 1; i++)
        tree[i] = LONG_LONG_MAX;

    int x1, x2;
    long long val;
    for (int i = 0; i < m; i++)
    {
        cin >> x1 >> x2 >> val;
        arr.push_back({ x1, x2, val });
    }
    sort(arr.begin(), arr.end(), cmp);

    for (int i = 0; i < m; i++)
        update_set(arr[i].l + full - 2, arr[i].r + full - 1, 0, full - 1, 2 * full - 1, arr[i].res);

    build(0);

    for (int i = full - 2; i >= 0; i--)
        tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);

    bool can = true;
    for (int i = 0; i < m && can; i++)
    {
        val = result(arr[i].l + full - 2, arr[i].r + full - 1, 0, full - 1, 2 * full - 1);
        if (val != arr[i].res)
            can = false;
    }

    if (can)
    {
        cout << "consistent" << endl;
        for (int i = full - 1; i < full + n - 1; i++)
            if (tree[i] == LONG_LONG_MAX)
                cout << INT_MAX << " ";
            else
                cout << tree[i] << " ";
    } else
        cout << "inconsistent";

    return 0;
}