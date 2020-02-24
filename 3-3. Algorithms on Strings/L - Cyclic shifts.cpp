#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>
#include <climits>
#include <unordered_map>

using namespace std;

int const L = 32;
int const R = 126;

vector<vector<int>> calc(R - L + 1);
vector<int> p;
vector<int> c;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    auto n = s.size();

    c.resize(n);

    for (int i = 0; i < n; i++) {
        calc[s[i] - L].push_back(i);
    }

    int cnt = 0;
    for (auto i = 0; i < calc.size(); i++) {
        for (int ind : calc[i]) {
            c[ind] = cnt;
            p.push_back(ind);
        }
        if (!calc[i].empty()) {
            cnt++;
        }
    }

    for (auto k = 0; (1 << k) < n; k++) {
        vector<int> second_sorted(n);
        for (int i = 0; i < n; i++) {
            second_sorted[i] = int((p[i] - (1 << k) + n) % n);
        }

        vector<vector<int>> calc(cnt);
        for (int ind : second_sorted) {
            calc[c[ind]].push_back(ind);
        }

        p.clear();
        for (int i = 0; i < cnt; i++) {
            for (int ind : calc[i]) {
                p.push_back(ind);
            }
        }

        int new_cnt = 0;
        auto prev_fir = c[p[0]];
        auto prev_sec = c[(p[0] + (1 << k)) % n];
        c[p[0]] = new_cnt;

        vector<int> new_c(n);

        for (int i = 1; i < p.size(); i++) {
            auto ind = p[i];
            auto fir = c[ind];
            auto sec = c[(ind + (1 << k)) % n];

            if (fir != prev_fir || sec != prev_sec) {
                new_cnt++;
            }
            new_c[ind] = new_cnt;

            prev_fir = fir;
            prev_sec = sec;
        }

        c = new_c;
        cnt = ++new_cnt;
    }

    int k;
    cin >> k;

    string res;
    for (int i = 0; i < n; i++) {
        if (c[i] == k - 1) {
            for (int j = i; j < n; j++) {
                cout << s[j];
            }
            for (int j = 0; j < i; j++) {
                cout << s[j];
            }
            return 0;
        }
    }

    cout << "IMPOSSIBLE";
    return 0;
}