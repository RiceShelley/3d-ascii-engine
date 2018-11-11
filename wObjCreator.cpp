#include "include/wObjCreator.hpp"

void ObjCreator::construct_box(WorldObj *obj, double x, double y, double z) {
    obj->add_vertex(Vector(x, y, -z));
    obj->add_vertex(Vector(x, -y, -z));
    obj->add_vertex(Vector(-x, y, -z));
    obj->add_vertex(Vector(-x, -y, -z));

    obj->add_vertex(Vector(x, y, z));
    obj->add_vertex(Vector(x, -y, z));
    obj->add_vertex(Vector(-x, y, z));
    obj->add_vertex(Vector(-x, -y, z));

    obj->add_edge({0, 1});
    obj->add_edge({2, 3});
    obj->add_edge({0, 2});
    obj->add_edge({1, 3});
    obj->add_edge({4, 5});
    obj->add_edge({6, 7});
    obj->add_edge({4, 6});
    obj->add_edge({5, 7});
    obj->add_edge({0, 4});
    obj->add_edge({1, 5});
    obj->add_edge({2, 6});
    obj->add_edge({3, 7});
}

void ObjCreator::construct_cube(WorldObj *obj, double size) {
    obj->add_vertex(Vector(size, size, size * -1));
    obj->add_vertex(Vector(size, size * -1, size * -1));
    obj->add_vertex(Vector(size * -1, size, size * -1));
    obj->add_vertex(Vector(size * -1, size * -1, size * -1));

    obj->add_vertex(Vector(size, size, size));
    obj->add_vertex(Vector(size, size * -1, size));
    obj->add_vertex(Vector(size * -1, size, size));
    obj->add_vertex(Vector(size * -1, size * -1, size));

    obj->add_edge({0, 1});
    obj->add_edge({2, 3});
    obj->add_edge({0, 2});
    obj->add_edge({1, 3});
    obj->add_edge({4, 5});
    obj->add_edge({6, 7});
    obj->add_edge({4, 6});
    obj->add_edge({5, 7});
    obj->add_edge({0, 4});
    obj->add_edge({1, 5});
    obj->add_edge({2, 6});
    obj->add_edge({3, 7});
}