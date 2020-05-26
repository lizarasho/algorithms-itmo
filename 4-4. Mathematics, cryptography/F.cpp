#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

#define PI 3.14159265358979323846

using namespace std;

vector<complex<double>> fft(vector<complex<double>> &a, complex<double> w)
{
    auto n = a.size();

    if (n == 1) {
        return vector({a[0]});
    }

    vector<complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    auto u0 = fft(a0, w * w);
    auto u1 = fft(a1, w * w);

    vector<complex<double>> u(n);

    auto p = complex<double>(1);
    for (int i = 0; i < n; i++) {
        u[i] = u0[i % (n / 2)] + p * u1[i % (n / 2)];
        p *= w;
    }

    return u;
}

vector<complex<double>> reverse_fft(vector<complex<double>> &a, complex<double> w)
{
    auto res = fft(a, w);
    auto n = res.size();

    for (int k = 0; k < n; k++) {
        res[k] /= n;
    }
    reverse(res.begin() + 1, res.end());

    return res;
}

void fill(vector<complex<double>> & a, string & s)
{
    int i = s[0] == '-';
    for (int k = (int) s.size() - 1; k >= i; k--) {
        a[s.size() - 1 - k] = s[k] - '0';
    }
    for (int k = (int) s.size() - i; k < a.size(); k++) {
        a[k] = 0;
    }
}

void prepare(size_t &n)
{
    size_t increased_n = 1;

    while (increased_n < n) {
        increased_n <<= 1;
    }

    n = 2 * increased_n;
}

vector<int> convert_to_num(vector<complex<double>> const &a)
{
    auto n = a.size();

    vector<int> ans(n);
    for (int k = 0; k < n; k++) {
        ans[k] = (int) (a[k].real() + 0.5);
    }

    int r = 0;
    for (int k = 0; k < n; k++) {
        ans[k] += r;
        r = ans[k] / 10;
        ans[k] %= 10;
    }

    while (ans.back() == 0) {
        ans.pop_back();
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    if (s1 == "0" || s2 == "0") {
        cout << 0;
        return 0;
    }
    int i = s1[0] == '-';
    int j = s2[0] == '-';

    int sign = (i == 0 ? 1 : -1) * (j == 0 ? 1 : -1);

    size_t n;
    n = max(s1.size() - i, s2.size() - j);
    prepare(n);

    vector<complex<double>> a(n);
    vector<complex<double>> b(n);

    fill(a, s1);
    fill(b, s2);

    double ang = 2 * PI / n;
    complex<double> w(cos(ang), sin(ang));

    auto u = fft(a, w);
    auto v = fft(b, w);

    vector<complex<double>> c(n);
    for (int k = 0; k < n; k++) {
        c[k] = u[k] * v[k];
    }

    auto ans = convert_to_num(reverse_fft(c, w));

    if (sign == -1) {
        cout << '-';
    }
    for (int k = ans.size() - 1; k >= 0; k--) {
        cout << ans[k];
    }

    return 0;
}