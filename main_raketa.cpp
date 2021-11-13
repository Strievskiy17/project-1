#include <iostream>
#include <cstdlib>
#include <math.h>

// константы
#define g 	9.81
#define dM 	-300.0
#define S 	1.0
#define r0	1.25
#define k	0.00013
#define	u	3000.0

// начальные условия
#define z0	0.0
#define V0	0.0
#define M0	20000.0

using namespace std;

// расчет полета ракеты
// метод Рунге-Кутты 4 порядка

// вычисление ро
double r(double y){
	return r0*exp(-k*y);
}
// правые части
double f1(double v){
	return v;
}
double f2(double z, double v, double m){
	return -(u*dM/m + g + S*r(z)*v*v/m);
}
double f3(){
	return dM;
}
// вывод
void outX(double x, double t, double m){
	printf("t = %.3f \tz = %.1f \tM = %.0f\n", t, x, m);
}

int main(int argc, char** argv) {

	setlocale(LC_ALL, "Russian");
	double k1, k2, k3, k4;
	double q1, q2, q3, q4;
	// x - текущая точка, xn - следующая точка
	double z, zn;
	double V, Vn;
	double M, Mn;

	double h = 1.0/3.0;
	double t = 0; // время

	// начальная точка
	zn = z0;
	Vn = V0;
	Mn = M0;

	cout << "Взлет ракеты: t - время, с; z - высота, м; М - масса, кг" << endl;
	for(int j = 0; j < 161; j++){
		z = zn;
		V = Vn;
		M = Mn;
		if(j % 10 == 0) outX(z, t, M);

		t += h;
		q1 = f1(V); 			k1 = f2(z, V, M);
		q2 = f1(V + k1*h/2.0);	k2 = f2(z + q1*h/2.0, V + k1*h/2.0, M + f3()*h/2.0);
		q3 = f1(V + k2*h/2.0);	k3 = f2(z + q2*h/2.0, V + k2*h/2.0, M + f3()*h/2.0);
		q4 = f1(V + k3*h);		k4 = f2(z + q3*h, V + k3*h, M + f3()*h);

		zn = z + h/6.0*(q1 + 2.0*(q2 + q3) + q4);
		Vn = V + h/6.0*(k1 + 2.0*(k2 + k3) + k4);
		Mn = M + h*f3();
	}
	cout << endl << "Ракета взлетит на высоту " << z/1000 << " км" << endl;

    system("PAUSE");
    return EXIT_SUCCESS;
}
