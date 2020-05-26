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

result gcd(ll a, ll b)
{
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [d, x, y] = gcd(b, a % b);
    return {d, y, x - y * (a / b)};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, n, m;
    cin >> a >> b >> n >> m;

    auto x = gcd(n, m).x * (b - a);

    ll res = a + x * n;
    while (res < 0) {
        res += m * n;
    }
    while (res > m * n) {
        res -= m * n;
    }

    cout << res << '\n';

    return 0;
}