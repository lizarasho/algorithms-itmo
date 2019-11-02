#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <climits>
#include <unordered_set>

using namespace std;

vector<vector<int>> out;
vector<vector<int>> in;

vector<vector<int>> graph;
vector<bool> used;
vector<int> comp;
vector<int> p;
int cnt;

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

bool is_good(int m)
{
    fill(comp.begin(), comp.end(), -1);
    fill(used.begin(), used.end(), false);
    p.clear();
    for (int i = 0; i < in.size(); i++)
    {
        in[i].clear();
        out[i].clear();
    }

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            if (i == j)
                continue;
            if (graph[i][j] <= m)
            {
                out[i].push_back(j);
                in[j].push_back(i);
            }
        }
    }

    for (int i = 0; i < graph.size(); i++)
    {
        dfs1(i);
    }

    cnt = 1;
    for (int i = graph.size() - 1; i >= 0; i--)
    {
        int v = p[i];
        if (comp[v] != -1)
            continue;
        dfs2(v, cnt++);
    }
    return cnt - 1 == 1;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    freopen ("avia.in", "r", stdin);
    freopen ("avia.out", "w", stdout);

    int n;
    cin >> n;
    out.resize(n);
    in.resize(n);
    used.resize(n);
    comp.resize(n);
    graph.resize(n);


    int mn = INT_MAX;
    int mx = 0;

    for (int i = 0; i < n; i++)
    {
        graph[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            int c;
            cin >> c;
            mn = min(mn, c);
            mx = max(mx, c);
            graph[i][j] = c;
        }
    }

    int l = mn - 1;
    int r = mx;
    while (r - l > 1)
    {
        int m = (r + l) / 2;
        if (!is_good(m))
            l = m;
        else
            r = m;
    }

    cout << r;
    return 0;
}