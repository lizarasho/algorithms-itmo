#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

struct edge
{
    int to;
    int num;

    friend bool operator<  (const edge& e1, const edge& e2)
    {
        return e1.to<e2.to || (e2.to >= e1.to && e1.num < e2.num);
    }
};

vector<vector<edge>> graph;
vector<vector<int>> new_graph;
vector<bool> used;
vector<int> color;
vector<int> t_in;
vector<int> d;
set<pair<int, edge>> bridges;
int t = 0;

void dfs(int u, int p)
{
    t_in[u] = d[u] = t++;
    used[u] = true;
    for (auto [v, num] : graph[u])
    {
        if (v == p)
        {
            continue;
        }
        if (used[v])
        {
            d[u] = min(d[u], t_in[v]);
            continue;
        }
        dfs(v, u);
        d[u] = min(d[u], d[v]);
        if (d[v] > t_in[u])
        {
            bridges.insert({u, {v, num}});
            bridges.insert({v, {u, num}});
        }
    }
}

void paint(int u, int c)
{
    if (color[u]) return;
    color[u] = c;
    for (auto v : new_graph[u])
    {
        paint(v, c);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    size_t n, m;
    cin >> n >> m;
    graph.resize(n);
    new_graph.resize(n);
    used.resize(n);
    color.resize(n);
    t_in.resize(n);
    d.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back({v - 1, i});
        graph[v - 1].push_back({u - 1, i});
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            dfs(i, -1);
        }
    }

    for (int u = 0; u < n; u++)
    {
        for (auto [v, num] : graph[u])
        {
            if (!bridges.count({u, {v, num}}))
            {
                new_graph[u].push_back(v);
            }
        }
    }


    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (color[i] == 0)
        {
            cnt++;
            paint(i, cnt);
        }
    }

    cout << cnt << '\n';
    for (int c : color)
    {
        cout << c << ' ';
    }

    return 0;
}