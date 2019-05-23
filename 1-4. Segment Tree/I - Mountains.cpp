#include <iostream>

using namespace std;

struct node
{
    node* left;
    node* right;
    int sum;
    int max_pref;
    bool set;
    node(): left(nullptr), right(nullptr), sum(0), max_pref(0), set(0) {}
};

void push(node* v, int l, int m, int r)
{
    if (!v -> left)
        v -> left = new node();
    if (!v -> right)
        v -> right = new node();
    if (v -> set)
    {
        int x = (v -> sum) / (r - l);
        v -> left -> sum = x * (m - l);
        v -> right -> sum = x * (r - m);
        v -> left -> max_pref = max(0, v -> left -> sum);
        v -> right -> max_pref = max(0, v -> right -> sum);
        v -> left -> set = v -> right -> set = true;
        v -> set = false;
    }
}

void apply(node* v)
{
    v -> sum = v -> left -> sum + v -> right -> sum;
    v -> max_pref = max(v -> left -> max_pref, v -> left -> sum + v -> right -> max_pref);
}

void update(int L, int R, node* v, int l, int r, int x)
{
    if (R <= l || r <= L)
        return;
    if (l >= L && r <= R)
    {
        v -> sum = (r - l) * x;
        v -> max_pref = max(0, v -> sum);
        v -> set = true;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, m, r);
    update(L, R, v -> left, l, m, x);
    update(L, R, v -> right, m, r, x);
    apply(v);
}

int find(node* v, int h, int l, int r)
{
    if (l == r - 1)
        return (v -> max_pref > h) ? l : r;
    int m = (l + r) / 2;
    push(v, l, m, r);
    if (v -> left -> max_pref > h)
        return find(v -> left, h, l, m);
    else
        return find(v -> right, h - v -> left -> sum, m, r);
}

int main()
{
    int n;
    cin >> n;
    node* root = new node();

    int h, a, b, D;
    string str;
    cin >> str;
    while (str != "E")
    {
        if (str == "Q")
        {
            cin >> h;
            cout << find(root, h, 0, n) << endl;
        }
        if (str == "I")
        {
            cin >> a >> b >> D;
            update(a - 1, b, root, 0, n, D);
        }
        cin >> str;
    }
    return 0;
}