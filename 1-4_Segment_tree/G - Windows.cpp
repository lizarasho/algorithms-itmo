#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1 << 19;
const int MAX = 200000;
struct node
{
    int max;
    int index;
    int add;
};
vector<node> tree(2 * N - 1);
struct rect
{
    int x;
    int y1;
    int y2;
    bool open;
};
vector<rect> queries;
bool cmp(rect a, rect b)
{
    return (a.x == b.x) ? a.open > b.open : a.x < b.x;
}

void push(int i)
{
    tree[2 * i + 1].max += tree[i].add;
    tree[2 * i + 2].max += tree[i].add;
    tree[2 * i + 1].add += tree[i].add;
    tree[2 * i + 2].add += tree[i].add;
    tree[i].add = 0;
}

void apply(int v)
{
    tree[v].max = max(tree[2 * v + 1].max, tree[2 * v + 2].max);
    tree[v].index = tree[2 * v + 1].max > tree[2 * v + 2].max ? tree[2 * v + 1].index : tree[2 * v + 2].index;
}

void update_add(int L, int R, int v, int l, int r, int x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
    {
        tree[v].add += x;
        tree[v].max += x;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update_add(L, R, 2 * v + 1, l, m, x);
    update_add(L, R, 2 * v + 2, m, r, x);
    apply(v);
}

void fill(rect cur)
{
    if (cur.open)
        update_add(cur.y1 + N - 1, cur.y2 + N, 0, N - 1, 2 * N - 1, 1);
    else
        update_add(cur.y2 + N - 1, cur.y1 + N, 0, N - 1, 2 * N - 1, -1);
}

int main()
{
    int n;
    cin >> n;
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        queries.push_back({ x1 + MAX, y1 + MAX, y2 + MAX, true });
        queries.push_back({ x2 + MAX, y2 + MAX, y1 + MAX, false });
    }

    sort(queries.begin(), queries.end(), cmp);

    for (int i = N - 1; i < 2 * N - 1; i++)
        tree[i] = { 0, i - N + 1, 0 };
    for (int i = N - 2; i >= 0; i--)
        tree[i] = { 0, tree[2 * i + 1].index, 0 };

    int x = 0, y = 0, max = 0;
    for (auto query : queries)
    {
        fill(query);
        node res = tree[0];
        if (res.max > max)
        {
            max = res.max;
            y = res.index;
            x = query.x;
        }
    }
    cout << max << endl << x - MAX << " " << y - MAX;
    return 0;
}