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

vector<int> convert(vector<complex<double>> const &a)
{
    auto n = a.size();

    vector<int> ans(n);
    for (int k = 0; k < n; k++) {
        ans[k] = (int) (a[k].real() + 0.5);
    }

    return ans;
}

int main()
{
    freopen("duel.in", "r", stdin);
    freopen("duel.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    size_t n = s.size();
    prepare(n);

    vector<complex<double>> a(n);
    fill(a, s);

    double ang = 2 * PI / n;
    complex<double> w(cos(ang), sin(ang));

    auto u = fft(a, w);

    vector<complex<double>> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = u[i] * u[i];
    }

    auto ans = convert(reverse_fft(c, w));

    long long sum = 0;
    reverse(s.begin(), s.end());

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '1') {
            sum += ans[2 * i] / 2;
        }
    }

    cout << sum;

    return 0;
}