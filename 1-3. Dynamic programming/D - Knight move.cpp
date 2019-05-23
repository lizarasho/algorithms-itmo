#include <iostream>
#include <algorithm>
#include<vector>

using namespace std;

const int MOD = 1000000000;
const int N = 100;
long long dp[N + 1][10];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < 10; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i][0] = (dp[i - 1][4] + dp[i - 1][6]) % MOD;
        dp[i][1] = (dp[i - 1][6] + dp[i - 1][8]) % MOD;
        dp[i][2] = (dp[i - 1][9] + dp[i - 1][7]) % MOD;
        dp[i][3] = (dp[i - 1][4] + dp[i - 1][8]) % MOD;
        dp[i][4] = (dp[i - 1][3] + dp[i - 1][9] + dp[i - 1][0]) % MOD;
        dp[i][5] = 0;
        dp[i][6] = (dp[i - 1][1] + dp[i - 1][7] + dp[i - 1][0]) % MOD;
        dp[i][7] = (dp[i - 1][2] + dp[i - 1][6]) % MOD;
        dp[i][8] = (dp[i - 1][1] + dp[i - 1][3]) % MOD;
        dp[i][9] = (dp[i - 1][2]+ dp[i - 1][4]) % MOD;
    }
    long long s = 0;
    for (int i = 0; i < 10; i++)
        if (i != 0 && i != 8)
            s = (s + dp[n][i]) % MOD;
    cout << s;
}