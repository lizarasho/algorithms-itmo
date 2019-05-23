#include <iostream>
#include <vector>

using namespace std;

int counter = 1;
int log_m = 0;
int m;
vector<int> d;
vector<vector<int>> dp;
vector<int> p;

void create(int v)
{
    p[counter] = counter;
    dp[counter][0] = v;
    d[counter] = 1 + d[v];

    for (int j = 1; 1 << (j - 1) < m; j++)
        dp[counter][j] = dp[dp[counter][j - 1]][j - 1];

    counter++;
}

int get_main(int x)
{
    if (p[x] != x)
        p[x] = get_main(p[x]);
    return p[x];
}

void join(int x, int y)
{
    int u = get_main(x);
    int v = get_main(y);

    if (u != v)
        p[u] = v;
}

int lca(int u, int v)
{
    if (d[v] > d[u])
        swap(u, v);

    for (int i = log_m; i >= 0; i--)
        if (d[u] - (1 << i) >= d[v])
            u = dp[u][i];

    if (u == v)
        return u;

    for (int i = log_m; i >= 0; i--)
    {
        if (dp[v][i] != dp[u][i])
        {
            v = dp[v][i];
            u = dp[u][i];
        }
    }

    return dp[u][0];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m;
    d.resize(m);
    dp.resize(m);
    p.resize(m);

    for (int j = 1; 1 << (j - 1) < m; j++)
        log_m++;

    for (int i = 0; i < m; i++)
        dp[i].resize(log_m + 1);

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int v;
            cin >> v;
            create(v - 1);
        }
        else if (c == '-')
        {
            int v;
            cin >> v;
            join(v - 1, dp[v - 1][0]);
        }
        else if (c == '?')
        {
            int u, v;
            cin >> u >> v;
            cout << get_main(lca(u - 1, v - 1)) + 1 << '\n';
        }
    }
    return 0;
}