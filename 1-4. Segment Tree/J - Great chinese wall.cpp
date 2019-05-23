#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1 << 20;
int full;
struct node
{
    int min;
    int index;
};
vector<node> s(2 * N - 1);


void push(int v)
{
    s[2 * v + 1].min = max(s[v].min, s[2 * v + 1].min);
    s[2 * v + 2].min = max(s[v].min, s[2 * v + 2].min);
}

void apply(int v)
{
    s[v] = (s[2 * v + 1].min <= s[2 * v + 2].min) ? s[2 * v + 1] : s[2 * v + 2];
}


void update_set(int L, int R, int v, int l, int r, int x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
        if (s[v].min >= x)
            return;
        else
        {
            s[v].min = x;
            if (v < full - 1)
                s[v].index = s[2 * v + 1].min <= s[2 * v + 2].min ? s[2 * v + 1].index : s[2 * v + 2].index;
            return;
        }
    int m = (l + r) / 2;
    push(v);
    update_set(L, R, 2 * v + 1, l, m, x);
    update_set(L, R, 2 * v + 2, m, r, x);
    apply(v);
}

node result(int L, int R, int v, int l, int r)
{
    if (R <= l || r <= L)
        return { INT_MAX, 0 };
    if (l >= L && r <= R)
        return s[v];
    int m = (l + r) / 2;
    push(v);
    node minL = result(L, R, 2 * v + 1, l, m);
    node minR = result(L, R, 2 * v + 2, m, r);
    return minL.min <= minR.min ? minL : minR;
}

int main()
{
    int n, m;
    cin >> n >> m;

    full = 1;
    while (full < n)
        full *= 2;

    for (int i = full - 1; i < full + n - 1; i++)
        s[i] = { 0, i - full + 2 };
    for (int i = full + n - 1; i < 2 * full - 1; i++)
        s[i] = { INT_MAX, i - full + 2 };
    for (int i = full - 2; i >= 0; i--)
        s[i] = { min(s[2 * i + 1].min, s[2 * i + 2].min), s[2 * i + 1].index };

    string str;
    int x1, x2;
    int val;
    for (int i = 0; i < m; i++)
    {
        cin >> str;
        if (str[0] == 'd')
        {
            cin >> x1 >> x2 >> val;
            update_set(x1 + full - 2, x2 + full - 1, 0, full - 1, 2 * full - 1, val);
        }
        if (str[0] == 'a')
        {
            cin >> x1 >> x2;
            node res = result(x1 + full - 2, x2 + full - 1, 0, full - 1, 2 * full - 1);
            cout <<  res.min << " " << res.index << endl;
        }
    }

    return 0;
}