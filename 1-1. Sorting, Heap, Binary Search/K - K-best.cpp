#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void merge(vector<double> & a, int l, int m, int r)
{
    vector<double> c(r - l);

    for (int k = 0, i = l, j = m; k < r - l; k++)
        c[k] = (j == r) || (i < m && (a[i] < a[j])) ? a[i++] : a[j++];

    for (int t = l, p = 0; t < r; t++, p++)
        a[t] = c[p];
}

void sort(vector<double> & a, int l, int r)
{
    if (r - l < 2)
        return;
    int m = (l + r) / 2;
    sort(a, l, m);
    sort(a, m, r);
    merge(a, l, m, r);
}

vector<int> v;
vector<int> w;
int n, k;
double const EPS = 10e-5;

double f(double m)
{
    vector<double> a(n);
    for (int i = 0; i < n; i++)
        a[i] = v[i] - m * w[i];
    sort(a, 0 , n);
    double f = 0;
    for (int i = n - 1; i >= n - k; i--)
        f += a[i];
    return f;
}


int main()
{
    cin >> n >> k;
    v.resize(n);
    w.resize(n);

    double r = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i] >> w[i];
        r = max(r, (double) v[i] / w[i]);
    }

    double l = -1;
    r += 1;
    while (r - l > EPS)
    {
        double m = (l + r) / 2;
        if (f(m) > 0)
            l = m;
        else
            r = m;
    }

    vector<double> a(n);
    vector<double> b(n);
    for (int i = 0; i < n; i++)
        a[i] = b[i] = v[i] - r * w[i];

    sort(b, 0, n);

    double min = b[n - k];
    int num = 0;
    int cur = 0;

    for (int i = n - k; i < n; i++)
    {
        if (b[i] != min)
            break;
        num++;
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] > min || (a[i] == min && cur < num))
            cout << i + 1 << '\n';
        cur += a[i] == min;
    }

    return 0;
}