#include <iostream>
#include <vector>

using namespace std;
int log_n;
vector<int> p;
vector<int> d;
vector<vector<int>> dp;

int lca(int u, int v)
{
    if (d[v] > d[u])
        swap(u, v);

    for (int i = log_n; i >= 0; i--)
        if (d[u] - (1 << i) >= d[v])
            u = dp[u][i];

    if (u == v)
        return u;

    for (int i = log_n; i >= 0; i--)
    {
        if (dp[v][i] != dp[u][i])
        {
            v = dp[v][i];
            u = dp[u][i];
        }
    }
    return p[v];
}

int main()
{
    int n;
    cin >> n;
    p.resize(n);
    d.resize(n);
    dp.resize(n);

    p[0] = d[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int x;
        cin >> x;
        p[i] = x - 1;
        d[i] = d[x - 1] + 1;
    }

    for (int i = 0; i < n; i++)
        dp[i].push_back(p[i]);

    log_n = 0;
    for (int j = 1; 1 << (j - 1) < n; j++)
    {
        for (int i = 0; i < n; i++)
            dp[i].push_back(dp[dp[i][j - 1]][j - 1]);
        log_n++;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << lca(u - 1, v - 1) + 1 << endl;
    }
    return 0;
}