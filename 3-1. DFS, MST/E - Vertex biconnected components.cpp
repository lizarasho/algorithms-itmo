#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <stack>

using namespace std;

struct edge
{
    int to;
    int num;
};

vector<vector<edge>> graph;
vector<bool> used;
vector<int> t_in;
vector<int> d;
vector<int> color;
stack<int> st;

int t = 0;
int max_color = 1;

void paint(int u, int n)
{
    t_in[u] = d[u] = ++t;
    used[u] = true;
    int cnt = 0;
    for (auto [v, num] : graph[u])
    {
        if (n == num)
        {
            continue;
        }
        if (used[v])
        {
            d[u] = min(d[u], t_in[v]);
            if (t_in[v] < t_in[u])
            {
                st.push(num);
            };
            continue;
        }
        cnt++;
        st.push(num);
        paint(v, num);
        d[u] = min(d[v], d[u]);
        if ((n != -1 && d[v] >= t_in[u]) || (n == -1 && cnt > 1))
        {
            int cur_color = max_color;
            while (st.top() != num)
            {
                color[st.top()] = cur_color;
                st.pop();
            }
            color[num] = cur_color;
            st.pop();
            max_color++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie();

    size_t n, m;
    cin >> n >> m;
    graph.resize(n);
    used.resize(n);
    t_in.resize(n);
    d.resize(n);
    color.resize(m);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back({v - 1, i});
        graph[v - 1].push_back({u - 1, i});
    }

    fill(used.begin(), used.end(), false);

    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            paint(i, -1);
            bool f = !st.empty();
            while (!st.empty())
            {
                color[st.top()] = max_color;
                st.pop();
            }
            if (f) max_color++;
        }
    }

    cout << max_color - 1 << '\n';
    for (int c : color)
    {
        cout << c << ' ';
    }

    return 0;
}