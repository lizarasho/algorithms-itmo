#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void merge(vector<int> & a, int l, int m, int r)
{
    vector<int> c(r - l);

    for (int k = 0, i = l, j = m; k < r - l; k++)
        c[k] = (j == r) || (i < m && (a[i] < a[j])) ? a[i++] : a[j++];

    for (int t = l, p = 0; t < r; t++, p++)
        a[t] = c[p];
}

void sort(vector<int> & a, int l, int r)
{
    if (r - l < 2)
        return;
    int m = (l + r) / 2;
    sort(a, l, m);
    sort(a, m, r);
    merge(a, l, m, r);
}

int bin_search(vector<int> & a, int x)
{
    int l = -1;
    int r = a.size();

    while (r > l + 1)
    {
        int m = (r + l) / 2;
        if (a[m] <= x)
            l = m;
        else
            r = m;
    }
    return r;
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, 0, n);

    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << bin_search(a, r) - bin_search(a, l - 1) << " ";
    }
    return 0;
}