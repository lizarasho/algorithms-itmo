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
    freopen ("game.in", "r", stdin);
    freopen ("game.out", "w", stdout);

    size_t n;
    int m, s;
    cin >> n >> m >> s;
    s--;

    graph.resize(n);
    used.resize(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }

    dfs(s);

    vector<bool> win(n, false);
    for (int u : vec)
    {
        for (int v : graph[u])
        {
            win[u] = win[u] | !win[v];
        }
    }

    cout << (win[s] ? "First" : "Second") << " player wins";

    return 0;
}