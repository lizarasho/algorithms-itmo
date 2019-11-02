#include <iostream>

using namespace std;

struct node
{
    node * left;
    node * right;
    int key;
    node(int x) : left(nullptr), right(nullptr), key(x) {};
};
node * root;

node * insert(node * v, int x)
{
    if (!v)
    {
        v = new node(x);
        return v;
    }
    if (v -> key == x)
        return v;
    if (x > v -> key)
        v -> right = insert(v -> right, x);
    if (x < v -> key)
        v -> left = insert(v -> left, x);
    return v;
}

node * min(node * v)
{
    if (!v -> left)
        return v;
    return min(v -> left);
}

node * max(node * v)
{
    if (!v -> right)
        return v;
    return max(v -> right);
}


node * remove(node * v, int x)
{
    if (!v)
        return v;
    if (x > v -> key)
        v -> right = remove(v -> right, x);
    else if (x < v -> key)
        v -> left = remove(v -> left, x);
    else
    {
        if (v -> left && v -> right)
        {
            v -> key = min(v -> right) -> key;
            v -> right = remove(v -> right, v -> key);
        } else
        if (v -> left)
            v = v -> left;
        else
            v = v -> right;
    }
    return v;

}

node * find(node * v, int x)
{
    if (!v)
        return v;
    if (v -> key == x)
        return v;
    return (x > v -> key) ? find(v -> right, x) : find(v -> left, x);
}

node * min_more(node * v, int x)
{
    if (!v)
        return v;
    if (x < v -> key)
    {
        node * nd = min_more(v -> left, x);
        return nd ? nd : v;
    }
    return min_more(v -> right, x);
}

node * max_less(node * v, int x)
{
    if (!v)
        return v;
    if (x > v -> key)
    {
        node * nd = max_less(v -> right, x);
        return nd ? nd : v;
    }
    return max_less(v -> left, x);
}

bool exists(int x)
{
    return find(root, x);
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
            root = insert(root, x);
        else if (s[0] == 'e')
        {
            if (exists(x))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if (s[0] == 'd')
            root = remove(root, x);
        else if (s[0] == 'n')
        {
            node * nd = min_more(root, x);
            if (nd)
                cout << nd -> key << endl;
            else
                cout << "none" << endl;
        }
        else if (s[0] == 'p')
        {
            node * nd = max_less(root, x);
            if (nd)
                cout << nd -> key << endl;
            else
                cout << "none" << endl;
        }
    }
    return 0;
}