#include <iostream>
#include <vector>

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

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a, 0, n);

    for (int i : a)
        cout << i << " ";
    return 0;
}