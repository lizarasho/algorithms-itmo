#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1 << 7;
int n;
int f[N + 1][N + 1][N + 1];

int sum(int i, int j, int k)
{
    int s = 0, x, y, z;
    x = i;
    while (x > 0)
    {
        y = j;
        while (y > 0)
        {
            z = k;
            while (z > 0)
            {
                s += f[x][y][z];
                z -= z & (-z);
            }
            y -= y & (-y);
        }
        x -= x & (-x);
    }
    return s;
}

void add(int i, int j, int k, int added)
{
    int x, y, z;
    x = i + 1;
    while (x <= n)
    {
        y = j + 1;
        while (y <= n)
        {
            z = k + 1;
            while (z <= n)
            {
                f[x][y][z] += added;
                z += z & (-z);
            }
            y += y & (-y);
        }
        x += x & (-x);
    }
}


int main()
{
    cin >> n;
    for (int x = 0; x <= n; x++)
        for (int y = 0; y <= n; y++)
            for (int z = 0; z <= n; z++)
                f[x][y][z] = 0;

    int x1, y1, z1, x2, y2, z2, k;
    string s;
    int m = 0;
    while (m != 3)
    {
        cin >> m;
        if (m == 1)
        {
            cin >> x1 >> y1 >> z1 >> k;
            add(x1, y1, z1, k);
        }
        if (m == 2)
        {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << sum(x2 + 1, y2 + 1, z2 + 1) - sum(x1, y1, z1) -
                    sum(x2 + 1, y2 + 1, z1) - sum(x2 + 1, y1, z2 + 1) - sum(x1, y2 + 1, z2 + 1) +
                    sum(x1,     y1, z2 + 1) + sum(x1, y2 + 1, z1    ) + sum(x2 + 1, y1, z1    ) << endl;
        }
    }

    return 0;
}