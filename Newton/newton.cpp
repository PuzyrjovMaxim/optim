#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

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

void M(double **A, double** B, int n) {
	for (int k = 0; k < n; ++k)
	{
		double div = A[k][k];

		for (int j = 0; j < n; ++j)
		{
			A[k][j] /= div;
			B[k][j] /= div;
		}

		for (int i = k + 1; i < n; ++i)
		{
			double multi = A[i][k];
			for (int j = 0; j < n; ++j)
			{
				A[i][j] -= multi * A[k][j];
				B[i][j] -= multi * B[k][j];
			}
		}
	}

	for (int k = n - 1; k > 0; --k)
	{
		for (int i = k - 1; i >= 0; --i)
		{
			double multi = A[i][k];
			for (int j = 0; j < n; ++j)
			{
				A[i][j] -= multi * A[k][j];
				B[i][j] -= multi * B[k][j];
			}
		}
	}
}


using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	int m = 50, it = 0;
	double eps1 = 0.005, eps2 = 0.01;
	double x, y, t, x01, y01, x00, y00, d1, d2, x0, y0;

	double** H = new double* [2];
	for (int i = 0; i < 2; i++) {
		H[i] = new double[2];
	}
	double** H1 = new double* [2];
	for (int j = 0; j < 2; j++) {
		H1[j] = new double[2];
	}

	H[0][0] = 2.0, H[0][1] = 1.0, H[1][0] = 1.0, H[1][1] = 8.0;
	H1[0][0] = 1.0, H1[0][1] = 0.0, H1[1][0] = 0.0, H1[1][1] = 1.0;
	M(H, H1, 2); // получение матрицы H-1

	x00 = x01 = x0 = 3, y00 = y01 = y0 = 1;
	if (H1[0][0] > 0 && (H1[0][1] < 0)) {
		for (int i = 0; i < m; i++) {
			if (L(Fx(x01, y01), Fy(x01, y01)) < eps1)
				break;
			d1 = -H1[0][0] * Fx(x01, y01) - H1[0][1] * Fy(x01, y01);
			d2 = -H1[1][0] * Fx(x01, y01) - H1[1][1] * Fy(x01, y01);
			x = x01 + d1;
			y = y01 + d2;
			if (L(x - x01, y - y01) < eps2 && fabs(F(x, y) - F(x01, y01)) < eps2 && L(x01 - x00, y01 - y00) < eps2 && fabs(F(x01, y01) - F(x00, y00)) < eps2) {
				x01 = x;
				y01 = y;
				it++;
				break;
			}
			x00 = x01, y00 = y01;
			x01 = x, y01 = y;
			it++;
		}
	}

	double M1 = 8.0, m1;
	d1 = Fx(x01, y01), d2 = Fy(x01, y01);
	cout << d1 << "\t" << d2 << endl;
	if (d1 >= d2)
		m1 = d2;
	else
		m1 = d1;
	double q = M1 * L(x0 - x01, y0 - y01) / (2 * m1);

	cout << "Алгоритм завершился за " << it << " итераций.\n";
	cout << "Точка минимума X = (" << x01 << "; " << y01 << ")\n";
	cout << "Значение функции в минимуме: F = " << F(x01, y01) << endl;
	cout << "Сходимость алгоритма: q = " << q << endl;
	return 0;
}