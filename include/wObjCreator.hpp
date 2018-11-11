#ifndef __WOBJCREATOR__H
#define __WOBJCREATOR__H

#include "worldObj.hpp"
#include "vector.hpp"

class ObjCreator {

    public:
        void construct_box(WorldObj *obj, double x, double y, double z);
        void construct_cube(WorldObj *obj, double size);

    private:
};

#endif