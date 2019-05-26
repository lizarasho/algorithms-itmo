#include <iostream>
#include <vector>

using namespace std;

int const NMAX = 101;
vector<int> a(NMAX);

int main()
{
    int k;
    while(cin >> k)
        a[k]++;

    for (int i = 0; i < NMAX; i++)
        for (int j = 0; j < a[i]; j++)
            cout << i << " ";

    return 0;
}