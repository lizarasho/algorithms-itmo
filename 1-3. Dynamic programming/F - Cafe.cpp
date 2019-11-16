#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;

#define INF INT_MAX

const int N = 100;

vector<vector<long long>> dp;
vector<int> c(N + 1);

int main()
{
    int n;
    cin >> n;

    dp.resize(N + 1, vector<long long>(N + 1, 0));
    for (int i = 1; i < n + 1; i++)
        cin >> c[i];

    for (int i = 0; i < n + 1; i++)
        for (int j = i + 1; j < n + 1; j++)
            dp[i][j] = INF;

    dp[1][0] = c[1];
    dp[1][1] = (c[1] > N) ? c[1] : INF;

    for (int i = 2; i < n + 1; i++)
        dp[i][0] = INF;

    for (int i = 2; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (c[i] <= N)
            {
                dp[i][j] = min(dp[i - 1][j] + c[i], dp[i - 1][j + 1]);
            } else if (j > 0)
            {
                dp[i][j] = min(dp[i - 1][j - 1] + c[i], dp[i - 1][j + 1]);
            } else
            {
                dp[i][j] = dp[i - 1][j + 1];
            }

            if (dp[i][j] > INF)
            {
                dp[i][j] = INF;
            }
        }
    }


    int col = 0;
    while (col < n && dp[n][col] >= dp[n][col + 1] && dp[n][col + 1] > 0)
        col++;

    cout << dp[n][col] << '\n';
    cout << col << ' ';

    int line = n;

    vector<int> days;
    while (line > 0)
    {
        if (dp[line][col] == dp[line - 1][col + 1])
        {
            days.push_back(line);
            line--;
            col++;
            continue;
        }
        line--;
        if (c[line + 1] > N)
            col--;
    }

    cout << days.size() << '\n';

    for (int i = days.size() - 1; i >= 0; i--)
        cout << days[i] << '\n';

    return 0;
}
