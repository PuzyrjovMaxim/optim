#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;
double F(double x) {
	return pow(x, 2) + 2;
}

int main() {
	setlocale(LC_ALL, "rus");
	int it = 0;
	double a = -3.0;
	double b = 7.0;
	double eps = 0.2;
	double l = 0.5;
	double x, y;
	do {
		x = (a + b - eps) / 2;
		y = (a + b + eps) / 2;
		if (F(x) <= F(y))
			b = y;
		else
			a = x;
		it++;
	} while (fabs(b - a) > l);
	double min = (a + b) / 2;
	cout << "Искомый минимум функции: " << min << endl;
	cout << "Значение в минимуме: " << F(min) << endl;
	cout << "Сходимость заданной функции: " << 1 / pow(2, (it / 2)) << endl;
	return 0;
}