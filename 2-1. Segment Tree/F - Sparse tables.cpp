#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
vector<int> a(100001);
int st[100001][17];
int n;


void build()
{
    for (int j = 1; j <= n; j++)
        st[j][0] = a[j];

    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; (i + (1 << j) - 1) <= n; i++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int result(int l1, int r1)
{
    int l = min(l1, r1);
    int r = max(l1, r1);
    int k = (int)(log(r - l + 1) / log(2));
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}


int main()
{
    int m, x;
    cin >> n >> m >> x;
    a[1] = x;
    for (int i = 2; i <= n; i++)
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    build();

    int u, v;
    cin >> u >> v;
    int ans = result(u, v);
    for (int i = 2; i <= m; i++)
    {
        u = ((17 * u + 751 + ans + 2 * (i - 1)) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * (i - 1)) % n) + 1;
        ans = result(u, v);
    }

    cout << u << " " << v << " " << ans;
}