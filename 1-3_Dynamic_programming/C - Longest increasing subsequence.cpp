#include <iostream>
#include <algorithm>
#include<vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> dp(n);
    vector<int> a(n);
    vector<int> from(n);
    vector<int> nvp;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        dp[i] = 1;
    }

    int max_end = 0;

    for (int i = 0; i < n; i++) {
        int index = i;
        for(int j = 0; j < i; j++)
            if (a[j] < a[i] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                index = j;
            }
        from[i] = index;
        if (dp[i] > dp[max_end])
            max_end = i;
    }

    while (from[max_end] != max_end)
    {
        nvp.push_back(a[max_end]);
        max_end = from[max_end];
    }

    nvp.push_back(a[max_end]);
    cout << nvp.size() << endl;
    for (int i = nvp.size() - 1; i >= 0; i--)
        cout << nvp[i] << " ";
}