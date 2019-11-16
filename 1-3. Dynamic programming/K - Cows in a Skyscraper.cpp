#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);

    int n, w;
    cin >> n >> w;

    vector <pair<long long, long long>> dp(1 << n);
    vector<int> last(1 << n);
    vector<int> c(n);

    for (int i = 0; i < n; i++)
        cin >> c[i];

    for (int i = 1; i < 1 << n; i++)
        dp[i] = make_pair(INT_MAX, INT_MAX);
    dp[0] = make_pair(0, 0);

    pair<long long, long long> temp;

    for (int i = 1; i < 1 << n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >> j & 1)
            {
                temp = dp[i & ~(1 << j)];

                if (temp.second + c[j] < w)
                {
                    temp.second += c[j];
                }
                else if (temp.second + c[j] == w)
                {
                    temp.first++;
                    temp.second = 0;
                } else
                {
                    temp.first++;
                    temp.second = c[j];
                }

                if ((temp.first < dp[i].first) || (temp.first == dp[i].first && temp.second < dp[i].second))
                {
                    dp[i] = temp;
                    last[i] = j;
                }
            }
        }
    }

    cout << dp[(1 << n) - 1].first + (dp[(1 << n) - 1].second > 0);

    int mask = (1 << n) - 1;
    vector<int> way;

    while (mask > 0)
    {
        int from = last[mask];
        way.push_back(from);
        mask -= 1 << from;
    }
    cout << endl;

    int s = 0;
    vector<int> cur_way;

    for (int i = way.size() - 1; i >= 0 ; i--)
    {
        if (s + c[way[i]] > w)
        {
            cout << cur_way.size() << " ";
            for (int j = cur_way.size() - 1; j >= 0; j--)
                cout << cur_way[j] << " ";
            cout << endl;

            s = c[way[i]];
            cur_way.clear();
            cur_way.push_back(way[i] + 1);
            continue;
        }
        if (s + c[way[i]] == w)
        {
            cur_way.push_back(way[i] + 1);
            cout << cur_way.size() << " ";
            for (int j = cur_way.size() - 1; j >= 0; j--)
                cout << cur_way[j] << " ";
            cout << endl;
            cur_way.clear();
            s = 0;
            continue;
        }
        if (s + c[way[i]] < w)
        {
            cur_way.push_back(way[i] + 1);
            s += c[way[i]];
        }
    }

    if (!cur_way.empty())
    {
        cout << cur_way.size() << " ";
        for (int j = cur_way.size() - 1; j >= 0; j--)
            cout << cur_way[j] << " ";
    }

    return 0;
}
