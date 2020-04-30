#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<vector<int>> edges;
vector<int> r;
vector<bool> used;

struct ufo
{
    int time;
    int x;
    int y;
};

vector<ufo> vec;
int v;

double dist(ufo a, ufo b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)) / v * 60;
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
    freopen ("ufo.in", "r", stdin);
    freopen ("ufo.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n >> v;

    int prev = 0;
    for (int i = 0; i < n; i++) {
        char ch;
        int hh, mm, x, y;
        cin >> hh >> ch >> mm >> x >> y;

        vec.push_back({60 * hh + mm, x, y});
    }

    sort(vec.begin(), vec.end(), [] (ufo a, ufo b) { return a.time < b.time; });

    edges.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec[i].time + dist(vec[i], vec[j]) <= vec[j].time) {
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