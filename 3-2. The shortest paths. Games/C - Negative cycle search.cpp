#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>
#include <climits>

using namespace std;

struct edge
{
    int u;
    int v;
    int w;
};


int main()
{
    size_t n;
    cin >> n;
    vector<edge> edges;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int w;
            cin >> w;
            if (w == 100000)
                continue;
            edges.push_back({i, j, w});
        }
    }

    vector<int> d(n, 0);
    vector<int> p(n, -1);

    int a = -1;
    for (int k = 0; k < n; k++)
    {
        a = -1;
        for (auto [u, v, w] : edges)
        {
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                p[v] = u;
                a = v;
            }
        }
    }

    if (a == -1)
    {
        cout << "NO\n", 0;
    }

    cout << "YES\n";

    list<int> cycle;
    for (int i = 0; i < n; i++)
        a = p[a];

    int ptr = a;
    while (ptr != a || cycle.empty())
    {
        cycle.push_front(ptr);
        ptr = p[ptr];
    }

    cout << cycle.size() << '\n';
    for (int v : cycle)
        cout << v + 1 << ' ';

    return 0;
}