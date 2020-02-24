#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string p, t;
    cin >> p >> t;

    string s = p + '#' + t;

    vector<int> pr(s.size() + 1);
    pr[0] = -1;

    vector<int> ans;

    for (int i = 1; i < s.size() + 1; i++) {
        for (int k = pr[i - 1]; ; k = pr[k]) {
            if (k == -1 || s[k] == s[i - 1]) {
                pr[i] = k + 1;
                break;
            }
        }
        if (pr[i] == p.size()) {
            ans.push_back((int)(i - 2 * p.size()));
        }
    }

    cout << ans.size() << '\n';
    for (int e : ans) {
        cout << e << ' ';
    }

    return 0;
}