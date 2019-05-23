#include <iostream>
#include <vector>

using namespace std;

int log_n;
vector<int> d;
vector<vector<int>> dp;
vector<vector<int>> path_min;

int minimum(int u, int v)
{
    if (d[v] > d[u])
        swap(u, v);

    int ans = INT_MAX;

    for (int i = log_n; i >= 0; i--)
    {
        if (d[u] - (1 << i) >= d[v])
        {
            ans = min(ans, path_min[u][i]);
            u = dp[u][i];
        }
    }

    if (u == v)
        return ans;

    for (int i = log_n; i >= 0; i--)
    {
        if (dp[v][i] != dp[u][i])
        {
            ans = min(min(path_min[v][i], path_min[u][i]), ans);
            v = dp[v][i];
            u = dp[u][i];
        }
    }

    return min(min(path_min[v][0], path_min[u][0]), ans);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);

    int n;
    cin >> n;
    d.resize(n);
    dp.resize(n);
    path_min.resize(n);

    log_n = 0;
    for (int j = 1; 1 << (j - 1) < n; j++)
        log_n++;
    for (int i = 0; i < n; i++)
    {
        path_min[i].resize(log_n + 1);
        dp[i].resize(log_n + 1);
    }

    dp[0][0] = 0;
    path_min[0][0] = INT_MAX;

    for (int i = 1; i < n; i++)
    {
        int x, c;
        cin >> x >> c;
        dp[i][0] = x - 1;
        d[i] = d[x - 1] + 1;
        path_min[i][0] = c;
    }

    for (int j = 1; 1 << (j - 1) < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            path_min[i][j] = min(path_min[i][j - 1], path_min[dp[i][j - 1]][j - 1]);
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << minimum(u - 1, v - 1) << '\n';
    }
    return 0;
}