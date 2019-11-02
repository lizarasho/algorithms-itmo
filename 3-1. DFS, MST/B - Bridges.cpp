#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct edge
{
    int to;
    int num;
};

vector<vector<edge>> graph;
vector<bool> used;
vector<int> t_in;
vector<int> d;
vector<int> bridges;
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
            bridges.push_back(num);
        }
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
    used.resize(n);
    t_in.resize(n);
    d.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back({v - 1, i + 1});
        graph[v - 1].push_back({u - 1, i + 1});
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            dfs(i, -1);
        }
    }

    cout << bridges.size() << '\n';
    sort(bridges.begin(), bridges.end());
    for (int num : bridges)
    {
        cout << num << '\n';
    }

    return 0;
}