#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<vector<int>> out;
vector<vector<int>> in;
vector<bool> used;
vector<int> comp;
vector<int> p;
vector<unordered_set<int>> condensation;

void dfs1(int v)
{
    if (used[v])
        return;
    used[v] = true;
    for (int u : out[v])
        dfs1(u);
    p.push_back(v);
}

void dfs2(int v, int c)
{
    if (comp[v] != -1)
        return;
    comp[v] = c;
    for (int u : in[v])
        dfs2(u, c);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    int n, m;
    cin >> n >> m;
    out.resize(n);
    in.resize(n);
    used.resize(n);
    comp.resize(n);
    fill(comp.begin(), comp.end(), -1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        out[u - 1].push_back(v - 1);
        in[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < n; i++)
    {
        dfs1(i);
    }

    int cnt = 1;
    for (auto i = n - 1; i >= 0; i--)
    {
        int v = p[i];
        if (comp[v] != -1)
            continue;
        dfs2(v, cnt);
        cnt++;
    }

    condensation.resize(cnt);
    for (int u = 0; u < n; u++)
    {
        for (int v : out[u])
        {
            if (comp[u] != comp[v])
            {
                condensation[comp[u]].insert(comp[v]);
            }
        }
    }

    int ans = 0;
    for (auto &s : condensation)
        ans += s.size();

    cout << ans;

    return 0;
}