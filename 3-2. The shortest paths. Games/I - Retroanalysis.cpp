#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> in;
vector<int> deg;
vector<int> win;
vector<bool> used;

void dfs(int v)
{
    used[v] = true;
    for (int u : in[v])
    {
        if (used[u])
            continue;
        if (win[v] == 1)
        {
            deg[u]--;
            if (deg[u] == 0)
            {
                win[u] = false;
                dfs(u);
            }
        } else if (win[v] == 0)
        {
            win[u] = true;
            dfs(u);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    size_t n;

    while (cin >> n)
    {
        int m;
        cin >> m;

        graph.clear();
        in.clear();
        win.clear();
        deg.clear();
        used.clear();

        graph.resize(n);
        in.resize(n);
        win.resize(n, -1);
        deg.resize(n, 0);
        used.resize(n, false);

        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            graph[u - 1].push_back(v - 1);
            in[v - 1].push_back(u - 1);
            deg[u - 1]++;
        }

        for (int u = 0; u < n; u++)
        {
            if (deg[u] == 0)
            {
                win[u] = false;
                dfs(u);
            }
        }

        for (int res : win)
        {
            switch (res)
            {
                case 1 :
                    cout << "FIRST\n";
                    break;
                case 0 :
                    cout << "SECOND\n";
                    break;
                case -1 :
                    cout << "DRAW\n";
            }
        }
        cout << '\n';
    }

    return 0;
}