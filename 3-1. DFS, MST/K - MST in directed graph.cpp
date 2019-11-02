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
    int w;
};

vector<vector<edge>> origin_graph;
int visited = 0;

void dfs1(int v, vector<bool> &used, vector<vector<edge>> &graph2)
{
    if (used[v])
        return;
    used[v] = true;
    visited++;
    for (auto [u, w] : graph2[v])
        dfs1(u, used, graph2);
}

void dfs2(int v, vector<bool> &used, vector<vector<int>> &graph)
{
    if (used[v])
        return;
    used[v] = true;
    visited++;
    for (int u : graph[v])
        dfs2(u, used, graph);
}

void dfs3(int v, vector<int> &p, vector<bool> &used, vector<vector<int>> &out)
{
    if (used[v])
        return;
    used[v] = true;
    for (int u : out[v])
        dfs3(u, p, used, out);
    p.push_back(v);
}

void dfs4(int v, int c, vector<int> &comp, vector<vector<int>> &in)
{
    if (comp[v] != -1)
        return;
    comp[v] = c;
    for (int u : in[v])
        dfs4(u, c, comp, in);
}

pair<vector<int>, int> condense(vector<vector<int>> &graph)
{
    auto n = graph.size();
    vector<vector<int>> in(n);
    vector<int> comp(n, -1);
    vector<bool> used(n, false);
    for (int u = 0; u < n; u++)
    {
        for (auto v : graph[u])
        {
            in[v].push_back(u);
        }
    }
    vector<int> p;
    for (int i = 0; i < n; i++)
    {
        dfs3(i, p, used, graph);
    }
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int v = p[i];
        if (comp[v] != -1)
            continue;
        dfs4(v, cnt, comp, in);
        cnt++;
    }
    return {comp, cnt};
}

long long find_MST(vector<vector<edge>> graph, int root)
{
    auto n = graph.size();
    long long res = 0;

    vector<int> min_edge(n, INT_MAX);
    for (auto &vec : graph)
    {
        for (auto [to, w] : vec)
        {
            min_edge[to] = min(w, min_edge[to]);
        }
    }

    for (int v = 0; v < n; v++)
    {
        if (v == root)
            continue;
        res += min_edge[v];
    }
    vector<vector<int>> zero_graph(n);
    for (int u = 0; u < n; u++)
    {
        for (auto [v, w] : graph[u])
        {
            if (w == min_edge[v])
            {
                zero_graph[u].push_back(v);
            }
        }
    }

    vector<bool> used(n, false);
    visited = 0;
    dfs2(root, used, zero_graph);
    if (visited == n)
        return res;

    auto [new_comp, cnt] = condense(zero_graph);
    vector<vector<edge>> new_graph(cnt);
    for (int u = 0; u < n; u++)
    {
        for (auto [v, w] : graph[u])
        {
            if (new_comp[u] == new_comp[v])
                continue;
            new_graph[new_comp[u]].push_back({new_comp[v], w - min_edge[v]});
        }
    }
    res += find_MST(new_graph, new_comp[root]);
    return res;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    int n, m;
    cin >> n >> m;
    origin_graph.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        origin_graph[u - 1].push_back({v - 1, c});
    }

    vector<bool> used(origin_graph.size(), false);
    visited = 0;
    dfs1(0, used, origin_graph);
    if (visited != origin_graph.size())
    {
        cout << "NO";
        return 0;
    }

    cout << "YES\n" << find_MST(origin_graph, 0);

    return 0;
}