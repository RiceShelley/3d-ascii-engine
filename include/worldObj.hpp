#ifndef __WORLDOBJ_H 
#define __WORLDOBJ_H

#include <iostream>
#include <vector>
#include <math.h>
#include "vector.hpp"
#include "screen.hpp"
#include "structures.hpp"

class WorldObj {

    public:
        WorldObj();
        WorldObj(double x, double y, double z);
        void add_vertex(Vector v);
        void add_edge(point p);
        void render(Screen *s);
        void obj_move(double x, double y, double z);
        void obj_set_pos(double x, double y, double z);
        void obj_set_pos(Vector v);
        void set_basis(Vector v);
        Vector get_basis();
        Vector get_pos();
        Vector rot_x(double ang, Vector v);
        Vector rot_y(double ang, Vector v);
        Vector rot_z(double ang, Vector v);
        double rx = 0;
        double ry = 0;
        double rz = 0;
    private:
        Vector pos;
        // basis vectors <i, j, k>
        Vector bi;
        Vector bj;
        Vector bk;
        // rotation of object in space
        double rot = 0;
        // get abs val of a double
        double dabs(double val);
        // find dot product between 2 vectors
        double dotp(Vector v1, Vector v2);
        // get magnitude of vector
        double mag(Vector v1);
        // get angle between 2 vectors
        double vang(Vector v1, Vector v2);
        // Array of points that make up world object
        std::vector<Vector> vertices;
        // edges that connect vertices
        std::vector<point> edges;
};

#endif