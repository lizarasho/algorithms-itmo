#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct result
{
    ll d;
    ll x;
    ll y;
};

ll multiply(ll a, ll b, ll mod)
{
    if (b == 1) {
        return a;
    }
    if (b % 2 == 1) {
        return (multiply(a, b - 1, mod) + a) % mod;
    }
    auto x = multiply(a, b / 2, mod);
    return (x << 1) % mod;
}

result gcd(ll a, ll b)
{
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [d, x, y] = gcd(b, a % b);
    return {d, y, x - y * (a / b)};
}

ll bin_pow(ll a, ll p, ll mod)
{
    if (p == 1) {
        return a;
    }
    if (p % 2 == 1) {
        auto x = bin_pow(a, p - 1, mod);
        return multiply(x, a, mod);
    }
    auto x = bin_pow(a, p / 2, mod);
    return multiply(x, x, mod);
}

ll get_reverse(ll a, ll mod)
{
    auto [g, x, _] = gcd(a, mod);
    x /= g;
    if (x < 0) {
        x += mod;
    }
    return x;
}

pair<ll, ll> get_factorization(ll n)
{
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            return {i, n / i};
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, e, c;
    cin >> n >> e >> c;
    auto [p, q] = get_factorization(n);

    auto mod = (p - 1) * (q - 1);
    auto d = get_reverse(e, mod);

    cout << bin_pow(c, d, n);

    return 0;
}