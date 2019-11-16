#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits.h>

#define INF LONG_LONG_MAX

using namespace std;

vector<vector<long long>> dp;

int main()
{
    string a, b;
    cin >> a;
    cin >> b;

    dp.resize(a.size() + 1, vector<long long>(b.size() + 1, INF));

    for (int i = 0; i <= a.size(); i++)
    {
        for (int j = 0; j <= b.size(); j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = i + j;
                continue;
            }
            if (i > 0 && j > 0 && a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            if (i > 0 && j > 0)
            {
                dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j - 1]);
                dp[i][j] = min(dp[i][j], 1 + dp[i][j - 1]);
                dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j]);
            }
        }
    }

    cout << dp[a.length()][b.length()];
}
