#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<vector<int>> graph;
vector<bool> used;
vector<int> t_in;
vector<int> d;
set<int> cutpoints;
int t = 0;

void dfs(int u, int p)
{
    t_in[u] = d[u] = t++;
    used[u] = true;
    int cnt = 0;
    for (int v : graph[u])
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
        if (d[v] >= t_in[u] && p != -1)
        {
            cutpoints.insert(u);
        }
        cnt++;
    }
    if (cnt > 1 && p == -1)
    {
        cutpoints.insert(u);
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
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            dfs(i, -1);
        }
    }

    cout << cutpoints.size() << '\n';

    for (int num : cutpoints)
    {
        cout << num + 1 << ' ';
    }

    return 0;
}