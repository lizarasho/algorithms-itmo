#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

typedef long long ll;

int const N = 3;

ll gcd(ll a, ll b)
{
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

pair<ll, ll> decompose(ll n)
{
    ll s = n;
    ll pow = 0;
    for (; !(s & 1); s >>= 1, pow++);
    return { s, pow };
}

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

bool prime(ll n)
{
    if (n == 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    srand(unsigned((time(nullptr))));

    // n - 1 = s * 2 ^ p
    auto [s, p] = decompose(n - 1);

    for (int i = 0; i < N; i++) {
        
        ll x = (rand() % (n - 2)) + 2;
        if (gcd(x, n) != 1) {
            return false;
        }

        auto cur = bin_pow(x, s, n);
        if (cur == 1 || cur == n - 1) {
            continue;
        }

        for (int j = 1; j < p; j++) {
            cur = bin_pow(cur, 2, n);
            if (cur == n - 1) {
                break;
            }
        }

        if (cur != n - 1) {
            return false;
        }
    }

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        cout << (prime(a) ? "YES" : "NO") << '\n';
    }

    return 0;
}