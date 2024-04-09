#include <iostream>
#include <cmath>
#include <math.h>

double F(double x, double y) {
	return pow(x, 2) + 4 * pow(y, 2) + x * y + x;
}

double Fx(double x, double y) {
	return 2 * x + y + 1;
}

double Fy(double x, double y) {
	return x + 8 * y;
}

double L(double x, double y) {
	double l = pow(x, 2) + pow(y, 2);
	return sqrt(l);
}

double G(double x, double y, double t) {  // функция f(t)
	return F(x - t * Fx(x, y), y - t * Fy(x, y));
}

double Zol(double x, double y) {  // мтеод нахождения минимума функции f(t)
	double a = -1;
	double b = 1;
	double k = 0.38196;
	double l = 0.01;
	double t1 = a + k * (b - a);
	double t2 = a + b - t1;
	do {
		if (G(x, y, t1) <= G(x, y, t2)) {
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

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	int m = 50, it = 0;
	double eps1 = 0.1, eps2 = 0.15;
	double x, y, x0, y0, t, x01, y01, x00, y00;
	x0 = x00 = 3, y0 = y00 = 1;
	for (int i = 0; i < m; i++) {
		if (L(Fx(x0,y0), Fy(x0,y0)) < eps1)
			break;
		t = Zol(x0, y0);
		x = x0 - t * Fx(x0,y0);
		y = y0 - t * Fy(x0,y0);
		if (L(x - x0, y - y0) < eps2 && fabs(F(x, y) - F(x0, y0)) < eps2)
			break;
		x01 = x0, y01 = y0;
		x0 = x, y0 = y;
		it++;
	}
	// Матрица Гессе
	double MG[2][2];
	MG[0][0] = 2.0, MG[0][1] = 1.0, MG[1][0] = 1.0, MG[1][1] = 8.0;
	double l1 = (MG[0][0] + MG[1][1] + sqrt(pow((MG[0][0] + MG[1][1]), 2) - 4 * (MG[0][0] * MG[1][1] - MG[0][1] * MG[1][0]))) / 2;
	double l2 = (MG[0][0] + MG[1][1] - sqrt(pow((MG[0][0] + MG[1][1]), 2) - 4 * (MG[0][0] * MG[1][1] - MG[0][1] * MG[1][0]))) / 2;
	if (l1 > l2) {
		double c = l1;
		l1 = l2;
		l2 = c;
	}

	double q = (pow((l1 / l2 - 1), 2)) / (pow((l1 / l2 + 1), 2));
	double a = pow((L(x0 - x01, y0 - y01) / L(x01 - x00, y01 - y00)), it / 2);

	cout << "Алгоритм завершился за " << it << " итераций.\n";
	cout << "Точка минимума X = (" << x0 << "; " << y0 << ")\n";
	cout << "Значение функции в минимуме: F = " << F(x0, y0) << endl;
	cout << "Сходимость функции находится в пределах: " << a << " <= q <= " << q << endl;
	return 0;
}