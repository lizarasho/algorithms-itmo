#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;

int const INF = INT_MAX;

struct vert
{
    int l;
    int h;
};

struct edge
{
    vert u;
    vert v;
    int f;
    int c;
};

int n, m;
vert s, t;

vector<edge> edges;
vector<vector<vector<int>>> graph;
vector<vector<int>> d, p;
vector<vector<char>> table;


void add_edges(vert u, vert v, int c = 1)
{
    graph[u.l][u.h].push_back((int) edges.size());
    edges.push_back({u, v, 0, c});
    graph[v.l][v.h].push_back((int) edges.size());
    edges.push_back({v, u, 0, 0});
}

bool bfs()
{
    for (auto &i : d) {
        for (int &j : i) {
            j = -1;
        };
    }
    d[s.l][s.h] = 0;

    queue<vert> q;
    q.push(s);

    while (!q.empty()) {
        vert u = q.front();
        q.pop();

        for (auto e : graph[u.l][u.h]) {
            auto[_, v, f, c] = edges[e];
            if (f < c && d[v.l][v.h] == -1) {
                d[v.l][v.h] = d[u.l][u.h] + 1;
                q.push(v);
            }
        }
    }
    return d[t.l][t.h] != -1;
}

int dfs(vert u, int min_c)
{
    if (((u.l == t.l) && (u.h == t.h)) || min_c == 0) {
        return min_c;
    }
    for (; p[u.l][u.h] < graph[u.l][u.h].size(); p[u.l][u.h]++) {
        int e = graph[u.l][u.h][p[u.l][u.h]];
        auto [_, v, f, c] = edges[e];
        if (d[v.l][v.h] != d[u.l][u.h] + 1) {
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

void reconctruct(vert u)
{
    if ((u.l == t.l) && (u.h == t.h)) {
        return;
    }
    for (auto e : graph[u.l][u.h]) {
        auto [_, v, f, c] = edges[e];
        if (c == 0 || f == 0) {
            continue;
        }
        if (c == INF) {
            reconctruct(v);
        } else {
            table[u.l][u.h / 2] = '+';
            edges[e].f = edges[e + 1].f = 0;
        }
    }
}

double max_flow()
{
    double ans = 0;
    while (bfs())
    {
        for (auto &i : p) {
            for (int &j : i) {
                j = 0;
            };
        }
        while (int cur_flow = dfs(s, INF)) {
            ans += cur_flow;
        }
    }
    return ans;
}

void check_reachable(vector<vector<bool>> & reachable, vert u) {
    if (reachable[u.l][u.h]) return;
    reachable[u.l][u.h] = true;
    for (int e : graph[u.l][u.h]) {
        auto [_, v, f, c] = edges[e];
        if (f != c) {
            check_reachable(reachable, v);
        }
    }
}

double min_cut()
{
    double ans = max_flow();

    vector<vector<bool>> reachable((size_t) m, vector<bool>((size_t) 2 * n, false));
    check_reachable(reachable, s);

    for (int e = 0; e < edges.size(); e += 2) {
        vert u = edges[e].u;
        vert v = edges[e].v;
        if (reachable[u.l][u.h] == reachable[v.l][v.h] || edges[e].f != 1) {
            continue;
        }
        table[u.l][u.h / 2] = '+';
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;

    graph.resize((size_t) m, vector<vector<int>>((size_t) 2 * n));
    d.resize((size_t) m, vector<int>((size_t) 2 * n));
    p.resize((size_t) m, vector<int>((size_t) 2 * n));

    table.resize((size_t) m, vector<char> ((size_t) n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            table[i][j] = c;
            if (c == '#') {
                continue;
            }
            if (c == '-') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, INF);
                continue;
            }
            if (c == '.') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, 1);
                continue;
            }
            if (c == 'A') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, INF);
                s = {i, 2 * j};
                continue;
            }
            if (c == 'B') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, INF);
                t = {i, 2 * j + 1};
                continue;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (table[i][j] == '#') {
                continue;
            }
            if (j + 1 < n && table[i][j + 1] != '#') {
                add_edges({i, 2 * j + 1}, {i, 2 * (j + 1)}, INF);
                add_edges({i, 2 * (j + 1) + 1}, {i, 2 * j}, INF);
            }
            if (i + 1 < m && table[i + 1][j] != '#') {
                add_edges({i, 2 * j + 1}, {i + 1, 2 * j}, INF);
                add_edges({i + 1, 2 * j + 1}, {i, 2 * j}, INF);
            }
        }
    }

    double ans = min_cut();
    if (ans >= INF) {
        cout << -1;
        return 0;
    }
    cout << ans << '\n';

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << table[i][j];
        }
        cout << '\n';
    }

    return 0;
}