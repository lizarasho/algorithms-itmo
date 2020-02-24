#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <climits>

#define INF INT_MAX;

using namespace std;

int const x = 5051;
int const N = 10000;

vector<vector<int>> h;
vector<string> str;
vector<int> p(N + 1);

string common_substr(int l)
{
    unordered_set<int> set;

    for (int j = 0; j < h[0].size() - l; j++) {
        set.insert(h[0][j + l] - h[0][j] * p[l]);
    }

    string ans;
    auto k = h.size();

    for (int i = 0; i < k; i++) {
        unordered_set<int> next_set;
        for (int j = 0; j < h[i].size() - l; j++) {
            auto hash = h[i][j + l] - h[i][j] * p[l];
            if (set.count(hash)) {
                next_set.insert(hash);
                if (i == k - 1) {
                    ans = str[i].substr(j, l);
                    break;
                }
            }
        }
        set = next_set;
    }

    return ans;
}


int main()
{
    size_t k;
    cin >> k;

    h.resize(k);
    str.resize(k);

    p[0] = 1;
    for (int i = 1; i < N + 1; i++) {
        p[i] = x * p[i - 1];
    }

    int l = -1;
    int r = INF;

    for (int i = 0; i < k; i++) {
        cin >> str[i];

        auto s = str[i];
        r = min(r, (int)s.size() + 1);

        h[i].resize(s.size() + 1);
        h[i][0] = 0;
        for (int j = 1; j < h[i].size(); j++) {
            h[i][j] = h[i][j - 1] * x + s[j - 1];
        }
    }

    string res;

    while (r - l > 1) {
        int m = (l + r) / 2;
        string s = common_substr(m);
        if (!s.empty() || !m) {
            res = s;
            l = m;
        } else {
            r = m;
        }
    }

    cout << res;
    return 0;
}