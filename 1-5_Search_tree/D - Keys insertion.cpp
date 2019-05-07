#include <iostream>
#include <vector>

using namespace std;

struct node
{
    node * left;
    node * right;
    int c;
    int y;
    int size;
    int zero;
    node(int k): left(nullptr), right(nullptr), size(1), y(rand() * RAND_MAX + rand()), c(k), zero(k == 0 ? 1 : 0) {}
};
node * root;
vector<int> result;

int size(node * t)
{
    return t ? t->size : 0;
}
int zero(node * t)
{
    return t ? t->zero : 0;
}
void update(node * t)
{
    if (t)
    {
        t->size = size(t->left) + size(t->right) + 1;
        t->zero = zero(t->left) + zero(t->right) + (t->c ? 0 : 1);
    }
}

pair<node *, node * > split(node * t, int k)
{
    if (k == size(t->left) + 1)
    {
        node * temp = t->right;
        t->right = nullptr;
        update(t);
        return { t, temp };
    }
    if (k > size(t->left) + 1)
    {
        pair<node *, node *> temp = split(t->right, k - size(t->left) - 1);
        t->right = temp.first;
        update(t);
        return { t, temp.second };
    }
    if (k == 0)
        return { nullptr, t };
    pair<node *, node *> temp = split(t->left, k);
    t->left = temp.second;
    update(t);
    return { temp.first, t };
}

node * merge(node * a, node * b)
{
    if (!a) return b;
    if (!b) return a;
    if (a -> y > b -> y)
    {
        a -> right = merge(a -> right, b);
        update(a);
        return a;
    }
    b -> left = merge(a, b -> left);
    update(b);
    return b;
}

node * remove_zero(node * t)
{
    if (t->left && t->left->zero)
        t->left = remove_zero(t->left);
    else if (t->c == 0)
        t = merge(t->left, t->right);
    else
        t->right = remove_zero(t->right);
    update(t);
    return t;
}

void build_result(node * v)
{
    if (!v) return;
    build_result(v->left);
    result.push_back(v->c);
    build_result(v->right);
}

int main()
{
    root = nullptr;
    int n, m, k;
    cin >> n >> m;
    for (int i = 1; i <= n + m; i++)
        root = merge(root, new node(0));
    for (int  i = 1; i <= n; i++)
    {
        cin >> k;
        pair<node *, node *> temp = split(root, k - 1);
        temp.first = merge(temp.first, new node(i));
        temp.second = remove_zero(temp.second);
        root = merge(temp.first, temp.second);
    }

    build_result(root);
    while (result[result.size() - 1] == 0)
        result.pop_back();

    cout << result.size() << endl;
    for (int i : result)
        cout << i << " ";

    return 0;
}