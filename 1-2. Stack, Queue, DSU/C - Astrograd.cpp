#include <iostream>
#include <vector>

using namespace std;

int const NMAX = 10e5;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> queue(NMAX);
    vector<int> index(NMAX);

    size_t n;
    cin >> n;

    int tail = 0;
    int head = 0;

    for (int i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        switch (c)
        {
            case 1 :
            {
                int id;
                cin >> id;
                queue[tail] = id - 1;
                index[id - 1] = tail;
                tail++;
                break;
            }
            case 2 :
            {
                head++;
                break;
            }
            case 3 :
            {
                tail--;
                break;
            }
            case 4 :
            {
                int q;
                cin >> q;
                cout << index[q - 1] - head << '\n';
                break;
            }
            case 5 :
            {
                cout << queue[head] + 1 << '\n';
            }
        }
    }

    return 0;
}