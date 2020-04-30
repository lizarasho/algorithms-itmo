#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;

int const INF = INT_MAX;

struct edge
{
    int u;
    int v;
    int f;
    int c;
};

int n, m;
int s, t;
vector<edge> edges;
vector<vector<int>> graph;
vector<int> d, p;


void add_edges(int u, int v, int c)
{
    graph[u].push_back((int)edges.size());
    edges.push_back({u, v, 0, c});
    graph[v].push_back((int)edges.size());
    edges.push_back({v, u, 0, 0});
}

bool bfs()
{
    fill(d.begin(), d.end(), -1);
    d[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int e : graph[u]) {
            auto [_, v, f, c] = edges[e];
            if (f < c && d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[t] != -1;
}

int dfs(int u, int min_c)
{
    if (u == t || min_c == 0) {
        return min_c;
    }
    for (; p[u] < graph[u].size(); p[u]++) {
        int e = graph[u][p[u]];
        auto [_, v, f, c] = edges[e];
        if (d[v] != d[u] + 1) {
            continue;
        }

        int pushed = dfs(v, min(min_c, c - f));
        if (pushed) {
            edges[e].f += pushed;
            edges[e ^ 1].f -= pushed;
            return pushed;
        }
    }
    return 0;
}

long long max_flow()
{
    long long ans = 0;
    while (bfs())
    {
        fill(p.begin(), p.end(), 0);
        while (int cur_flow = dfs(s, INF)) {
            ans += cur_flow;
        }
    }
    return ans;
}

void check_reachable(vector<bool> & reachable, int u) {
    if (reachable[u]) return;
    reachable[u] = true;
    for (int e : graph[u]) {
        auto [_, v, f, c] = edges[e];
        if (f != c) {
            check_reachable(reachable, v);
        }
    }
}

long long min_cut(vector<int>& res)
{
    long long ans = max_flow();

    vector<bool> reachable((size_t) n, false);
    check_reachable(reachable, s);

    for (int e = 0; e < edges.size(); e += 4) {
        auto [u, v, f, c] = edges[e];
        if (reachable[u] == reachable[v]) {
            continue;
        }
        res.push_back(e / 4);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    cin >> n >> m;
    graph.resize((size_t)n);
    d.resize((size_t)n);
    p.resize((size_t)n);

    s = 0;
    t = n - 1;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        add_edges(u, v, c);
        add_edges(v, u, c);
    }

    vector<int> res;
    long long cut = min_cut(res);
    cout << res.size() << ' ' << cut << '\n';
    for (auto e : res) {
        cout << e + 1 << ' ';
    }

    return 0;
}