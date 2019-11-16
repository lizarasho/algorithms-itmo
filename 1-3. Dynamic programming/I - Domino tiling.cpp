#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<long long>> dp (2);
vector<long long> need(14);
int n, m;

bool good(int x, int y, int col)
{
    for (int j = m - 1; j >= 0; j--)
    {
        if ((x >> j & 1) == 0)
        {
            if ((y >> j & 1) == 1)
            {
                if ((need[col - 1] >> j & 1) == 1)
                    return false;
                continue;
            }

            if ((need[col] >> j & 1) == 1 && (need[col - 1] >> j & 1) == 1)
                continue;
            if ((need[col - 1] >> j & 1) == 1)
                continue;

            if (j == 0 || x >> (j - 1) & 1 != 0 || (need[col - 1] >> (j - 1) & 1) == 1 || y >> (j - 1) & 1 != 0)
                return false;
            j--;
        }
    }
    return true;
}


int main() {

    cin >> m >> n;
    int mask = 1 << m;

    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
            if (s[j] == 'X')
                need[j] += 1 << (m - i - 1);
    }
    need[n] = mask - 1;

    bool all = true;

    for (int i = 0; i <= n; i++)
    {
        if (need[i] != mask - 1)
        {
            all = false;
            break;
        }
    }

    for (int x = 0; x < mask; x++)
    {
        dp[0].push_back(0);
        dp[1].push_back(0);
    }
    dp[0][0] = 1;


    for (int i = 1; i < n; i++)
    {
        for (int x = 0; x < mask; x++)
        {
            for (int y = 0; y < mask; y++)
            {
                if (((~need[i - 1] | x) == ~need[i - 1]) && ((~need[i] | y) == ~need[i]))
                {
                    if (((x & y) == 0) && good(x, y, i))
                    {
                        dp[1][y] += dp[0][x];
                    }
                }
            }
        }

        dp[0] = dp[1];
        for (int x = 0; x < mask; x++)
        {
            dp[1][x] = 0;
        }
    }

    long long res = 0;
    if (!all)
    {
        for (int x = 0; x < mask; x++)
        {
            if (good(x, 0, n))
            {
                res += dp[0][x];
            }
        }
        cout << res, 0;
    }

    cout << 1;
    return 0;
}
