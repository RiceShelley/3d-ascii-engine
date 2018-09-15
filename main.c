#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include "screen.h"
#include "vector.h"

double dabs(double val) {
	if (val < 0) {
		val *= -1;
	}
	return val;
}

int main(char* args) {
	init_screen();
	clear_screen(' ');

	//output_screen();

	int v_amt = 8;

	struct vector v[] = {{1, 1, 10}, {1, -1, 10}, {-1, 1, 10}, {-1, -1, 10},
				{1, 1, 15}, {1, -1, 15}, {-1, 1, 15}, {-1, -1, 15}};	
	struct point p[v_amt];

	struct edge e[] = {{0, 1}};

	for (int j = 0; j < 500; j++) {
		printf("----------------\n");
		usleep(10000);	
		clear_screen(' ');
		for (int i = 0; i < v_amt; i++) {
			convert_2d(&v[i], &p[i]);
			write_screen((int) p[i].x, (int) p[i].y, '*');	
			printf("x = %d | y = %d\n", (int) p[i].x, (int) p[i].y);
			v[i].z += .1;
		}
		for (int i = 0; i < 1; i++) {
			/*double x1 = p[e[i].v1].x + .00001;
			double y1 = p[e[i].v1].y;
			
			double x2 = p[e[i].v2].x;
			double y2 = p[e[i].v2].y;*/

			double x1 = 5.1;
			double x2 = 5;

			double y1 = 37;
			double y2 = 18;

			printf("x1 = %f | y1 = %f | x2 = %f | y2 = %f\n", x1, y1, x2, y2);

			double slope = (y2 - y1) / (x2 - x1);
			char c = '|';

			if (slope < -.2) {
				c = '/';
			} else if (slope > .2) {
				c = '\\';
			} else {
				c = '-';
			}
			if (slope > 100) {
				c = '|';
			} 

			for (double n = 0; n < dabs(x1 - x2); n += .01) {
				//double yf = (slope * n - x2 * slope) + y2;
				double yf = (slope * n) + y2 - x2;
				//printf("yf += %f\n", n);
				write_screen((int) (n + x1), (int) (yf + y1), c);
				//printf("x = %d | y = %d\n", (int) x2, (int) yf + n);
			}
			printf("dabs = %f\n", slope);	
		}
		output_screen();
	}

	return 0;
}
