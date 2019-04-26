#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
struct node
{
    node * left;
    node * right;
    node * parent;
    int letter;
    int all_letters;
    int size;
    int all_size;
    int y;
    node(int n, char c): left(nullptr), right(nullptr), parent(nullptr), letter(1 << (c - 'a')),
                         all_letters(1 << (c - 'a')), size(n), all_size(n), y(rand() * RAND_MAX + rand()) {}
    node(int n, int c): left(nullptr), right(nullptr), parent(nullptr), letter(c),
                         all_letters(c), size(n), all_size(n), y(rand() * RAND_MAX + rand()) {}
};
node * root;
node * last;
vector<node *> tree;

int all_size(node * t)
{
    return t ? t->all_size : 0;
}

int all_letters(node * t)
{
    return t ? t->all_letters : 0;
}
void update(node * t)
{
    if (t)
    {
        t->all_letters = all_letters(t->left) | all_letters(t->right) | (t->letter);
        t->all_size = all_size(t->left) + all_size(t->right) + (t->size);
    }
}

pair<node *, node * > split(node * t, int k)
{
    if(!t) return {nullptr, nullptr};

    int ls = all_size(t->left);

    if (k > ls + t->size)
    {
        pair<node *, node *> temp = split(t->right, k - ls - t->size);
        t->right = temp.first;
        update(t);
        return {t, temp.second};
    }

    if (k == ls + t->size)
    {
        node * temp = t->right;
        t->right = nullptr;
        update(t);
        return {t, temp};
    }

    if (k - ls >= 0)
    {
        node * first = new node(k - ls, t->letter);
        node * second = new node(t->size + ls - k, t->letter);
        first->left = t->left;
        second->right = t->right;
        if (k == 0)
            first = nullptr;
        else if (k - ls == 0)
            first = t->left;
        update(first);
        update(second);
        return {first, second};
    }
    pair<node *, node *> temp = split(t->left, k);
    t->left = temp.second;
    update(t);
    return {temp.first, t};
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

void insert(int index, int number, char letter)
{
    pair<node *, node *> temp = split(root, index - 1);
    root = merge(merge(temp.first, new node(number, letter)), temp.second);
}

node * remove(int index, int number)
{
    pair<node *, node *> temp1 = split(root, index - 1);
    return merge(temp1.first, split(temp1.second, number).second);
}

int query(int index1, int index2)
{
    pair<node *, node *> temp1 = split(root, index1 - 1);
    pair<node *, node *> temp2 = split(temp1.second, index2 - index1 + 1);
    int k = temp2.first->all_letters;
    int ans = 0;
    while (k > 0)
    {
        ans++;
        k = k & (k - 1);
    }
    temp1.second = merge(temp2.first, temp2.second);
    root = merge(temp1.first, temp1.second);
    return ans;
}

void insert_new(node * last, node * t)
{
    while (last != root && last->y > t->y)
        last = last->parent;
    if (last == root && last->y > t->y)
    {
        node * temp = root;
        temp->parent = t;
        t->left = temp;
        root = t;
        return;
    }
    if (!last->right)
    {
        last->right = t;
        t->parent = last;
        return;
    }
    t->left = last->right;
    last->right->parent = t;
    last->right = t;
    t->parent = last;
}

void update_tree(node * t)
{
    if (!t) return;
    update_tree(t->left);
    update_tree(t->right);
    update(t);
}

void in_order (node * t)
{
    if (!t) return;
    in_order(t->left);
    tree.push_back(new node(t->size, t->letter));
    in_order(t->right);
}

void rebuild()
{
    tree.clear();
    in_order(root);
    int i = 0;
    int k = 0;
    while (k < tree.size() - 1)
    {
        i = k;
        while (i < tree.size() - 1 && tree[i]->letter == tree[i + 1]->letter)
        {
            tree[i + 1] = new node(tree[i]->size + tree[i + 1]->size, tree[i]->letter);
            tree[i] = nullptr;
            i++;
        }
        k = max(k + 1, i);
    }

    k = 0;
    while (!tree[k])
        k++;
    root = last = tree[k];
    k++;
    while (k < tree.size())
    {
        if (tree[k])
        {
            insert_new(last, tree[k]);
            last = tree[k];
        }
        k++;
    }
    update_tree(root);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    root = nullptr;
    int n;
    int index, number;
    int index1, index2;
    char letter;
    char c;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        if (i % 777 == 0)
            rebuild();
        cin >> c;
        if (c == '+')
        {
            cin >> index >> number >> letter;
            insert(index, number, letter);
        } else if (c == '-')
        {
            cin >> index >> number;
            root = remove(index, number);
        } else
        {
            cin >> index1 >> index2;
            cout << query(index1, index2) << endl;
        }
    }
    return 0;
}