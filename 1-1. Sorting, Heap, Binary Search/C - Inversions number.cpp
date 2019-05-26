#include <iostream>
#include <vector>

using namespace std;

long long ans = 0;

void merge(vector<int> & a, int l, int m, int r)
{
    vector<int> c(r - l);

    for (int k = 0, i = l, j = m; k < r - l; k++)
    {
        if ((i < m) && (j < r) && (a[i] > a[j]))
            ans += m - i;

        c[k] = (j == r) || (i < m && (a[i] < a[j])) ? a[i++] : a[j++];
    }

    for (int t = l, p = 0; t < r; t++, p++)
        a[t] = c[p];
}

void calc(vector<int> & a, int l, int r)
{
    if (r - l < 2)
        return;
    int m = (l + r) / 2;
    calc(a, l, m);
    calc(a, m, r);
    merge(a, l, m, r);
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    calc(a, 0, n);

    cout << ans;

    return 0;
}