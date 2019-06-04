#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    stack<int> stack;
    vector<string> words;

    size_t n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int last = 0;

    for (int i = 0; i <= n; i++)
    {
        while (!stack.empty() && (i == n || stack.top() < a[i]))
        {
            if (last && stack.top() < last)
            {
                cout << "impossible";
                return 0;
            }
            last = stack.top();
            stack.pop();
            words.emplace_back("pop");
        }
        if (i == n)
            continue;
        stack.push(a[i]);
        words.emplace_back("push");
    }

    for (const string &s : words)
        cout << s << endl;

    return 0;
}