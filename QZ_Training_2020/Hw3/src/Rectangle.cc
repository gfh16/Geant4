#include "Rectangle.h"
#include <cmath>
const double PI = atan(1.0)*4;

#include<iostream>
using namespace std;

double Rectangle::maxCircle_area(){
    double r_max;
    r_max = fmin(this->width,this->height)/2;
    return 4*PI*r_max*r_max;
};


void Rectangle::print_self(){
    cout<<"----------------------------------------"<<endl;
    cout<<"Data:"<<endl;
    cout<<"width = "<<this->width<<endl;
    cout<<"height = "<<this->height<<endl;
    cout<<"area = "<<this->area()<<endl;
    cout<<"maxCircleArea = "<<this->maxCircle_area()<<endl;
    cout<<"----------------------------------------"<<endl;
}
