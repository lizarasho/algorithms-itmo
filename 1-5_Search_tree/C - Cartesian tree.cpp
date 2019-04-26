#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    node * parent;
    node * left;
    node * right;
    int x;
    int y;
    int n;
    node(int x, int y, int n): parent(nullptr), left(nullptr), right(nullptr),x(x), y(y), n(n) {};
};

node * root;
node * last;

struct ans
{
    int p;
    int l;
    int r;
    int i;
    ans(int p, int l, int r, int i) : p(p), l(l), r(r), i(i) {};
};
vector<ans> answers;


bool cmp(node* a, node* b)
{
    return a->x < b->x;
}

bool cmp2(ans a, ans b)
{
    return a.i < b.i;
}

void insert(node * last, node * t)
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
    if (last->right == nullptr)
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

void tree(node * v)
{
    if(!v) return;
    answers.emplace_back(
            (v->parent) ? v->parent->n : 0,
                (v->left) ? v->left->n : 0,
                (v->right) ? v->right->n : 0,
                v->n
    );
    tree(v->left);
    tree(v->right);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    root = nullptr;
    int n, a, b;
    cin >> n;
    vector<node * > points;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        points.push_back(new node(a, b, i + 1));
    }
    sort(points.begin(), points.end(), cmp);

    root = points[0];
    last = points[0];
    for (int i = 1; i < n; i++)
    {
        insert(last, points[i]);
        last = points[i];
    }
    cout << "YES" << endl;
    tree(root);
    sort(answers.begin(), answers.end(), cmp2);
    for (ans t : answers)
    {
        cout << t.p << " " << t.l << " " << t.r << endl;
    }
    return 0;
}