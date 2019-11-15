#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<vector<int>> graph;
vector<bool> used;
vector<int> vec;

void dfs(int u)
{
    if (used[u])
        return;
    used[u] = true;
    for (int v : graph[u])
        dfs(v);
    vec.push_back(u);
}

int main()
{
    size_t n;
    int m;
    cin >> n >> m;

    graph.resize(n);
    used.resize(n);
    vector<int> deg(n);

    int max_deg = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        deg[u - 1]++;
        max_deg = max(max_deg, deg[u - 1]);
    }

    for (int u = 0; u < n; u++)
        dfs(u);

    vector<int> grundy(n);
    vector<bool> was(max_deg + 1);

    for (int u : vec)
    {
        fill(was.begin(), was.end(), false);
        for (int v : graph[u])
            was[grundy[v]] = true;
        int res = 0;
        while (was[res])
            res++;
        grundy[u] = res;
        fill(was.begin(), was.end(), false);
    }

    for (int res : grundy)
        cout << res << '\n';

    return 0;
}