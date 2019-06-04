#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct set
{
    int exp;
    int rank;
    int main;
};

vector<set> inf;

int find(int a)
{
    while (inf[a].main != a)
        a = inf[a].main;
    return a;
}

int get(int a)
{
    if (inf[a].main != a)
        return inf[a].exp + get(inf[a].main);
    return inf[a].exp;
}

void join(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    if (inf[b].rank > inf[a].rank)
        swap(a, b);
    inf[b].main = a;
    inf[b].exp -= inf[a].exp;
    inf[a].rank = max(inf[a].rank, inf[b].rank + 1);
}

void add(int a, int v)
{
    a = find(a);
    inf[a].exp += v;
}

int main()
{
    size_t n;
    int m;
    cin >> n >> m;
    inf.resize(n);
    for (int i = 0; i < n; i++)
        inf[i] = {0, 0, i};

    string s;
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        if (s == "get")
        {
            int x;
            cin >> x;
            cout << get(x - 1) << '\n';
        } else if (s == "join")
        {
            int x, y;
            cin >> x >> y;
            join(x - 1, y - 1);
        } else if (s == "add")
        {
            int x, v;
            cin >> x >> v;
            add(x - 1, v);
        }
    }
    return 0;
}