#include <iostream>
#include <vector>

using namespace std;
const int N = 1 << 20;
const int SHIFT = 500001;
struct node
{
    int kol;
    int left;
    int right;
    int sum;
    int changed;
};
vector<node> s(2 * N - 1);

void apply(int i)
{
    s[i] = { s[2 * i + 1].kol + s[2 * i + 2].kol,
             s[2 * i + 1].left,
             s[2 * i + 2].right,
             s[2 * i + 1].sum + s[2 * i + 2].sum,
             s[i].changed };
    if (s[2 * i + 1].right == s[2 * i + 2].left && s[2 * i + 2].left  == 1)
        s[i].kol--;
}

void push(int i, int len)
{
    if (s[i].changed >= 0)
    {
        s[2 * i + 1] = s[2 * i + 2] = { s[i].changed, s[i].changed, s[i].changed, s[i].changed * len, s[i].changed };
        s[i].changed = -1;
    }
}

void update(int L, int R, int v, int l, int r, int x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
    {
        s[v] = {x, x, x, x * (r - l), x};
        return;
    }
    push(v, (r - l) / 2);
    int m = (l + r) / 2;
    update(L, R, 2 * v + 1, l, m, x);
    update(L, R, 2 * v + 2, m, r, x);
    apply(v);
}


int main()
{
    int n;
    cin >> n;

    int full = N;
    for (int i = 0; i < 2 * full - 1; i++)
        s[i] = { 0, 0, 0, 0, -1 };

    string str;
    int x1, x2, x;
    for (int i = 0; i < n; i++)
    {
        cin >> str >> x1 >> x2;
        x2 = x1 + x2 - 1;
        x1 += SHIFT;
        x2 += SHIFT;
        x = str[0] == 'W' ? 0 : 1;
        update(x1 + full - 2, x2 + 1 + full - 2, 0, full - 1, 2 * full - 1, x);
        cout << s[0].kol << " " << s[0].sum << endl;
    }

    return 0;
}