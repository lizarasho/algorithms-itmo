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

    vector<vector<int>> graph(8);
    vector<edge> edges;

    int s = 0;
    int t = 7;

    int r1, s1, t1;
    int r2, s2, t2;

    cin >> r1 >> s1 >> t1;
    cin >> r2 >> s2 >> t2;

    // s <-> 0
    // r1 <-> 1, s1 <-> 2, t1 <-> 3
    // r2 <-> 4, s2 <-> 5, t2 <-> 6
    // t <-> 7

    add_edges(1, 4, INF, 0, graph, edges);
    add_edges(1, 5, INF, 1, graph, edges);
    add_edges(1, 6, INF, 0, graph, edges);

    add_edges(2, 4, INF, 0, graph, edges);
    add_edges(2, 5, INF, 0, graph, edges);
    add_edges(2, 6, INF, 1, graph, edges);

    add_edges(3, 4, INF, 1, graph, edges);
    add_edges(3, 5, INF, 0, graph, edges);
    add_edges(3, 6, INF, 0, graph, edges);

    add_edges(0, 1, r1, 0, graph, edges);
    add_edges(0, 2, s1, 0, graph, edges);
    add_edges(0, 3, t1, 0, graph, edges);

    add_edges(4, 7, r2, 0, graph, edges);
    add_edges(5, 7, s2, 0, graph, edges);
    add_edges(6, 7, t2, 0, graph, edges);

    cout << min_cost(s, t, graph, edges);

    return 0;
}