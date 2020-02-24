#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string s;
    cin >> s;

    vector<int> z(s.size(), 0);

    for (int i = 1, l = 0, r = 1; i < z.size(); i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i);
        }
        while (s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
        cout << z[i] << ' ';
    }

    return 0;
}