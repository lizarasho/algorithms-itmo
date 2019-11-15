#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF LONG_LONG_MAX

struct edge
{
    int v;
    int w;
};

int main()
{
    size_t n, m, k;
    int s;
    cin >> n >> m >> k >> s;
    vector<vector<edge>> in(n);
    vector<vector<long long>> d(n, vector<long long>(k + 1, INF));

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        in[v - 1].push_back({u - 1, w});
    }

    d[s - 1][0] = 0;
    for (int i = 0; i < k; i++)
    {
        for (int v = 0; v < n; v++)
        {
            for (auto [u, w] : in[v])
            {
                if (d[u][i] == INF)
                    continue;
                d[v][i + 1] = min(d[v][i + 1], d[u][i] + w);
            }
        }
    }

    for (int v = 0; v < n; v++)
        cout << (d[v][k] == INF ? -1 : d[v][k]) << '\n';

    return 0;
}