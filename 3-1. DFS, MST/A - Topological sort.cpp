#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> color;
vector<int> ans;
bool cycle;

void dfs(int u)
{
    if (color[u] == 2)
        return;
    color[u] = 1;
    for (int v : graph[u])
    {
        if (color[v] == 1) {
            cycle = true;
            return;
        }
        dfs(v);
    }
    color[u] = 2;
    ans.push_back(u);
}

int main()
{
    size_t n, m;
    cin >> n >> m;
    graph.resize(n);
    color.resize(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }

    for (int i = 0; i < n; i++)
        dfs(i);

    if (cycle)
    {
        cout << -1;
        return 0;
    }

    reverse(ans.begin(), ans.end());
    for (int u : ans)
        cout << u + 1 << ' ';

    return 0;
}