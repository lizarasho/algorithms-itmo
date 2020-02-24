#include <iostream>
#include <vector>

using namespace std;

int const x = 11;

int main()
{
    string s;
    cin >> s;

    auto n = s.size();

    vector<int> pow(n + 1);
    vector<int> hash(n + 1);

    pow[0] = 1;
    hash[0] = 0;

    for (int i = 1; i < n + 1; i++) {
        pow[i] = x * pow[i - 1];
        hash[i] = hash[i - 1] * x + s[i - 1];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        cout << ((hash[r1] - hash[l1 - 1] * pow[r1 - (l1 - 1)] ==
                  hash[r2] - hash[l2 - 1] * pow[r2 - (l2 - 1)])
                 ? "Yes\n"
                 : "No\n");
    }


    return 0;
}