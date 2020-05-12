#include <iostream>
#include <vector>
#include <queue>
#include <set>

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
            auto [u, v, f, c, w] = edges[e];
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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> graph((size_t) 2 * n + 2);
    vector<edge> edges;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c;
            cin >> c;
            add_edges(i, n + j, 1, c, graph, edges);
        }
    }

    int s = 2 * n;
    int t = 2 * n + 1;

    for (int i = 0; i < n; i++) {
        add_edges(s, i, 1, 0, graph, edges);
        add_edges(n + i, t, 1, 0, graph, edges);
    }

    auto cost = min_cost(s, t, graph, edges);
    cout << cost << '\n';

    for (int e = 0; e < edges.size(); e += 2) {
        auto [u, v, f, c, w] = edges[e];
        if (f != 1 || u == s || v == t) {
            continue;
        }
        cout << u + 1 << ' ' << v - n + 1 << '\n';
    }

    return 0;
}