#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

double F(double x, double y, double r) {
	return pow(x, 2) + 4 * pow(y, 2) + x * y + x + (r/2) * pow((x + y - 2), 2);
}

double P(double x, double y, double r) {
	return (2 / r) * pow((x + y - 2), 2);
}

double Fx(double x, double y, double r) {
	return 2 * x + y + 1 + r * (x + y - 2);
}

double Fy(double x, double y, double r) {
	return x + 8 * y + r * (x + y - 2);
}


double L(double x, double y) {
	double l = pow(x, 2) + pow(y, 2);
	return sqrt(l);
}

double G(double x, double y, double r, double t) {  // функция f(t)
	return F(x - t * Fx(x, y, r), y - t * Fy(x, y, r), r);
}


double Zol(double x, double y, double r) {  // метод нахождения минимума функции f(t)
	double a = -1;
	double b = 1;
	double k = 0.38196;
	double l = 0.01;
	double t1 = a + k * (b - a);
	double t2 = a + b - t1;
	do {
		if (G(x, y, r, t1) <= G(x, y, r, t2)) {
			b = t2;
			t2 = t1;
			t1 = a + b - t2;
		}
		else {
			a = t1;
			t1 = t2;
			t2 = a + b - t1;
		}
	} while (fabs(b - a) > l);
	return (b + a) / 2;
}


int main() {
	setlocale(LC_ALL, "rus");
	int it = 0, m = 20;
	double eps1 = 0.01, eps2 = 0.015;
	double r = 0.1; double C = 5;
	double x, y, t, x01, y01, x00, y00, d1, d2, x0, y0, b, d10, d20;
	x00 = x01 = 3.0, y00 = y01 = 1.0;

	do {
		r = r * C;
		t = Zol(x00, y00, r);
		x0 = x00 - t * Fx(x00, y00, r);
		y0 = y00 - t * Fy(x00, y00, r);
		d10 = -Fx(x0, y0, r);
		d20 = -Fy(x0, y0, r);
		for (int i = 1; i < m; i++) {
			if (L(Fx(x0, y0, r), Fy(x0, y0, r)) < eps1)
				break;
			b = pow(L(Fx(x0, y0, r), Fy(x0, y0, r)), 2) / pow(L(Fx(x01, y01, r), Fy(x01, y01, r)), 2);
			d1 = -Fx(x0, y0, r) + b * d10;
			d2 = -Fy(x0, y0, r) + b * d20;
			t = Zol(x0, y0, r);
			x = x0 + t * d1;
			y = y0 + t * d2;
			if (L(x - x0, y - y0) < eps2 && fabs(F(x, y, r) - F(x0, y0, r)) < eps2 && L(x0 - x01, y0 - y01) < eps2 && fabs(F(x0, y0, r) - F(x01, y01, r)) < eps2) {
				x0 = x;
				y0 = y;
				break;
			}
			d10 = d1;
			d20 = d2;
			x01 = x0, y01 = y0;
			x0 = x, y0 = y;
		}
		x00 = x0, y00 = y0;
		//cout << x00 << "\t" << y00 << endl;
		it++;
	} while (P(x0, y0, r) > eps1);

	cout << "Алгоритм завершился за " << it << " итераций.\n";
	cout << "r = " << r << endl;
	cout << "Точка минимума X = (" << x0 << "; " << y0 << ")\n";
	cout << "Значение функции в минимуме: F = " << F(x0, y0, r) << endl;
	cout << "Аналитическое решение функции: F = " << F(1.625, 0.375, 0) << endl;
	return 0;
}