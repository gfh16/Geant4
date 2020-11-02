#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h"

class Rectangle: public Polygon{
    public:
        double area(){
            return width*height;
        }
        double maxCircle_area();
        void print_self();
};


#endif
