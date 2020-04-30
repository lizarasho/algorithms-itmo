#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> edges;
vector<int> r;
vector<bool> used;
vector<vector<bool>> is__empty;
size_t n, m;

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

int get(int i, int j) {
    return ((i * m + j) / 2);
}


int main()
{
    freopen ("dominoes.in", "r", stdin);
    freopen ("dominoes.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int a, b;
    cin >> n >> m >> a >> b;

    is__empty.resize(n, vector<bool>(m, false));

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '*') {
                is__empty[i][j] = true;
                cnt++;
            }
        }
    }

    if (2 * b <= a) {
        cout << b * cnt;
        return 0;
    }

    size_t k = n * m;
    edges.resize(k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!is__empty[i][j] || (i + j) % 2 == 0) {
                continue;
            }
            if (j > 0 && is__empty[i][j - 1]) {
                edges[get(i, j)].push_back(get(i, j - 1));
            }
            if (j < m - 1 && is__empty[i][j + 1]) {
                edges[get(i, j)].push_back(get(i, j + 1));
            }
            if (i > 0 && is__empty[i - 1][j]) {
                edges[get(i, j)].push_back(get(i - 1, j));
            }
            if (i < n - 1 && is__empty[i + 1][j]) {
                edges[get(i, j)].push_back(get(i + 1, j));
            }
        }
    }

    r.assign(k, -1);
    used.resize(k);

    for (int i = 0; i < k; i++) {
        if (dfs(i)) {
            fill(used.begin(), used.end(), false);
        }
    }

    int ans = 0;
    for (int j : r) {
        ans += (j != -1);
    }

    cout << ans * a + (cnt - 2 * ans) * b;
    return 0;
}