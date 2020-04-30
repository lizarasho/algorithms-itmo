#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> edges;
vector<int> r;
vector<bool> used;

struct vertex
{
    int x;
    int y;
};

struct order
{
    int time;
    vertex start;
    vertex finish;
};

vector<order> orders;

int dist(vertex a, vertex b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool dfs(int i)
{
    if (used[i]) {
        return false;
    }
    used[i] = true;

    for (int j : edges[i]) {
        if (r[j] == -1 || dfs(r[j])) {
            r[j] = i;
            return true;
        }
    }

    return false;
}

bool dfs2(int i)
{
    if (used[i]) {
        return false;
    }
    used[i] = true;

    if (r[i] != -1) {
        dfs2(r[i]);
    }
    return true;
}


int main()
{
    freopen ("taxi.in", "r", stdin);
    freopen ("taxi.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    size_t n;
    cin >> n;

    int prev = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        char ch;
        int hh, mm, a, b, c, d;
        cin >> hh >> ch >> mm >> a >> b >> c >> d;

        int time = k + 60 * hh + mm;
        k += (time < prev) * 24 * 60;

        orders.push_back({k + 60 * hh + mm, {a, b}, {c, d}});
        prev = time;
    }

    edges.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (orders[i].time + dist(orders[i].start, orders[i].finish) + dist(orders[i].finish, orders[j].start)
                < orders[j].time) {
                edges[i].push_back(j);
            }
        }
    }

    r.assign(n, -1);
    used.resize(n);

    for (int i = 0; i < n; i++) {
        if (dfs(i)) {
            fill(used.begin(), used.end(), false);
        }
    }

    fill(used.begin(), used.end(), false);
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += dfs2(i);
    }

    cout << ans;
}