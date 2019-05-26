#include <iostream>
#include <vector>

using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    int size;
    node() : left(nullptr), right(nullptr), parent(nullptr), size(1) {};
};
vector<node *> pointer;
vector<int> group;
int k;

void set_parent(node * x, node * p)
{
    if (x)
        x->parent = p;
}

void update_parent(node * x)
{
    set_parent(x->left, x);
    set_parent(x->right, x);
}

int size(node * x)
{
    return x ? x->size : 0;
}

void update(node * x)
{
    if (x)
        x->size = size(x->left) + size(x->right) + 1;
}

bool is_root(node * x)
{
    return x && (x->parent == nullptr || (x->parent->left != x && x->parent->right != x));
}

void rotate(node * x)
{
    auto p = x->parent;
    auto g = p->parent;
    if (!is_root(p))
    {
        if (g->left == p)
            g->left = x;
        else
            g->right = x;
    }
    if (p->left == x)
    {
        p->left = x->right;
        x->right = p;
    } else
    {
        p->right = x->left;
        x->left = p;
    }
    update_parent(x);
    update_parent(p);
    set_parent(x, g);
    update(p);
    update(x);
    update(g);
}


node * splay(node * x)
{
    if (is_root(x))
    {
        update(x);
        return x;
    }
    auto p = x->parent;
    auto g = p->parent;
    if (is_root(p))
    {
        // zig
        rotate(x);
        return x;
    }
    //                                      zig-zig   zig-zag
    rotate((p->left == x) == (g->left == p)  ?  p   :   x    );
    rotate(x);
    return splay(x);
}

node * get_splay_root(node * x)
{
    while (x && x->parent && (x->parent->left == x || x->parent->right == x))
        x = x->parent;
    return x;
}

node * expose(node * x)
{
    node * last = nullptr;
    for (auto y = x; y; y = y->parent)
    {
        splay(y);
        y->left = last;
        update(y);
        last = y;
    }
    splay(x);
    return last;
}

void link(node * x, node * y)
{
    expose(x);
    x->parent = y;
}

int get_index(node * v)
{
    if (!v) return 0;
    int ans = size(v->left);

    while (!is_root(v))
    {
        if (v == v->parent->right)
            ans += size(v->parent->left) + 1;
        v = v->parent;
    }
    return ans;
}

long long answer()
{
    long long ans = 0;
    for (int i = 0; i < k; i++)
        expose(pointer[group[i]]);

    for (int i = 0; i < k; i++)
        if (get_index(pointer[group[i]]) == 0)
            ans += get_splay_root(pointer[group[i]])->size;

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, g;
    cin >> n;
    pointer.resize(n);
    group.resize(n);
    for (int i = 0; i < n; i++)
        pointer[i] = new node();

    for (int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        if (p == -1)
            continue;
        link(pointer[i], pointer[p - 1]);
    }

    cin >> g;
    for (int i = 0; i < g; i++)
    {
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int p;
            cin >> p;
            group[j] = p - 1;
        }
        cout << answer() << '\n';
        group.clear();
    }

    return 0;
}