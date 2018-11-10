#ifndef __WOBJCREATOR__H
#define __WOBJCREATOR__H

#include "worldObj.hpp"
#include "vector.hpp"

class ObjCreator {

    public:
        void construct_rect(WorldObj *obj);
        void construct_cube(WorldObj *obj, double size);

    private:
};

#endif