#include <iostream>
#include <vector>

using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    int k;
    int size;
    node(int k) : left(nullptr), right(nullptr), parent(nullptr), k(k), size(1) {};
};
node * root;

int size (node * t)
{
    return t ? t->size : 0;
}

void update_size(node * t)
{
    if (t)
        t->size = size(t->left) + size(t->right) + 1;
}

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

void rotate(node * x)
{
    auto p = x->parent;
    auto g = p->parent;
    if (g)
    {
        if (g->left == p)
            g->left = x;
        else
            g->right = x;
    }
    else
        root = x;

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
    update_size(p);
    update_size(x);
}

node * splay(node * x)
{
    if (!x->parent)
        return x;
    auto p = x->parent;
    auto g = p->parent;
    if (!g)
    {
        // zig
        rotate(x);
        return x;
    }
    if ((p->left == x) == (g->left == p))
        // zig-zig
        rotate(p);
    else
        // zig-zag
        rotate(x);
    rotate(x);
    return splay(x);
}

pair<node *, node * > split(node * t, int k)
{
    if(!t)
        return {nullptr, nullptr};
    if (size(t->left) >= k)
    {
        auto [first, second] = split(t->left, k);
        t->left = second;
        set_parent(second, t);
        set_parent(first, nullptr);
        update_size(t);
        return {first, t};
    }
    auto [first, second] = split(t->right, k - size(t->left) - 1);
    t->right = first;
    set_parent(first, t);
    set_parent(second, nullptr);
    update_size(t);
    return {t, second};
}

node * merge(node * a, node * b)
{
    if (!a) return b;
    if (!b) return a;
    splay(a);
    while (a->right)
        a = a->right;
    splay(a);
    a->right = b;
    set_parent(b, a);
    return a;
}

void print_tree(node * v)
{
    if (!v) return;
    print_tree(v->left);
    cout << v->k << " ";
    print_tree(v->right);
}

int main()
{
    root = nullptr;
    int n, m, l, r;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        root = merge(root, new node(i));
    for (int i = 0; i < m; i++)
    {
        cin >> l >> r;
        auto[u, v] = split(root, l - 1);
        auto[a, b] = split(v, r - l + 1);
        root = merge(merge(a, u), b);
    }
    print_tree(root);
    return 0;
}