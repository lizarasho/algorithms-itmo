#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

const int N = 100;
int dp[N][N];
int from[N][N];
string s;

string build(int i, int j)
{
    if (dp[i][j] == 0)
        return s.substr(i, j + 1 - i);
    if (dp[i][j] == j - i + 1)
        return "";
    if (from[i][j] == INT_MAX)
        return s[i] + build(i + 1, j - 1) + s[j];
    return build(i, from[i][j]) + build(from[i][j] + 1, j);
}

int main()
{
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            dp[i][j] = (i == j);

    for (int j = 0; j < n; j++)
        for (int i = j - 1; i >= 0; i--)
        {
            int index = INT_MAX;
            int minimum = INT_MAX;
            if (s[i] == '(' && s[j] == ')' || s[i] == '[' && s[j] == ']' || s[i] == '{' && s[j] == '}')
                minimum = dp[i + 1][j - 1];
            for (int x = i; x < j; x++)
                if (dp[i][x] + dp[x + 1][j] < minimum)
                {
                    minimum = dp[i][x] + dp[x + 1][j];
                    index = x;
                }
            from[i][j] = index;
            dp[i][j] = minimum;
        }

    cout << build(0, n - 1);
}