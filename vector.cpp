#include "include/vector.hpp"

Vector::Vector() {
	Vector::x = 0;
	Vector::y = 0;
	Vector::z = 0;
}

Vector::Vector(double x, double y, double z) {
	Vector::x = x;
	Vector::y = y;
	Vector::z = z;
}

void Vector::output_vector() {
	printw("x: %f\n", x);
	printw("y: %f\n", y);
	printw("z: %f\n", z);
}

void Vector::convert_2d(point *p) {
	double f = sc.get_fnum() / z;
	p->x = (x * f) + sc.get_cx();
	p->y = (y * f) + sc.get_cy();	
}
