#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double const EPS = 10e-6;

double f(double x)
{
    return x * x + sqrt(x);
}

int main()
{
    double c;
    cin >> c;

    double l = 1;
    double r = 1;
    while (f(r) < c)
        r *= 2;

    while (r - l > EPS)
    {
        double m = (l + r) / 2;
        if (f(m) < c)
            l = m;
        else
            r = m;
    }

    cout << fixed << setprecision(6) << r;
    return 0;
}