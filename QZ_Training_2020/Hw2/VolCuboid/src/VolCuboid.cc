
#include "VolCuboid.h"

VolCuboid::VolCuboid(float x, float y, float z) {
   length = x ;
   width  = y ;
   height = z ;
}

VolCuboid::~VolCuboid() {
   //new pointers should be deleted here.
   //if not, do nothing.
}

float VolCuboid::Vol() {
   return length*width*height;
}

float VolCuboid::Area() {
   float area;
   area = 2*length*width + 2*length*height + 2* width*height ;
   return area;
}
