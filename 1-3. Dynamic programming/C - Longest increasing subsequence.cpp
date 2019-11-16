#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<int> dp(n, 1);
    vector<int> a(n);
    vector<int> from(n);
    vector<int> ans;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    int max_end = 0;

    for (int i = 0; i < n; i++)
    {
        int index = i;
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                index = j;
            }
        }

        from[i] = index;

        if (dp[i] > dp[max_end])
        {
            max_end = i;
        }
    }

    while (from[max_end] != max_end)
    {
        ans.push_back(a[max_end]);
        max_end = from[max_end];
    }

    ans.push_back(a[max_end]);

    cout << ans.size() << '\n';
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << ' ';

    return 0;
}
