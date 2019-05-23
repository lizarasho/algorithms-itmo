#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> dp(n + 1);

    dp[0].push_back(0);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        dp[i].push_back(x);
    }

    for (int j = 1; (1 << (j - 1)) < n; j++)
        for (int i = 0; i <= n; i++)
            dp[i].push_back(dp[dp[i][j - 1]][j - 1]);

    for (int i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (int j = 0; (1 << (j - 1) < n) && (dp[i][j]); j++)
            cout << dp[i][j] << " ";
        cout << endl;
    }
    return 0;
}