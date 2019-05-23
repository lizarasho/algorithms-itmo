#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;
const int N = 1000;
long long dp[N + 1][N + 1];

int main()
{
    int n;
    string a, b;
    cin >> a;
    cin >> b;
    for (int i = 0; i <= a.size(); i++)
        for (int j = 0; j <= b.size(); j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = i + j;
                continue;
            }
            dp[i][j] = LONG_LONG_MAX;
            if (i > 0 && j > 0 && a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
            if (i > 0 && j > 0)
            {
                dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j - 1]);
                dp[i][j] = min(dp[i][j], 1 + dp[i][j - 1]);
                dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j]);
            }
        }
    cout << dp[a.length()][b.length()];
}