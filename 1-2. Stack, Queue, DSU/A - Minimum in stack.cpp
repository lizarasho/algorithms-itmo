#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    stack<int> st;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (k == 1)
        {
            int p;
            cin >> p;
            st.push((st.empty()) ? p : min(p, st.top()));
            continue;
        }
        if (k == 2)
        {
            st.pop();
            continue;
        }
        cout << st.top() << endl;
    }
    return 0;
}