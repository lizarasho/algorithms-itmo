#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 13;
long long dp[N][1 << N];
long long from[N][1 << N];
long long n;
long long road[N][N];

int main() {
    
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> road[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 1 << n; j++)
            dp[i][j] = INT_MAX;

    for (int i = 0; i < n; i++)
        dp[i][0] = 0;

    for (int x = 0; x < (1 << n); x++)
        for (int i = 0; i < n; i++)
            if ((x >> i & 1) == 1)
                for (int j = 0; j < n; j++)
                    if (dp[j][x - (1 << i)] + road[i][j] < dp[i][x])
                    {
                        dp[i][x] = dp[j][x - (1 << i)] + road[i][j];
                        from[i][x] = j;
                    }

    long long k, last, temp;
    long long minimum = INT_MAX;

    for (int i = 0; i < n; i++)
        if (dp[i][(1 << n) - 1] < minimum)
        {
            minimum = dp[i][(1 << n) - 1];
            last = i;
        }

    long long x = (1 << n) - 1;
    vector<long long> way;

    for (int i = 0; i < n; i++)
    {
        way.push_back(last + 1);
        temp = last;
        last = from[last][x];
        x -= (1 << temp);
    }

    cout << minimum << endl;

    for (int i = n - 1; i >= 0; i--)
        cout << way[i] << " ";
}