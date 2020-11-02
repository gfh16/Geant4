#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Polygon.h"

class Triangle: public Polygon{
    public:
        double area(){
            return width*height/2;
        }
        double maxCircle_area(); 
        void print_self();
};

#endif
