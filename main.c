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

	int v_amt = 8;

	struct vector v[] = {{1, 1, 10}, {1, -1, 10}, {-1, 1, 10}, {-1, -1, 10},
				{1, 1, 15}, {1, -1, 15}, {-1, 1, 15}, {-1, -1, 15}};	
	struct point p[v_amt];

	struct edge e[] = {{0, 1}, {2, 3}, {0, 2}, {1, 3}, 
				{4, 5}, {6, 7}, {4, 6}, {5, 7},
				{0, 4}, {1, 5}, {2, 6}, {3, 7}};

	while (1) {
	for (int j = 0; j < 100; j++) {
		usleep(10000);	
		clear_screen(' ');
		for (int i = 0; i < v_amt; i++) {
			convert_2d(&v[i], &p[i]);
			write_screen((int) p[i].x, (int) p[i].y, '*');	
			v[i].z += .1;
		}
		write_screen(0, 0, '0');	
		for (int i = 0; i < sizeof(e) / sizeof(struct edge); i++) {
			double x1 = p[e[i].v1].x + .1;
			double y1 = p[e[i].v1].y * -1;
			
			double x2 = p[e[i].v2].x;
			double y2 = p[e[i].v2].y * -1;

			double slope = (y2 - y1) / (x2 - x1);
			
			char c = '|';

			if (slope < -.2) {
				c = '\\';
			} else if (slope > .2) {
				c = '/';
			} else {
				c = '-';
			}
			if (dabs(slope) > 15) {
				c = '|';
			} 

			double start = x2;
			double end = x1;

			if (x1 < x2) {
				start = x1;
				end = x2;
			}

			for (double n = start; n < end; n += .01) {
				double yf = (slope * n - slope * x2) + y2;
				yf = dabs(yf);
				
				if (get_sc_char((int) n, (int) yf) == ' ') {
					write_screen((int) n, (int) yf, c);
				}
			}
		}
		output_screen();
	}


	for (int j = 100; j > 0; j--) {
		usleep(10000);	
		clear_screen(' ');
		for (int i = 0; i < v_amt; i++) {
			convert_2d(&v[i], &p[i]);
			write_screen((int) p[i].x, (int) p[i].y, '*');	
			v[i].z -= .1;
		}
		write_screen(0, 0, '0');	
		for (int i = 0; i < sizeof(e) / sizeof(struct edge); i++) {
			double x1 = p[e[i].v1].x + .1;
			double y1 = p[e[i].v1].y * -1;
			
			double x2 = p[e[i].v2].x;
			double y2 = p[e[i].v2].y * -1;

			double slope = (y2 - y1) / (x2 - x1);
			
			char c = '|';

			if (slope < -.2) {
				c = '\\';
			} else if (slope > .2) {
				c = '/';
			} else {
				c = '-';
			}
			if (dabs(slope) > 15) {
				c = '|';
			} 

			double start = x2;
			double end = x1;

			if (x1 < x2) {
				start = x1;
				end = x2;
			}

			for (double n = start; n < end; n += .01) {
				double yf = (slope * n - slope * x2) + y2;
				yf = dabs(yf);
				
				if (get_sc_char((int) n, (int) yf) == ' ') {
					write_screen((int) n, (int) yf, c);
				}
			}
		}
		output_screen();
	}
	}

	return 0;
}
