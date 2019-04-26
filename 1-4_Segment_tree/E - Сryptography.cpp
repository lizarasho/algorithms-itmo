#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1 << 18;
int r;
struct node
{
    int x11;
    int x12;
    int x21;
    int x22;
};
node E = {1, 0, 0, 1};
vector<node> s(2 * N - 1);

node multiply (node A1, node A2)
{
    return
    {
        (A1.x11 * A2.x11 + A1.x12 * A2.x21) % r,
        (A1.x11 * A2.x12 + A1.x12 * A2.x22) % r,
        (A1.x21 * A2.x11 + A1.x22 * A2.x21) % r,
        (A1.x21 * A2.x12 + A1.x22 * A2.x22) % r,
    };
}

node apply(int l, int r)
{
    node lres = E, rres = E;
    while (l <= r)
    {
        if (l % 2 == 0)
            lres = multiply(lres, s[l]);
        l = l / 2;
        if (r % 2 == 1)
            rres = multiply(s[r], rres);
        r = r / 2 - 1;
    }
    return multiply(lres, rres);
}


int main()
{
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> r >> n >> m;

    int full = 1;
    while (full < n)
        full *= 2;

    int x11, x22, x12, x21;
    for (int i = full - 1; i < full + n - 1; i++)
    {
        cin >> x11 >> x12 >> x21 >> x22;
        s[i].x11 = x11 % r;
        s[i].x12 = x12 % r;
        s[i].x21 = x21 % r;
        s[i].x22 = x22 % r;
    }
    for (int i = full + n - 1; i < 2 * full - 1; i++)
        s[i] = E;
    for (int i = full - 2; i >= 0; i--)
        s[i] = multiply(s[2 * i + 1], s[2 * i + 2]);

    int x1, x2;
    for (int i = 0; i < m; i++)
    {
        cin >> x1 >> x2;
        node result = apply(full - 1 + x1 - 1, full - 1 + x2 - 1);
        cout << result.x11 << " " << result.x12 << endl << result.x21 << " " << result.x22 << endl << endl;
    }
    return 0;
}