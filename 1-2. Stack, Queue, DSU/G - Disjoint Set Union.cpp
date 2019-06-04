#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct set
{
    int main;
    int min;
    int max;
    int number;
};

vector<set> inf;

int find(int a)
{
    if (inf[a].main != a)
        return inf[a].main = find(inf[a].main);
    return a;
}

void join(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    inf[a].min = min(inf[a].min, inf[b].min);
    inf[a].max = max(inf[a].max, inf[b].max);
    inf[a].number += inf[b].number;
    inf[b].main = a;
}

int main()
{
    size_t n;
    cin >> n;
    inf.resize(n);
    for (int i = 0; i < n; i++)
        inf[i] = {i, i, i, 1};
    string s;
    while (cin >> s)
    {
        if (s == "union")
        {
            int a, b;
            cin >> a >> b;
            join(a - 1, b - 1);
        } else if (s == "get")
        {
            int a;
            cin >> a;
            a = find(a - 1);
            cout << inf[a].min + 1 << ' ' << inf[a].max + 1 << ' ' << inf[a].number << '\n';
        }
    }
    return 0;
}