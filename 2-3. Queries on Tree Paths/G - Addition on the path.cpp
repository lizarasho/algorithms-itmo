#include <iostream>
#include <vector>

using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    int size;
    long long d;
    long long my_d;
    node() : left(nullptr), right(nullptr), parent(nullptr), size(1), d(0), my_d(0) {};
};
vector<node *> pointer;
vector<vector<int>> edge;
vector<bool> was;

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

void add(node * x, long long d)
{
    if (x)
    {
        x->d += d;
        x->my_d += d;
    }
}

void update(node * x)
{
    if (x)
    {
        x->size = 1 ;
        if (x->left)
            x->size += x->left->size;
        if (x->right)
            x->size += x->right->size;
        x->d = 0;
    }
}

void push(node * x)
{
    if (x->d)
    {
        add(x->left, x->d);
        add(x->right, x->d);
        x->d = 0;
    }
}

bool is_root(node * x)
{
    return x && (x->parent == nullptr || (x->parent->left != x && x->parent->right != x));
}

void rotate(node * x)
{
    auto p = x->parent;
    auto g = p->parent;
    if (g)
        push(g);
    push(p);
    push(x);
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
        push(x);
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

node * LCA(node * x, node * y)
{
    expose(x);
    return expose(y);
}

void build(int u, int v, unsigned long long d)
{
    node * x = pointer[u];
    node * y = pointer[v];
    node * lca = LCA(x, y);
    if (lca != x && lca != y)
    {
        splay(x);
        add(x, d);
    } else
    {
        expose((x == lca) ? y : x);
    }
    splay(lca);
    add(lca->left, d);
    lca->my_d += d;
}

void dfs(int u)
{
    was[u] = true;
    for (int v : edge[u])
    {
        if (!was[v])
        {
            link(pointer[v], pointer[u]);
            dfs(v);
        }
    }
}

long long query(int x)
{
    splay(pointer[x]);
    return pointer[x]->my_d;
}

int main()
{
    {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    int n;
    cin >> n;
    pointer.resize(n);
    edge.resize(n);
    was.resize(n);

    for (int i = 0; i < n; i++)
        pointer[i] = new node();

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        edge[u - 1].push_back(v - 1);
        edge[v - 1].push_back(u - 1);
    }
    dfs(0);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int u, v;
            long long d;
            cin >> u >> v >> d;
            build(u - 1, v - 1, d);
        } else if (c == '?')
        {
            int u;
            cin >> u;
            cout << query(u - 1) << '\n';
        }
    }
    return 0;
}