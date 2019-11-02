#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

struct edge
{
    int u;
    int v;
};

vector<pair<edge, int>> edges;
vector<int> p;

int find(int a)
{
    if (p[a] != a)
        return p[a] = find(p[a]);
    return a;
}

void join(int a, int b)
{
    a = find(a);
    b = find(b);
    p[b] = a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    size_t n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({{u - 1, v - 1}, w});
    }

    sort(edges.begin(), edges.end(),
            [] (pair<edge, int> p1, pair<edge, int> p2) { return p1.second < p2.second; });

    p.resize(n);
    for (int i = 0; i < n; i++)
        p[i] = i;

    long long ans = 0;
    for (auto [e, w] : edges)
    {
        auto [u, v] = e;
        if (find(u) == find(v))
            continue;
        ans += w;
        join(u, v);
    }

    cout << ans;

    return 0;
}