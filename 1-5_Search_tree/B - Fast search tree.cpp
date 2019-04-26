#include <iostream>

using namespace std;

struct node
{
    node * left;
    node * right;
    int x;
    int y;
    node(int x) : left(nullptr), right(nullptr), x(x), y(rand() * RAND_MAX + rand()) {};
};
node * root;

pair<node *, node * > split(node * t, int k)
{
    if(!t)
        return { nullptr, nullptr };
    if (k > t -> x)
    {
        pair<node *, node *> temp = split(t -> right, k);
        t -> right = temp.first;
        return { t, temp.second };
    }
    pair<node *, node *> temp = split(t -> left, k);
    t -> left = temp.second;
    return { temp.first, t };
}

node * merge(node * a, node * b)
{
    if (!a) return b;
    if (!b) return a;
    if (a -> y > b -> y)
    {
        a -> right = merge(a -> right, b);
        return a;
    }
    b -> left = merge(a, b -> left);
    return b;
}

node * insert (node * t, node * k)
{
    pair<node *, node *> temp = split(t, k -> x);
    temp.first = merge(temp.first, k);
    return merge(temp.first, temp.second);
}

node * find(node * v, int k)
{
    if (!v)
        return v;
    if (v -> x == k)
        return v;
    return (k > v -> x) ? find(v -> right, k) : find(v -> left, k);
}

node * remove (int x)
{
    pair<node *, node *> temp1 = split(root, x);
    pair<node *, node *> temp2 = split(temp1.second, x + 1);
    return merge(temp1.first, temp2.second);
}

bool exists(int x)
{
    return find(root, x);
}

node * min_more(node * v, int k)
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

node * max_less(node * v, int k)
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
        }
        else if (s[0] == 'd')
            root = remove(x);
        else if (s[0] == 'n')
        {
            node * next = min_more(root, x);
            if (next)
                cout << next -> x << endl;
            else
                cout << "none" << endl;

        }
        else if (s[0] == 'p')
        {
            node * prev = max_less(root, x);
            if (prev)
                cout << prev -> x << endl;
            else
                cout << "none" << endl;

        }
    }
    return 0;
}