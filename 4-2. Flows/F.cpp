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

int n;
int s, t;

vector<edge> edges;
vector<vector<int>> graph;
vector<int> d, p;
vector<vector<char>> table;


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

double max_flow()
{
    double ans = 0;
    while (bfs()) {
        fill(p.begin(), p.end(), 0);
        while (int cur_flow = dfs(s, INF)) {
            ans += cur_flow;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    graph.resize((size_t) n + 2);
    d.resize((size_t) n + 2);
    p.resize((size_t) n + 2);

    table.resize((size_t) n + 2, vector<char> ((size_t) n + 2));

    s = n;
    t = n + 1;

    vector<int> score((size_t) n, 0);
    vector<int> max_score((size_t) n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            table[i][j] = c;
            switch (c) {
                case 'W' : {
                    score[i] += 3;
                    break;
                }
                case 'l' : {
                    score[i] += 1;
                    break;
                }
                case 'w' : {
                    score[i] += 2;
                    break;
                }
                case '.' : {
                    if (i < j) {
                        add_edges(i, j, 3);
                        max_score[i] += 3;
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        add_edges(s, i, max_score[i]);
        add_edges(i, t, k - score[i]);
    }

    max_flow();

    for (int i = 0; i < n; i++) {
        for (auto e : graph[i]) {
            auto [u, j, f, c] = edges[e];
            if (table[i][j] == '.' && i < j && j != s && j != t)
                switch (f) {
                    case 0 : {
                        table[i][j] = 'W';
                        table[j][i] = 'L';
                        break;
                    }
                    case 1 : {
                        table[i][j] = 'w';
                        table[j][i] = 'l';
                        break;
                    }
                    case 2 : {
                        table[i][j] = 'l';
                        table[j][i] = 'w';
                        break;
                    }
                    case 3 : {
                        table[i][j] = 'L';
                        table[j][i] = 'W';
                        break;
                    }
                    default: {
                        break;
                    }
                }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << table[i][j];
        }
        cout << '\n';
    }

    return 0;
}