#include "include/worldObj.hpp"

WorldObj::WorldObj() {
}

WorldObj::WorldObj(double x, double y, double z) {
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

void WorldObj::add_vertex(Vector v) {
    vertices.push_back(v);
}

void WorldObj::add_edge(point p) {
    edges.push_back(p);
}

void WorldObj::obj_move(double x, double y, double z) {
    pos.x += x;
    pos.y += y;
    pos.z += z;
}

void WorldObj::obj_set_pos(double x, double y, double z) {
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

void WorldObj::obj_set_pos(Vector v) {
    pos = v;
}


Vector WorldObj::get_pos() {
    return pos;
}

double WorldObj::dabs(double val) {
    if (val < 0) {
        val *= -1;
    } 
    return val;
}

void WorldObj::render(Screen *s) {
    // render verticies 
    point points[vertices.size()];
    int i = 0;
    for (Vector v : vertices) {
        point p;
        v.x += pos.x;
        v.y += pos.y;
        v.z += pos.z;
        v.convert_2d(&p);
        s->write_screen(p.x, p.y, '*');
        points[i] = {p.x, p.y};
        i++;
    }
    // draw edges
    for (int i = 0; i < edges.size(); i++) {
        double x1 = points[(int) edges.at(i).x].x + .1;
        double y1 = points[(int) edges.at(i).x].y * -1;

        double x2 = points[(int) edges.at(i).y].x;
        double y2 = points[(int) edges.at(i).y].y * -1;

        double slope = (y2 - y1) / (x2- x1);

        char c = 0;
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

        double precision = .01;
        if (c == '|') {
            precision = .0001;
        }
        for (double n = start; n < end; n += precision) {
            double yf = (slope * n - slope * x2) + y2;
            yf = dabs(yf);
            if (s->get_sc_char((int) n, (int) yf) == ' ') {
                s->write_screen((int) n, (int) yf, c);
            }
        }
    }
}