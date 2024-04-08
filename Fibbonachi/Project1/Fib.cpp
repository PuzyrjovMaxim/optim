#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;
double F(double x) {
	return pow(x, 2) + 2;
}

int main() {
	setlocale(LC_ALL, "rus");
	int it = 0, i = 1;
	double a = -3.0;
	double b = 7.0;
	double l = 0.5;
	double eps = 0.2;
	double L = abs(a - b) / (2 * l);
	double fib[20], f1;
	fib[0] = 1, fib[1] = 1;
	do {
		i++;
		fib[i] = fib[i - 1] + fib[i - 2];
	} while (fib[i] <= L && i <= 19);

	double y = a + fib[i - 2] * (b - a) / fib[i];
	double z = a + fib[i - 1] * (b - a) / fib[i];

	do {
		if (F(y) <= F(z)) {
			b = z;
			z = y;
			y = a + fib[i - it - 3]*(b - a) / fib[i - it - 1];
		}
		else {
			a = y;
			y = z;
			z = a + fib[i - it - 2] * (b - a) / fib[i - it - 1];
		}
		it++;
	} while (it <= i-3);

	y = (a + b) / 2;
	z = y + eps;

	if (F(y) <= F(z))
		b = z;
	else
		a = y;

	double min = (a + b) / 2;
	cout << "Алгоритм сошёлся за " << it << " итераций." << endl;
	cout << "Искомый минимум функции: " << min << endl;
	cout << "Значение в минимуме: " << F(min) << endl;
	cout << "Сходимость заданной функции: " << 1 / fib[i] << endl;
	return 0;
}