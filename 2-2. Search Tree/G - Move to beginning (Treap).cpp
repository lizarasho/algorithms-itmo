#include <iostream>
using namespace std;
struct node
{
    node * left;
    node * right;
    int c;
    int y;
    int size;
    node(int c): left(nullptr), right(nullptr), c(c), y(rand() * RAND_MAX + rand()), size(1) {}
};
node * root;

int size (node * t)
{
    return t ? t->size : 0;
}

void apply(node * t)
{
    t->size = size(t->left) + size(t->right) + 1;
}

pair<node *, node * > split(node * t, int k)
{
    if(!t)
        return { nullptr, nullptr };
    if (size(t->left) >= k)
    {
        pair<node *, node *> temp = split(t->left, k);
        t->left = temp.second;
        apply(t);
        return { temp.first, t };
    }
    pair<node *, node *> temp = split(t->right, k - size(t->left) - 1);
    t->right = temp.first;
    apply(t);
    return { t, temp.second };

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
        apply(a);
        return a;
    }
    b -> left = merge(a, b -> left);
    apply(b);
    return b;
}

void print_tree(node * v)
{
    if (!v)
        return;
    print_tree(v->left);
    cout << v->c << " ";
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
        pair<node *, node *> temp1 = split(root, l - 1);
        pair<node *, node *> temp2 = split(temp1.second, r - l + 1);
        root = merge(merge(temp2.first, temp1.first), temp2.second);
    }
    print_tree(root);
    return 0;
}