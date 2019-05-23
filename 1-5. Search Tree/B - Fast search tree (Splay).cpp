#include <iostream>

using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    int x;
    node(int x) : left(nullptr), right(nullptr), parent(nullptr), x(x) {};
};
node * root;

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
    x->parent = g;
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

node * find(node * v, int k)
{
    if (!v)
        return v;
    if (v->x == k)
        return splay(v);
    if (k > v->x && v->right)
        return find(v->right, k);
    if (k < v->x && v->left)
        return find(v->left, k);
    return splay(v);
}

pair<node *, node * > split(node * t, int k)
{
    if(!t)
        return {nullptr, nullptr};
    root = find(root, k);
    if (root->x < k)
    {
        set_parent(root->right, nullptr);
        auto v = root->right;
        root->right = nullptr;
        return {root, v};
    }
    set_parent(root->left, nullptr);
    auto u = root->left;
    root->left = nullptr;
    return {u, root};
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

bool exists(int x)
{
    return find(root, x) && root->x == x;
}

node * insert (node * t, node * k)
{
    if (exists(k->x))
        return root;
    auto [u, v] = split(t, k->x);
    return merge(merge(u, k), v);
}

node * remove (int x)
{
    if (!exists(x))
        return root;
    root = find(root, x);
    auto u = root->left;
    auto v = root->right;
    set_parent(root->left, nullptr);
    set_parent(root->right, nullptr);
    return merge(u, v);
}

node * min_more(node * v, int k)
{
    if (!v)
        return v;
    if (k < v->x)
    {
        auto u = min_more(v->left, k);
        return u ? splay(u) : splay(v);
    }
    return min_more(v->right, k);
}

node * max_less(node * v, int k)
{
    if (!v)
        return v;
    if (k > v->x)
    {
        auto u = max_less(v->right, k);
        return u ? splay(u) : splay(v);
    }
    return max_less(v->left, k);
}


int main()
{
    root = nullptr;
    string s;
    int x;

    while (cin >> s)
    {
        cin >> x;
        if (s[0] == 'i')
            root = insert(root, new node(x));
        else if (s[0] == 'e')
        {
            if (exists(x))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        } else if (s[0] == 'd')
            root = remove(x);
        else if (s[0] == 'n')
        {
            node * next = min_more(root, x);
            if (next)
                cout << next->x << endl;
            else
                cout << "none" << endl;

        } else if (s[0] == 'p')
        {
            node * prev = max_less(root, x);
            if (prev)
                cout << prev->x << endl;
            else
                cout << "none" << endl;
        }
    }
    return 0;
}