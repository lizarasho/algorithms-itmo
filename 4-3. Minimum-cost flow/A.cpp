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
    vector<int> d(n, INF);
    set<pair<int, int>> relax;
    relax.insert({s, 0});
    d[s] = 0;

    while (!relax.empty()) {
        auto [dist, u] = *(relax.begin());
        relax.erase({dist, u});
        for (auto e : graph[u]) {
            auto [u, v, f, c, w] = edges[e];
            if (d[v] <= d[u] + w || c - f == 0) {
                continue;
            }
            if (d[v] != INF) {
                relax.erase({d[v], v});
            }
            d[v] = d[u] + w;
            p[v] = e;
            relax.insert({d[v], v});
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

    size_t n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, c, s;
        cin >> u >> v >> c >> s;
        add_edges(u - 1, v - 1, c, s, graph, edges);
    }

    cout << min_cost(0, (int) (n - 1), graph, edges);

    return 0;
}