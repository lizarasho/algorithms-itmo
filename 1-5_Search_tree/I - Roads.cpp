#include <iostream>
#include <vector>
using namespace std;

struct node
{
    node * left;
    node * right;
    node * parent;
    int c;
    int y;
    int size;
    bool cycle;
    node(int c): left(nullptr), right(nullptr), parent(nullptr), size(1), y(rand() * RAND_MAX + rand()), c(c), cycle(false) {}
};
vector<node * > nodes;

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
        return {nullptr, nullptr};
    if (size(t->left) >= k)
    {
        auto [first, second] = split(t->left, k);
        t->left = second;
        if (second)
            second->parent = t;
        apply(t);
        return {first, t};
    }
    auto [first, second] = split(t->right, k - size(t->left) - 1);
    t->right = first;
    if (first)
        first->parent = t;
    apply(t);
    return {t, second};
}

node * merge(node * a, node * b)
{
    if (!a)
        return b;
    if (!b)
        return a;
    if (a -> y > b -> y)
    {
        node * temp = merge(a -> right, b);
        a->right = temp;
        temp->parent = a;
        a->size = size(a->left) + size(a->right) + 1;
        return a;
    }
    node * temp = merge(a, b -> left);
    b->left = temp;
    temp->parent = b;
    b->size = size(b->left) + size(b->right) + 1;
    return b;
}

void reverse(node * v)
{
    if (!v)
        return;
    node * temp = v->left;
    v->left = v->right;
    v->right = temp;
    reverse(v->left);
    reverse(v->right);
}

node * root_of(node * k)
{
    while (k->parent != nullptr)
        k = k->parent;
    return k;
}

pair<node *, node *> get_ends(node * k)
{
    node * node1;
    node * node2;
    node2 = node1 = k;
    while (node1->left)
        node1 = node1->left;
    while (node2->right)
        node2 = node2->right;
    return {node1, node2};
}


void insert(int i, int j)
{
    node * s = nodes[i];
    node * t = nodes[j];
    node * s_root = root_of(s);
    node * t_root = root_of(t);
    if (s_root == t_root)
    {
        pair<node *, node *> ends = get_ends(s_root);

        if ((ends.first == s && ends.second == t)
            || (ends.first == t && ends.second == s))
            s_root->cycle = true;
        return;
    }
    pair<node *, node *> s_ends = get_ends(s_root);
    pair<node *, node *> t_ends = get_ends(t_root);
    if (s_ends.second == s && t_ends.first == t)
        merge(s_root, t_root);
    else if (s_ends.first == s && t_ends.second == t)
        merge(t_root, s_root);
    else if (s_ends.first == s && t_ends.first == t)
    {
        reverse(s_root);
        merge(s_root, t_root);
    }
    else if (s_ends.second == s && t_ends.second == t)
    {
        reverse(t_root);
        merge(s_root, t_root);
    }
}

int find_number(node * v)
{
    int ans = size(v->left);
    while (v->parent != nullptr)
    {
        if (v == v->parent->right)
            ans += size(v->parent->left) + 1;
        v = v->parent;
    }
    return ans;
}

void remove(int i, int j)
{

    node * s = nodes[i];
    node * t = nodes[j];
    node * s_root = root_of(s);
    pair<node *, node *> s_ends = get_ends(s_root);
    if (s_root->cycle)
    {
        s_root->cycle = false;
        if ((s_ends.first == s && s_ends.second == t)
            || (s_ends.second == s && s_ends.first == t))
            return;
        int s_num = find_number(s);
        int t_num = find_number(t);
        if (s_num + 1 == t_num)
        {
            auto [first, second] = split(s_root, t_num);
            first->parent = second->parent = nullptr;
            node * i_root = root_of(nodes[i]);
            node * j_root = root_of(nodes[j]);
            reverse(i_root);
            reverse(j_root);
            merge(i_root, j_root);
        }
        else
        {
            auto [first, second] = split(s_root, s_num);
            first->parent = second->parent = nullptr;
            node * i_root = root_of(nodes[i]);
            node * j_root = root_of(nodes[j]);
            reverse(i_root);
            reverse(j_root);
            merge(j_root, i_root);
        }
        root_of(nodes[i])->cycle =
        root_of(nodes[j])->cycle = false;
        return;
    }
    int s_num = find_number(s);
    int t_num = find_number(t);
    if (s_num + 1 == t_num)
    {
        auto [first, second] = split(s_root, t_num);
        first->parent = second->parent = nullptr;
    } else
    {
        auto [first, second] = split(s_root, s_num);
        first->parent = second->parent = nullptr;
    }
}


int query(int i, int j)
{

    if (i == j)
        return 0;
    node * s = nodes[i];
    node * t = nodes[j];
    node * s_root = root_of(s);
    node * t_root = root_of(t);
    if (s_root != t_root)
        return -1;
    int s_num = find_number(s);
    int t_num = find_number(t);
    if (s_root->cycle == 0)
        return abs(t_num - s_num) - 1;
    node * temp = s_root;
    while (temp->right != nullptr)
        temp = temp->right;
    int maximum = find_number(temp);
    if (t_num > s_num)
        return min(maximum - t_num + s_num, t_num - s_num - 1);
    else
        return min(maximum - s_num + t_num, s_num - t_num - 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    for (int k = 0; k <= n; k++)
        nodes.push_back(new node(k));
    int i, j;
    for (int k = 0; k < m; k++)
    {
        cin >> i >> j;
        insert(i, j);
    }
    char c;
    for (int k = 0; k < q; k++)
    {
        cin >> c;
        cin >> i >> j;
        if (c == '+')
            insert(i, j);
        else if (c == '-')
            remove(i, j);
        else if (c == '?')
            cout << query(i, j) << endl;
    }
    return 0;
}
