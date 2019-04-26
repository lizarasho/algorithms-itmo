#include <iostream>
using namespace std;
struct node
{
    node * left;
    node * right;
    long long x;
    long long y;
    long long sum;
    node(long long x, long long sum) : left(nullptr), right(nullptr), x(x), y(rand() * RAND_MAX + rand()), sum(sum) {};
};
node * root;
const int MOD = 1000000000;

long long sum (node * t)
{
    return t == nullptr ? 0 : t->sum;
}

void update (node * t)
{
    t->sum = sum(t->left) + sum(t->right) + t->x;
}

pair<node *, node * > split(node * t, long long k)
{
    if(!t)
        return { nullptr, nullptr };
    if (k > t -> x)
    {
        pair<node *, node *> temp = split(t -> right, k);
        t -> right = temp.first;
        update(t);
        return make_pair(t, temp.second);
    }
    pair<node *, node *> temp = split(t -> left, k);
    t -> left = temp.second;
    update(t);
    return make_pair(temp.first, t);
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
        update(a);
        return a;
    }
    b -> left = merge(a, b -> left);
    update(b);
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
        return nd ? nd : v;
    }
    return min_more(v -> right, k);
}

bool exists(long long x)
{
    return find(root, x);
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

long long sum_lr(long long l, long long r)
{
    node * nd_left = min_more(root, l - 1);
    node * nd_right = max_less(root, r + 1);
    if (!nd_left || !nd_right)
        return 0;
    if (nd_left->x > nd_right->x)
        return 0;
    pair <node*, node*> temp1 = split(root, nd_left->x);
    pair <node*, node*> temp2 = split(temp1.second, nd_right -> x + 1);
    long long x = temp2.first->sum;
    root = merge(temp1.first, merge(temp2.first, temp2.second));
    return x;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    root = nullptr;
    long long n, l, r, x;
    char c;
    cin >> n;
    bool actual = false;
    long long last = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        if (c == '+')
        {
            cin >> x;
            if (actual)
                x = (x + last) % MOD;
            if (!exists(x))
                root = insert(root, new node(x, x));
            actual = false;
        } else if (c == '?')
        {
            cin >> l >> r;
            last = sum_lr(l, r);
            cout << last << endl;
            actual = true;
        }
    }
    return 0;
}