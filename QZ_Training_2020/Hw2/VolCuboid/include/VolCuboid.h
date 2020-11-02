//####Class VolCuboid######
//####to calculate the volume, surface area of a volCuboid####

#ifndef VOLCUBOID_H
#define VOLCUBOID_H

#include <iostream>
//#include <math>

class VolCuboid {
   public:
	VolCuboid(float x, float y, float z);//Constructor function
	~VolCuboid();//Deconstructor function
	float Vol();//Member Function
	float Area();//Member Function
   private:
	float length, width, height;
};

#endif

