#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<unordered_set<int>> edge;
vector<int> sub_size;
vector<int> parent;
int all_size;

int resize(int u, int p)
{
    sub_size[u] = 1;
    for (int v : edge[u])
        if (v != p)
            sub_size[u] += resize(v, u);
    return sub_size[u];
}

int find_centroid(int u, int p)
{
    for (int v : edge[u])
        if (v != p && sub_size[v] > all_size / 2)
            return find_centroid(v, u);
    return u;
}

void decompose(int u, int p)
{
    resize(u, -1);
    all_size = sub_size[u];
    int centroid = find_centroid(u, -1);
    parent[centroid] = p;
    for (int v : edge[centroid])
    {
        edge[v].erase(centroid);
        decompose(v, centroid);
    }
    edge[centroid].clear();
}

int main()
{
    int n;
    cin >> n;
    edge.resize(n);
    parent.resize(n);
    sub_size.resize(n);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        edge[u - 1].insert(v - 1);
        edge[v - 1].insert(u - 1);
    }
    decompose(0, -1);

    for (int i = 0; i < n; i++)
        cout << parent[i] + 1 << ' ';
    return 0;
}