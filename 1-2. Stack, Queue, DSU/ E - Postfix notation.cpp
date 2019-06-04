#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

int main()
{
    string s;
    getline(cin, s);
    stack<int> st;
    for (int i = 0; i < s.size(); i += 2)
    {
        if (isdigit(s[i]))
        {
            st.push(s[i] - '0');
            continue;
        }
        int y = st.top();
        st.pop();
        int x = st.top();
        st.pop();
        if (s[i] == '-')
            st.push(x - y);
        else if (s[i] == '+')
            st.push(x + y);
        else if (s[i] == '*')
            st.push(x * y);
    }
    cout << st.top();
    return 0;
}