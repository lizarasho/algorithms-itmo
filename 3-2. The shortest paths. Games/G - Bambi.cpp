#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>
#include <climits>
#include <set>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;

#define INF INT_MAX

struct edge
{
    int to;
    int w;
};

vector<vector<edge>> graph;
vector<vector<int>> num;
vector<vector<edge>> new_graph;
vector<bool> used;
vector<int> d;

int n, M;
long long t;
bool possible;

void dfs(int u, int s)
{
    if (used[num[u][s]])
        return;
    used[num[u][s]] = true;
    for (auto [v, w] : graph[u])
    {
        new_graph[num[u][s]].push_back({num[v][(s + w) % M], w});
        if (v == n - 1 && (s + w) % M == t % M)
        {
            possible = true;
            return;
        }
        dfs(v, (s + w) % M);
    }
}

void dijkstra()
{
    d.resize(n * M, INF);
    vector<bool> marked(n * M, false);
    set<pair<int, int>> relax;
    relax.insert({0, 0});
    d[0] = 0;

    while (!relax.empty())
    {
        auto [dist, u] = *(relax.begin());
        relax.erase({dist, u});
        for (auto [v, w] : new_graph[u])
        {
            if (d[v] <= d[u] + w)
                continue;
            if (d[v] != INF)
                relax.erase({d[v], v});
            d[v] = d[u] + w;
            relax.insert({d[v], v});
        }
    }
}

int main()
{
    int m;
    cin >> n >> m;
    graph.resize(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }
    cin >> t;

    if (graph[n - 1].empty())
    {
        cout << "Impossible", 0;
    }
    M = 2 * graph[n - 1][0].w;

    num.resize(n, vector<int>(M));
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < M; j++)
        {
            num[i][j] = k++;
        }
    }

    used.resize(n * M);
    new_graph.resize(n * M);
    dfs(0, 0);

    if (possible)
    {
        dijkstra();
        if (d[num[n - 1][t % M]] <= t)
        {
            cout << "Possible", 0;
        }
    }

    cout << "Impossible";
    return 0;
}