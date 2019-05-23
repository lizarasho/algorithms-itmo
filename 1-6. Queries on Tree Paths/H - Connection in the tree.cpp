#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    pair<int, int> edge;
    int size;
    node(int u, int v) : left(nullptr), right(nullptr), parent(nullptr), edge({u, v}), size(1) {};
};

map<pair<int, int>, node *> edge;
vector<node *> pointer;

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

void move_to_root(node * x)
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
    update_size(g);
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
        move_to_root(x);
        return x;
    }
    //                                          zig-zig   zig-zag
    move_to_root((p->left == x) == (g->left == p)   ?   p   :   x);
    move_to_root(x);
    return splay(x);
}


pair<node *, node * > split(node * t, int k)
{
    if(!t) return {nullptr, nullptr};
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

int get_index(node * v)
{
    if (!v) return 0;
    int ans = size(v->left);
    while (v->parent)
    {
        if (v == v->parent->right)
            ans += size(v->parent->left) + 1;
        v = v->parent;
    }
    return ans;
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
    update_size(a);
    return a;
}

node * get_root(node * v)
{
    if (!v) return v;
    while (v->parent)
        v = v->parent;
    return v;
}

node * first(node * v)
{
    if (!v) return v;
    while (v->left)
        v = v->left;
    return v;
}

node * last(node * v)
{
    if (!v) return v;
    while (v->right)
        v = v->right;
    return v;
}

void cut(int i, int j)
{
    // AuvBvuC -> AC, B
    auto uv = edge[{i, j}];
    auto vu = edge[{j, i}];
    edge.erase({i, j});
    edge.erase({j, i});

    if (get_index(vu) < get_index(uv))
        swap(uv, vu);

    auto [A, BC] = split(get_root(uv), get_index(uv));
    node * au = last(A);
    BC = split(BC, 1).second;

    auto [B, C] = split(BC, get_index(vu));
    node * vc = first(B);
    node * cv = (vc) ? edge[{vc->edge.second, vc->edge.first}] : nullptr;
    node * dv = last(B);
    C = split(C, 1).second;
    node * ub = first(C);
    node * bu = (ub) ? edge[{ub->edge.second, ub->edge.first}] : nullptr;

    pointer[uv->edge.second] = dv ? dv : cv;
    pointer[uv->edge.first] = au ? au : bu;

    auto result = merge(A, C);
}


void link(int i, int j)
{
    node * u = pointer[i];
    node * v = pointer[j];

    // AD, CB -> AuvBCvuD

    auto [A, D] = split(get_root(u), get_index(u) + 1);
    auto [C, B] = split(get_root(v), get_index(v) + 1);
    auto uv = new node(i, j);
    auto vu = new node(j, i);

    if (!v)
        pointer[j] = uv;
    if (!u)
        pointer[i] = vu;

    edge.insert({{i, j}, uv});
    edge.insert({{j, i}, vu});

    auto Auv = merge(A, uv);
    auto vuD = merge(vu, D);
    auto AuvB = merge(Auv, B);
    auto CvuD = merge(C, vuD);
    merge(AuvB, CvuD);
}

bool connected (int i, int j)
{
    auto u_root = get_root(pointer[i]);
    auto v_root = get_root(pointer[j]);
    return u_root && v_root && u_root == v_root;
}

int main()
{
    int n, m;
    cin >> n >> m;
    pointer.resize(n);
    for (int i = 0; i < n; i++)
        pointer[i] = nullptr;

    for (int i = 0; i < m; i++)
    {
        string s;
        int u, v;
        cin >> s >> u >> v;
        if (s == "link")
            link(u - 1, v - 1);
        else if (s == "cut")
            cut(u - 1, v - 1);
        else if (s == "connected")
            cout << connected(u - 1, v - 1) << '\n';
    }
    return 0;
}