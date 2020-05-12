#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <iomanip>
#include <algorithm>
#include <climits>

using namespace std;

long long const INF = INT_MAX;

struct edge
{
    int u;
    int v;
    int f;
    int c;
    long long w;
    edge(int u, int v, int c, long long w) : u(u), v(v), f(0), c(c), w(w) {};
};

bool exists_path(int s, int t, vector<vector<int>> &graph, vector<edge> &edges, vector<int> &p)
{
    auto n = graph.size();
    vector<long long> d(n, INF);
    set<pair<int, long long>> relax;
    relax.insert({s, 0});
    d[s] = 0;

    while (!relax.empty()) {
        auto [u, dist] = *(relax.begin());
        relax.erase({u, dist});
        for (auto e : graph[u]) {
            auto [_, v, f, c, w] = edges[e];
            if (d[v] <= d[u] + w || c - f == 0) {
                continue;
            }
            if (d[v] != INF) {
                relax.erase({v, d[v]});
            }
            d[v] = d[u] + w;
            p[v] = e;
            relax.insert({v, d[v]});
        }
    }

    return d[t] != INF;
}

int get_path_min(int s, int v, vector<edge> &edges, vector<int> &p)
{
    if (v == s) {
        return INF;
    }
    auto [u, _, f, c, w] = edges[p[v]];
    return min(c - f, get_path_min(s, u, edges, p));
}

void add_edges(int u, int v, int c, long long s, vector<vector<int>> &graph, vector<edge> &edges)
{
    graph[u].push_back((int)edges.size());
    edges.emplace_back(u, v, c, s);
    graph[v].push_back((int)edges.size());
    edges.emplace_back(v, u, 0, -s);
}

int get_reverse(int e)
{
    return e + (e % 2 == 0 ? 1 : -1);
}

long long min_cost(int s, int t, vector<vector<int>> &graph, vector<edge> &edges)
{
    vector<int> p(graph.size());
    long long result = 0;

    while (exists_path(s, t, graph, edges, p)) {
        long long cur_flow = get_path_min(s, t, edges, p);

        for (int cur = t; cur != s; cur = edges[p[cur]].u) {
            auto e = p[cur];
            edges[e].f += cur_flow;
            edges[get_reverse(e)].f -= cur_flow;
            result += cur_flow * edges[e].w;
        }
    }
    return result;
}

void floyd(vector<vector<long long>> &d)
{
    auto n = d.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] == INF || d[k][j] == INF) {
                    continue;
                }
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a((size_t) n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<long long>> d((size_t) n, vector<long long> ((size_t) n, INF));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u - 1][v - 1] = w;
    }

    floyd(d);

    vector<vector<int>> graph((size_t) 2 * n + 2);
    vector<edge> edges;

    for (int i = 0; i < n; i++) {
        add_edges(i, n + i, 1, a[i], graph, edges);
        for (int j = 0; j < n; j++) {
            if (i != j && d[i][j] != INF) {
                add_edges(i, j + n, 1, d[i][j], graph, edges);
            }
        }
    }

    int s = 2 * n;
    int t = 2 * n + 1;

    for (int i = 0; i < n; i++) {
        add_edges(s, i, 1, 0, graph, edges);
        add_edges(i + n, t, 1, 0, graph, edges);
    }

    cout << min_cost(s, t, graph, edges);

    return 0;
}