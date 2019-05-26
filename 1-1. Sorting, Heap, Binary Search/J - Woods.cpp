#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double const EPS = 10e-5;

int Vp, Vf;
double a;

double f(double x)
{
    return (sqrt((1 - a) * (1 - a) + x * x)) / Vp
         + (sqrt((1 - x) * (1 - x) + a * a)) / Vf;
}

int main()
{
    cin >> Vp >> Vf >> a;

    double l = 0;
    double r = 1;

    while (r - l > EPS)
    {
        double x = (2 * l + r) / 3;
        double y = (l + 2 * r) / 3;
        if (f(x) > f(y))
            l = x;
        else
            r = y;
    }

    cout << fixed << setprecision(6) << r;
    return 0;
}