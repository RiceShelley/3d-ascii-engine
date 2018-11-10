#ifndef __WORLDOBJ_H 
#define __WORLDOBJ_H

#include <iostream>
#include <vector>
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
        Vector get_pos();
    private:
        Vector pos;
        double dabs(double val);
        // Array of points that make up world object
        std::vector<Vector> vertices;
        // edges that connect vertices
        std::vector<point> edges;
};

#endif