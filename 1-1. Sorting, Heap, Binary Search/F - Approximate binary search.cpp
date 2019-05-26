#include <iostream>
#include <vector>

using namespace std;

int bin_search(vector<int> & a, int x)
{
    int l = -1;
    int r = a.size();
    while (r - l > 1)
    {
        int m = (r + l) / 2;
        if (a[m] <= x)
            l = m;
        else
            r = m;
    }
    return l;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> b(k);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < k; i++)
        cin >> b[i];

    for (int i = 0; i < k; i++)
    {
        int j = bin_search(a, b[i]);
        if (j == -1)
        {
            cout << a[0] << '\n';
            continue;
        }
        if (j == n - 1 || a[j] - b[i] >= b[i] - a[j + 1])
        {
            cout << a[j] << '\n';
            continue;
        }
        cout << a[j + 1] << '\n';
    }

    return 0;
}