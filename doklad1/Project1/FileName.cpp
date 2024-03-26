#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

double F(double x) {
    return pow(x, 2) + 6*x + 13;
}

int main() {
    setlocale(LC_ALL, "rus");

    int itt = 0;
    const double a = -6;
    const double b = 4;
    const double n = 99;
    const double dx = (b - a) / n;

    double yMin = F(a);
    double xMin = a;

    for (double x = a + dx; x <= b; x += dx)
    {
        itt++;
        double y = F(x);
        if (y < yMin)
        {
            xMin = x;
            yMin = y;
        }
        cout << "Иттерация " << itt << ":" << " x = " << x << "; f(x) = " << y << endl;
    }
    
    cout << "Точка искомого минимума: " << xMin << "\n";
    cout << "Значение минимума заданной функции: " << yMin << "\n";
    cout << "Сходимость заданной функции для N = " << n+1 << ": " << 2 / (n + 1) << endl;
    return 0;
}