#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

int n;
unordered_map<string, int> num;
unordered_map<int, string> reversed_num;
vector<int> comp;
vector<bool> used;
vector<int> p;
vector<vector<int>> out;
vector<vector<int>> in;

int get_ind(const string & s)
{
    string name = s.substr(1, s.length() - 1);
    return s[0] == '+' ? num[name] : num[name] + n;
}

void dfs1(int v)
{
    if (used[v])
        return;
    used[v] = true;
    for (int u : out[v])
        dfs1(u);
    p.push_back(v);
}

void dfs2(int v, int c)
{
    if (comp[v] != -1)
        return;
    comp[v] = c;
    for (int u : in[v])
        dfs2(u, c);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string a;
        cin >> a;
        num.insert({a, i});
        reversed_num.insert({i, a});
    }

    in.resize(2 * n);
    out.resize(2 * n);
    for (int i = 0; i < m; i++)
    {
        string a, arrow, b;
        cin >> a >> arrow >> b;
        int x = get_ind(a);
        int y = get_ind(b);
        int nx = (x + n) % (2 * n);
        int ny = (y + n) % (2 * n);
        in[y].push_back(x);
        in[nx].push_back(ny);
        out[x].push_back(y);
        out[ny].push_back(nx);
    }

    comp.resize(2 * n);
    fill(comp.begin(), comp.end(), -1);
    used.resize(2 * n);

    for (int i = 0; i < 2 * n; i++)
    {
        dfs1(i);
    }

    int cnt = 1;
    for (int i = 2 * n - 1; i >= 0; i--)
    {
        int v = p[i];
        if (comp[v] != -1)
            continue;
        dfs2(v, cnt++);
    }

    for (int i = 0; i < n; i++)
    {
        if (comp[i] == comp[i + n])
        {
            cout << -1;
            return 0;
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        if (comp[i] > comp[i + n])
        {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';
    for (int i : ans)
    {
        cout << reversed_num[i] << '\n';
    }

    return 0;
}