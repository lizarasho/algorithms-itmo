#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <algorithm>

using namespace std;

#define INF LONG_LONG_MAX

struct edge
{
    int to;
    long long w;
};

vector<vector<edge>> graph;
vector<long long> d;

void dijkstra(int s)
{
    d.clear();
    d.resize(graph.size(), INF);
    vector<bool> marked(graph.size(), false);
    set<pair<long long, int>> relax;
    relax.insert({0, s});
    d[s] = 0;

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
}


int main()
{
    size_t n;
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
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    c--;

    dijkstra(a);
    long long ab = d[b];
    long long ac = d[c];

    dijkstra(b);
    long long bc = d[c];

    vector<long long> paths {ab, ac, bc};
    sort(paths.begin(), paths.end());
    cout << (paths[1] == INF ? -1 : paths[0] + paths[1]);

    return 0;
}