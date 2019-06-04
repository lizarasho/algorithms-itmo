#include <iostream>
#include <vector>

using namespace std;

int main()
{
    size_t n;
    cin >> n;
    vector<int> a(n);
    vector<int> size(n);

    int last = -1;
    int cnt = 0;
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x == last)
        {
            res++;
            continue;
        }
        if (cnt && a[cnt - 1] == x)
        {
            if (size[cnt - 1] == 2) {
                cnt--;
                last = x;
                res += 3;
            } else {
                last = -1;
                size[cnt - 1]++;
            }
            continue;
        }
        last = -1;
        a[cnt] = x;
        size[cnt++] = 1;
    }

    cout << res;

    return 0;
}