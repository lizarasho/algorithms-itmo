#include <iostream>
#include <vector>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<int> p(n + 1);
    vector<vector<int>> dp(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> p[i];

    dp[0].push_back(0);
    for (int i = 1; i <= n; i++)
        dp[i].push_back(p[i]);

    for (int j = 1; (1 << (j - 1)) < n; j++)
        for (int i = 0; i <= n; i++)
            dp[i].push_back(dp[dp[i][j - 1]][j - 1]);

    for (int i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (int j = 0; (1 << (j - 1) < n) && dp[i][j]; j++)
            cout << dp[i][j] << " ";
        cout << '\n';
    }
    return 0;
}