#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    int size;
    bool set;
    bool my_set;
    node() : left(nullptr), right(nullptr), parent(nullptr), size(1), set(false), my_set(false) {};
};
vector<node *> pointer;
vector<vector<int>> edge;
vector<bool> was;
int n;

void update(node * t)
{
    if (t)
    {
        t->size = 1;
        t->set = false;
        if (t->left)
        {
            t->size += t->left->size;
        }
        if (t->right)
        {
            t->size += t->right->size;
        }
    }
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

void set (node * x)
{
    x->set = x->my_set = true;
}

void push(node * x)
{
    if (x->set)
    {
        x->set = false;
        x->my_set = true;
        if (x->left)
        {
            set(x->left);
        }
        if (x->right)
        {
            set(x->right);
        }
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

void build(node * x, node * y)
{
    node * lca = LCA(x, y);
    if (lca != x && lca != y)
    {
        splay(x);
        set(x);
        splay(lca);
        set(lca->left);
        return;
    }
    node *z = (x == lca) ? y : x;
    expose(z);
    splay(lca);
    set(lca->left);
}

void create_dfs(int u)
{
    was[u] = true;
    for (int v : edge[u])
    {
        if (!was[v])
        {
            link(pointer[v], pointer[u]);
            create_dfs(v);
        }
    }
}

void push_dfs(node * u)
{
    if (!u || !u->set)
        return;
    push(u);
    push_dfs(u->left);
    push_dfs(u->right);
}

int main()
{
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
    create_dfs(0);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        build(pointer[u - 1], pointer[v - 1]);
    }

    for (int i = 0; i < n; i++)
        push_dfs(pointer[i]);

    int ans = 0;
    for (int i = 1; i < n; i++)
        if (!pointer[i]->my_set)
            ans++;

    cout << ans << endl;
    return 0;
}