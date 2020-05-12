#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;

int const INF = INT_MAX;

struct edge
{
    int u;
    int v;
    int f;
    int c;
    int w;
    edge(int u, int v, int c, int w) : u(u), v(v), f(0), c(c), w(w) {};
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

void add_edges(int u, int v, int c, int s, vector<vector<int>> &graph, vector<edge> &edges)
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

long long min_cost(int s, int t, int k, vector<vector<int>> &graph, vector<edge> &edges)
{
    vector<int> p(graph.size());
    long long result = 0;

    for (int i = 0; i < k; i++) {
        if (!exists_path(s, t, graph, edges, p)) {
            return -1;
        }
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

void create_path(int u, int t, vector<int> & path, vector<vector<int>> &graph, vector<edge> &edges)
{
    if (u == t) {
        return;
    }
    for (auto e : graph[u]) {
        auto [_, v, f, c, w] = edges[e];
        if (f != c || c == 0) {
            continue;
        }
        edges[e].f = edges[e + 1].f = 0;
        path.push_back(e / 4);
        create_path(v, t, path, graph, edges);
        break;
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> graph((size_t) n);
    vector<edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edges(u - 1, v - 1, 1, w, graph, edges);
        add_edges(v - 1, u - 1, 1, w, graph, edges);
    }

    int s = 0;
    int t = n - 1;

    auto cost = min_cost(s, t, k, graph, edges);

    if (cost == -1) {
        cout << -1;
        return 0;
    }

    cout << fixed << setprecision(5) << (double)cost / k << '\n';

    for (int i = 0; i < k; i++) {
        vector<int> path;
        create_path(s, t, path, graph, edges);
        cout << path.size() << ' ';
        for (auto & e : path) {
            cout << e + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}