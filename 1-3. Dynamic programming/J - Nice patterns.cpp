#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <unordered_set>

using namespace std;

int main()
{
    vector<vector<int>> dp(2);
    vector<unordered_set<int>> vec(1 << 15);

    int n, m;
    cin >> n >> m;
    if (n > m)
        swap(n, m);

    for (int x = 0; x < 1 << n; x++)
    {
        for (int y = x; y < 1 << n; y++)
        {
            bool f = true;
            for (int j = 0; j < n - 1; j++)
                if ((x >> j & 1) == (y >> j & 1) 
                    && (y >> j & 1) == (x >> (j + 1) & 1) 
                    && (x >> (j + 1) & 1) == (y >> (j + 1) & 1))
                {
                    f = false;
                    break;
                }
            if (f)
            {
                vec[x].insert(y);
                vec[y].insert(x);
            }
        }
    }

    for (int x = 0; x < 1 << n; x++)
    {
        dp[0].push_back(1);
        dp[1].push_back(0);
    }

    for (int i = 1; i < m; i++)
    {
        for (int x = 0; x < (1 << n); x++)
            for (int y : vec[x])
                dp[1][x] += dp[0][y];

        dp[0] = dp[1];
        for (int x = 0; x < (1 << n); x++)
            dp[1][x] = 0;
    }

    long res = 0;
    for (int x = 0; x < 1 << n; x++)
        res += dp[0][x];

    cout << res;
}
