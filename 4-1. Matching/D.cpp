#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool dfs(int i, vector<vector<int>> &edges, vector<int> &r, vector<bool> &used)
{
    if (used[i]) {
        return false;
    }
    used[i] = true;

    for (int j : edges[i]) {
        if (r[j] == -1 || dfs(r[j], edges, r, used)) {
            r[j] = i;
            return true;
        }
    }

    return false;
}

bool dfs2(int i, vector<vector<int>> &edges, vector<int> &r, vector<bool> &used, vector<bool> &right_used)
{
    if (used[i]) {
        return false;
    }
    used[i] = true;

    for (int j : edges[i]) {
        if (!right_used[j]) {
            right_used[j] = true;
            dfs2(r[j], edges, r, used, right_used);
        }
    }

    return false;
}

int main()
{
    freopen ("birthday.in", "r", stdin);
    freopen ("birthday.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        size_t m, n;
        cin >> m >> n;

        vector<unordered_set<int>> edges(m);

        for (int j = 0; j < m; j++) {
            int g;
            while (cin >> g) {
                if (g == 0) {
                    break;
                }
                edges[j].insert(g - 1);
            }
        }

        vector<vector<int>> reversed_edges(m);

        for (int j = 0; j < m; j++) {
            for (int g = 0; g < n; g++) {
                if (edges[j].count(g)) {
                    continue;
                }
                reversed_edges[j].push_back(g);
            }
        }

        vector<int> r(n, -1);
        vector<bool> used(m, false);

        for (int j = 0; j < m; j++) {
            if (dfs(j, reversed_edges, r, used)) {
                fill(used.begin(), used.end(), false);
            }
        }

        unordered_set<int> free_vertex;
        for (int j = 0; j < m; j++) {
            free_vertex.insert(j);
        }
        for (int j : r) {
            free_vertex.erase(j);
        }

        vector<bool> right_used(n, false);
        fill(used.begin(), used.end(), false);

        for (int j : free_vertex) {
            dfs2(j, reversed_edges, r, used, right_used);
        }

        vector<int> boys;
        vector<int> girls;
        for (int j = 0; j < m; j++) {
            if (used[j]) {
                boys.push_back(j + 1);
            }
        }
        for (int j = 0; j < n; j++) {
            if (!right_used[j]) {
                girls.push_back(j + 1);
            }
        }

        cout << boys.size() + girls.size() << '\n';
        cout << boys.size() << ' ' << girls.size() << '\n';
        for (int j : boys) {
            cout << j << ' ';
        }
        cout << '\n';
        for (int j : girls) {
            cout << j << ' ';
        }
        cout << "\n\n";
    }
}