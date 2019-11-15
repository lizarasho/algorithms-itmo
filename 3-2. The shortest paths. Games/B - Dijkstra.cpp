#include <iostream>
#include <vector>
#include <climits>
#include <set>

using namespace std;

#define INF LONG_LONG_MAX

struct edge
{
    int to;
    int w;
};

int main()
{
    size_t n;
    int m;
    cin >> n >> m;
    vector<vector<edge>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }

    vector<bool> marked(n, false);
    vector<long long> d(n, INF);
    set<pair<long long, int>> relax;
    relax.insert({0, 0});
    d[0] = 0;

    while (!relax.empty())
    {
        auto [dist, u] = *(relax.begin());
        relax.erase({dist, u});
        for (auto [v, w] : graph[u])
        {
            if (d[v] <= d[u] + w)
                continue;
            if (d[v] != INF)
                relax.erase({d[v], v});
            d[v] = d[u] + w;
            relax.insert({d[v], v});
        }
    }

    for (auto dist : d)
        cout << dist << ' ';

    return 0;
}