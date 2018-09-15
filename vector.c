#include "vector.h"

void output_vector(struct vector *v) {
	printf("x: %f\n", v->x);
	printf("y: %f\n", v->y);
	printf("z: %f\n", v->z);
}

void convert_2d(struct vector *v, struct point *p) {
	double x = v->x;
	double y = v->y;
	double z = v->z;

	double f = fnum / z;
	p->x = (x * f) + cx;
	p->y = (y * f) + cy;	
}
