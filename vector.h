#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdio.h>
#include "screen.h"

struct vector {
	double x;
	double y;
	double z;
};

struct point {
	double x;
	double y;
};

struct edge {
	int v1;
	int v2;
};

void output_vector(struct vector *v);
void convert_2d(struct vector *v, struct point *p);

#endif
