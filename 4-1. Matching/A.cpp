#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> edges;
vector<int> r;
vector<bool> used;

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


int main()
{
    size_t n, m;
    cin >> n >> m;
    edges.resize(n);
    for (int i = 0; i < n; i++) {
        int k;
        while (cin >> k) {
            if (k == 0) {
                break;
            }
            edges[i].push_back(k - 1);
        }
    }

    r.resize(m, -1);
    used.resize(n, false);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dfs(i)) {
            ans++;
            fill(used.begin(), used.end(), false);
        }
    }

    cout << ans << '\n';
    for (int j = 0; j < m; j++) {
        if (r[j] == -1) {
            continue;
        }
        cout << r[j] + 1 << ' ' << j + 1 << '\n';
    }
}