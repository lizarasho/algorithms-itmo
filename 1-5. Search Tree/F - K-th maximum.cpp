#include <iostream>
using namespace std;
struct node
{
    node * left;
    node * right;
    long long x;
    long long y;
    long long child;
    node(int x): left(nullptr), right(nullptr), x(x), y(rand() * RAND_MAX + rand()), child(1) {}
};
node * root;

long long child (node * t)
{
    return t ? t->child : 0;
}

pair<node *, node * > split(node * t, long long k)
{
    if(!t)
        return { nullptr, nullptr };
    if (k > t -> x)
    {
        pair<node *, node *> temp = split(t -> right, k);
        t -> right = temp.first;
        t->child = child(t->left) + child(t->right) + 1;
        return { t, temp.second };
    }
    pair<node *, node *> temp = split(t -> left, k);
    t -> left = temp.second;
    t->child = child(t->left) + child(t->right) + 1;
    return { temp.first, t };
}

node * merge(node * a, node * b)
{
    if (!a)
        return b;
    if (!b)
        return a;
    if (a -> y > b -> y)
    {
        a -> right = merge(a -> right, b);
        a->child = child(a->left) + child(a->right) + 1;
        return a;
    }
    b -> left = merge(a, b -> left);
    b->child = child(b->left) + child(b->right) + 1;
    return b;
}

node * insert (node * t, node * k)
{
    pair<node *, node *> temp = split(t, k -> x);
    temp.first = merge(temp.first, k);
    return merge(temp.first, temp.second);
}


node * find(node * v, long long k)
{
    if (!v)
        return v;
    if (v -> x == k)
        return v;
    return (k > v -> x) ? find(v -> right, k) : find(v -> left, k);
}

node * min_more(node * v, long long k)
{
    if (!v)
        return v;
    if (k < v -> x)
    {
        node * nd = min_more(v -> left, k);
        return nd  ? nd : v;
    }
    return min_more(v -> right, k);
}

bool exists(long long x)
{
    return find(root, x);
}

node * remove (int x)
{
    pair<node *, node *> temp1 = split(root, x);
    pair<node *, node *> temp2 = split(temp1.second, x + 1);
    return merge(temp1.first, temp2.second);
}

node * max_less(node * v, long long k)
{
    if (!v)
        return v;
    if (k > v -> x)
    {
        node * nd = max_less(v -> right, k);
        return nd ? nd : v;
    }
    return max_less(v -> left, k);
}

long long max_k(node * v, long long k)
{
    if (child(v->right) + 1 == k)
        return v->x;

    if (!v->right)
        return max_k(v->left, k - 1);

    if (v->right->child >= k)
        return max_k(v->right, k);
    return max_k(v->left, k - v->right->child - 1);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    root = nullptr;
    long long n, x, k;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> k;
        if (x == 1)
            if (!exists(k))
                root = insert(root, new node(k));
        if (x == -1)
            root = remove(k);
        if (x == 0)
            cout << max_k(root, k) << endl;
    }
    return 0;
}