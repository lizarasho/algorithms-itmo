#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <cmath>
#include <iomanip>

using namespace std;

struct point
{
    int x;
    int y;
};

int dist(point v1, point v2)
{
    auto [x1, y1] = v1;
    auto [x2, y2] = v2;
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    size_t n;
    cin >> n;
    vector<point> vert(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        vert[i] = {x, y};
    }

    vector<bool> used(n, false);
    vector<int> min(n, INT_MAX);
    vector<int> end(n, -1);
    min[0] = 0;

    double ans = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1;
        for (int j = 0; j < n; j++)
        {
            if (!used[j] && (u == -1 || min[j] < min[u]))
            {
                u = j;
            }
        }
        used[u] = true;
        ans += u == 0 ? 0 : sqrt(dist(vert[u], vert[end[u]]));
        for (int v = 0; v < n; v++)
        {
            if (dist(vert[u], vert[v]) < min[v])
            {
                min[v] = dist(vert[u], vert[v]);
                end[v] = u;
            }
        }
    }

    cout << setprecision(11) << ans;

    return 0;
}