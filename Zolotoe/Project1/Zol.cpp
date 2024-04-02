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
	double l = 0.5;
	double k = 0.38196;
	double y = a + k * (b - a);
	double z = a + b - y;
	do 
	{
		if (F(y) <= F(z)) {
			b = z;
			z = y;
			y = a + b - z;
		}
		else {
			a = y;
			y = z;
			z = a + b - y;
		}
		it++;
	} while (fabs(b-a) > l);
	double min = (a + b) / 2;
	cout << "Алгоритм сошёлся за " << it << " итераций." << endl;
	cout << "Искомый минимум фукнции: " << min << endl;
	cout << "Значение в минимуме: " << F(min) << endl;
	cout << "Сходимость заданной функции: " << pow(0.618, it - 1) << endl;
	return 0;
}