#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct node
{
    char c;
    int par;
    unordered_map<char, int> transition;
    int suf_link;
    bool is_terminal = false;
    bool has_term_suf = false;

    node(char c = '\0', int par = -1, int suf_link = -1) : c(c), par(par), suf_link(suf_link) {};
};

int const root = 0;
vector<node> nodes;

void add_string(string s)
{
    int cur = root;
    int ptr = 0;

    while (nodes[cur].transition.count(s[ptr])) {
        cur = nodes[cur].transition[s[ptr++]];
    }

    for (int i = ptr; i < s.size(); i++) {
        int ind = (int)nodes.size();
        nodes[cur].transition[s[i]] = ind;
        nodes.emplace_back(s[i], cur);
        cur = ind;
    }

    if (cur != root) {
        nodes[cur].is_terminal = nodes[cur].has_term_suf = true;
    }
}

void create_suflinks()
{
    queue<int> q;
    for (auto [c, v] : nodes[root].transition) {
        q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        int p;
        p = nodes[v].par;
        p = nodes[p].suf_link;

        while (p != -1 && !nodes[p].transition.count(nodes[v].c)) {
            p = nodes[p].suf_link;
        }

        if (p == -1) {
            nodes[v].suf_link = root;
        } else {
            nodes[v].suf_link = nodes[p].transition[nodes[v].c];
        }

        for (auto [c, u] : nodes[v].transition) {
            q.push(u);
        }
    }
}

void create_terminals()
{
    queue<int> q;
    for (auto [c, v] : nodes[root].transition) {
        q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        nodes[v].has_term_suf = nodes[nodes[v].suf_link].has_term_suf || nodes[v].has_term_suf;
        for (auto [c, u] : nodes[v].transition) {
            q.push(u);
        }
    }
}

string get_word(int cur)
{
    string s;
    while (nodes[cur].par != -1) {
        s = nodes[cur].c + s;
        cur = nodes[cur].par;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen ("search4.in", "r", stdin);
    freopen ("search4.out", "w", stdout);

    int n;
    cin >> n;

    nodes.emplace_back();

    vector<string> words;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add_string(s);
        words.push_back(s);
    }

    create_suflinks();
    create_terminals();

    string text;
    cin >> text;

    unordered_set<int> states;

    int cur = 0;
    for (char c : text) {
        if (nodes[cur].transition.count(c)) {
            cur = nodes[cur].transition[c];
        } else if (cur != root) {
            while (nodes[cur].suf_link != -1 && !nodes[cur].transition.count(c)) {
                cur = nodes[cur].suf_link;
            }

            if (!nodes[cur].transition.count(c)) {
                cur = root;
            } else {
                cur = nodes[cur].transition[c];
            }
        }
        if (cur != root) {
            states.insert(cur);
        }
    }


    unordered_set<string> ans;
    for (auto state : states) {
        int p = state;
        if (!nodes[p].has_term_suf) {
            continue;
        }
        while (true) {
            if (nodes[p].is_terminal) {
                ans.insert(get_word(p));
            }
            p = nodes[p].suf_link;
            if (p == -1 || states.count(p) || !nodes[p].has_term_suf) {
                break;
            }
        }
    }

    for (const auto & word : words) {
        cout << (ans.count(word) ? "YES" : "NO") << '\n';
    }

    return 0;
}