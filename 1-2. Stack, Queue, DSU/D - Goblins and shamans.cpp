#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> first;
    list<int> second;

    size_t n;
    cin >> n;

    for (int j = 0; j < n; j++)
    {
        char ch;
        cin >> ch;
        switch (ch)
        {
            case '+' :
            {
                int i;
                cin >> i;
                second.push_back(i);
                break;
            }
            case '*' :
            {
                int i;
                cin >> i;
                second.push_front(i);
                break;
            }
            case '-' :
            {
                cout << first.front() << '\n';
                first.pop_front();
            }
        }
        if (second.size() > first.size())
        {
            int x = second.front();
            second.pop_front();
            first.push_back(x);
        }
    }


    return 0;
}