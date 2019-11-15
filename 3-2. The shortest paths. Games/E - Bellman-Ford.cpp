#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF LONG_LONG_MAX

struct edge
{
    int v;
    long long w;
};
vector<vector<edge>> graph;
vector<bool> used;

void dfs(int v)
{
    if (used[v])
        return;
    used[v] = true;
    for (auto [u, w] : graph[v])
        dfs(u);
}

int main()
{
    size_t n, m;
    int s;
    cin >> n >> m >> s;
    graph.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
    }

    vector<long long> d(n, INF);
    d[s - 1] = 0;

    for (int i = 0; i < n; i++)
    {
        bool ok = true;
        for (int u = 0; u < n; u++)
        {
            for (auto [v, w] : graph[u])
            {
                if (d[u] < INF && d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    ok = false;
                }
            }
        }
        if (ok) break;
    }

    used.resize(n);
    for (int u = 0; u < n; u++)
    {
        for (auto [v, w] : graph[u])
        {
            if (d[u] < INF && d[v] > d[u] + w && !used[u])
            {
                dfs(u);
            }
        }
    }

    for (int u = 0; u < n; u++)
    {
        if (d[u] == INF)
        {
            cout << "*\n";
            continue;
        }
        if (used[u])
        {
            cout << "-\n";
            continue;
        }
        cout << d[u] << '\n';
    }

    return 0;
}