#include "Triangle.h"

#include<iostream>
using namespace std;

double Triangle::maxCircle_area(){
    cout<<"Warning: We can't get the max CircleArea in Triangle only knowing the width and height\t\t";
    return 0;
};


void Triangle::print_self(){
    cout<<"----------------------------------------"<<endl;
    cout<<"Data:"<<endl;
    cout<<"width = "<<this->width<<endl;
    cout<<"height = "<<this->height<<endl;
    cout<<"area = "<<this->area()<<endl;
    cout<<"maxCircleArea = "<<this->maxCircle_area()<<endl;
    cout<<"----------------------------------------"<<endl;
}
