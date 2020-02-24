#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
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
    int word_ind = -1;

    node(char c = '\0', int par = -1, int suf_link = -1) : c(c), par(par), suf_link(suf_link) {};
};

int const root = 0;
vector<node> nodes;

void add_string(string s, int word_ind)
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
        nodes[cur].word_ind = word_ind;
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen ("search5.in", "r", stdin);
    freopen ("search5.out", "w", stdout);

    int n;
    cin >> n;

    nodes.emplace_back();

    vector<string> words;
    unordered_map<string, int> ans;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add_string(s, i);
        ans[s] = 0;
        words.push_back(s);
    }

    create_suflinks();
    create_terminals();

    string text;
    cin >> text;

    unordered_map<int, int> states;

    int cur = 0;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
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
            if (!states.count(cur)) {
                states[cur] = 1;
            } else {
                states[cur]++;
            }
        }
    }

    for (auto [state, num] : states) {
        int p = state;
        if (!nodes[p].has_term_suf) {
            continue;
        }
        while (true) {
            if (nodes[p].is_terminal) {
                ans[words[nodes[p].word_ind]] += num;
            }
            p = nodes[p].suf_link;
            if (p == -1 ||  !nodes[p].has_term_suf) {
                break;
            }
        }
    }

    for (const auto & word : words) {
        cout << (ans[word]) << '\n';
    }

    return 0;
}