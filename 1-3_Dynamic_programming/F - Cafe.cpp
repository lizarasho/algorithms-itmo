#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits.h>
using namespace std;

const int N = 100;
long long dp[N + 1][N + 1];
int c[N + 1];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;

    for (int i = 0; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            dp[i][j] = INT_MAX;

    dp[1][0] = c[1];

    if (c[1] > N)
        dp[1][1] = c[1];
    else
        dp[1][1] = INT_MAX;

    for (int i = 2; i <= n; i++)
        dp[i][0] = INT_MAX;

    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= n; j++)
        {
            if (c[i] <= N)
                dp[i][j] = min(dp[i - 1][j] + c[i], dp[i - 1][j + 1]);
            else
            {
                if (j > 0)
                    dp[i][j] = min(dp[i - 1][j - 1] + c[i], dp[i - 1][j + 1]);
                else
                    dp[i][j] = dp[i - 1][j + 1];
            }

            if (dp[i][j] > INT_MAX)
                dp[i][j] = INT_MAX;
        }


    int k1 = 0;
    while (k1 < n && dp[n][k1] >= dp[n][k1 + 1] && dp[n][k1 + 1] > 0)
        k1++;

    cout << dp[n][k1] << endl;
    cout << k1 << " ";
    int str = n;
    int stl = k1;
    vector<int> days;
    while (str > 0)
    {
        if (dp[str][stl] == dp[str - 1][stl + 1])
        {
            days.push_back(str);
            str--;
            stl++;
        }
        else
        {
            str--;
            if (c[str + 1] > 100)
                stl--;
        }
    }
    cout << days.size() << endl;

    for (int i = days.size() - 1; i >= 0; i--)
        cout << days[i] << endl;
}