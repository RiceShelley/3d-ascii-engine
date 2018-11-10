#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdio.h>
#include "screen.hpp"
#include "structures.hpp"

extern Screen sc;

class Vector {

	public:
		Vector();
		Vector(double x, double y, double z);

		double x;
		double y;
		double z;

		// print x, y, z to screen
		void output_vector();

		// flaten 3d point to 2d screen
		void convert_2d(struct point *p);

	private:
};
#endif
