#include "include/worldObj.hpp"

WorldObj::WorldObj() {
    bi.x = 1;
    bj.y = 1;
    bk.z = 1;
}

WorldObj::WorldObj(double x, double y, double z) {
    pos.x = x;
    pos.y = y;
    pos.z = z;
    bi.x = 1;
    bj.y = 1;
    bk.z = 1;
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

void WorldObj::set_basis(Vector v) {
    bi = v;
}

Vector WorldObj::get_basis() {
    return bi;
}

void WorldObj::obj_set_pos(Vector v) {
    pos = v;
}

Vector WorldObj::get_pos() {
    return pos;
}

double WorldObj::dotp(Vector v1, Vector v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z + v2.z);
}

double WorldObj::vang(Vector v1, Vector v2) {
    return acos(dotp(v1, v2) / (mag(v1) * mag(v2)));
}

double WorldObj::mag(Vector v1) {
    return sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2));
}

double WorldObj::dabs(double val) {
    if (val < 0) {
        val *= -1;
    } 
    return val;
}

Vector WorldObj::rot_x(double ang, Vector v) {
    Vector r;
    r.x = v.x;
    r.y = v.y * cos(ang) + v.z * sin(ang);
    r.z = v.y * sin(ang) * -1 + v.z * cos(ang);
    return r;
}

Vector WorldObj::rot_y(double ang, Vector v) {
    Vector r;
    r.x = v.x * cos(ang) - v.z * sin(ang);
    r.y = v.y;
    r.z = v.x * sin(ang) + v.z * cos(ang);
    return r;
}

Vector WorldObj::rot_z(double ang, Vector v) {
    Vector r;
    r.x = v.x * cos(ang) + v.y * sin(ang);
    r.y = v.x * sin(ang) * -1 + v.y * cos(ang);
    r.z = v.z;
    return r;
}

void WorldObj::render(Screen *s) {
    // render verticies 
    point points[vertices.size()];
    int i = 0;
    for (Vector v : vertices) {
        // get current angle between <i, j, k> components of basis vector

        // mulitply vector by basis vector
        /*v.x = bi.x * v.x + bj.x * v.y + bk.x * v.z;
        v.y = bi.y * v.x + bj.y * v.y + bk.y * v.z;
        v.z = bi.z * v.x + bj.z * v.y + bk.z * v.z;*/
        v = rot_x(rx, v);
        v = rot_y(ry, v);
        v = rot_z(rz, v);
        // add offset from origen to simulate movement 
        v.x += pos.x;
        v.y += pos.y;
        v.z += pos.z;

        point p;
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

        double slope = (y2 - y1) / (x2 - x1);

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
        if (dabs(start - end) > 2) {
            precision = .5;
        }
        for (double n = start; n < end; n += precision) {
            double yf = (slope * n - slope * x2) + y2;
            yf = dabs(yf);
            if (s->get_sc_char((int) n, (int) yf) != '*') {
                s->write_screen((int) n, (int) yf, c);
            }
        }
    }
}