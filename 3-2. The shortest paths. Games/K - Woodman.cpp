#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct edge
{
    int to;
    int num;
};
vector<vector<edge>> graph;
vector<bool> used;
vector<int> grundy;
int ans = -1;

void calc_grundy(int u)
{
    used[u] = true;
    int res = 0;

    for (auto [v, num] : graph[u])
    {
        if (!used[v])
        {
            calc_grundy(v);
            res ^= (grundy[v] + 1);
        }
    }
    grundy[u] = res;
}

void calc_edge(int u, int need)
{
    used[u] = true;
    for (auto [v, num] : graph[u])
    {
        if (used[v])
            continue;
        int new_need = need ^ grundy[u] ^ (grundy[v] + 1);
        if (new_need == 0)
        {
            ans = num;
            return;
        }
        calc_edge(v, new_need - 1);
        if (ans != -1)
            return;
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    size_t n;
    int r;
    cin >> n >> r;
    r--;
    graph.resize(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back({v - 1, i});
        graph[v - 1].push_back({u - 1, i});
    }
    used.resize(n);
    grundy.resize(n);

    calc_grundy(r);

    if (grundy[r] == 0)
    {
        cout << 2;
        return 0;
    }

    fill(used.begin(), used.end(), false);
    calc_edge(r, 0);

    cout << 1 << '\n' << ans;

    return 0;
}