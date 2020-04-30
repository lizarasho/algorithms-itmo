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

void add_edges(int u, int v, int c = 1)
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

double max_flow()
{
    double ans = 0;
    while (bfs())
    {
        fill(p.begin(), p.end(), 0);
        while (int cur_flow = dfs(s, INF)) {
            ans += cur_flow;
        }
    }
    return ans;
}

void create_path(int u, vector<int> & path)
{
    path.push_back(u);
    if (u == t) {
        return;
    }
    for (auto e : graph[u]) {
        auto [_, v, f, c] = edges[e];
        if (f != c || c == 0) {
            continue;
        }
        edges[e].f = edges[e + 1].f = 0;
        create_path(v, path);
        break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    s--; t--;

    graph.resize((size_t)n);
    d.resize((size_t)n);
    p.resize((size_t)n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edges(u - 1, v - 1);
    }

    double res = max_flow();

    if (res < 2) {
        cout << "NO";
        return 0;
    }

    vector<int> fpath;
    vector<int> spath;

    create_path(s, fpath);
    create_path(s, spath);

    cout << "YES" << '\n';
    for (int e : fpath) {
        cout << e + 1 << ' ';
    }
    cout << '\n';
    for (int e : spath) {
        cout << e + 1 << ' ';
    }

    return 0;
}