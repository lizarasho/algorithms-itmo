#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
const int MAX = 10000;
vector<int> c(MAX + 1);
vector<int> from(MAX + 1);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    cin >> n >> k;
    c[0] = c[1] = 0;
    for (int i = 2; i < n; i++)
        cin >> c[i];
    c[n] = 0;
    vector<int> dp(MAX + 1);
    dp[0] = dp[1] = 0;

    int max_index = 1;
    for (int i = 2; i <= n; i++)
    {
        if (max_index < i - k || dp[i - 1] > dp[max_index])
        {
            max_index = i - 1;
            for (int j = i - 2; j >= i - k; j--)
                if (j >= 1 && dp[j] >= dp[max_index])
                    max_index = j;
        }
        dp[i] = dp[max_index] + c[i];
        from[i] = max_index;
    }
    vector<int> way;
    int end = n;
    while (from[end] != 1)
    {
        way.push_back(end);
        end = from[end];
    }
    cout << dp[n] << endl;
    way.push_back(end);
    cout << way.size() << endl;
    way.push_back(1);
    for (int i = way.size() - 1; i >= 0; i--)
        cout << way[i] << " ";
}