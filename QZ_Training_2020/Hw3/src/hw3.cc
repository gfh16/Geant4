#include<iostream>
#include "Polygon.h"
#include "Rectangle.h"
#include "Triangle.h"

using namespace std;

int main(){
    Rectangle rect;
    Triangle trgl;
    Polygon * ppoly1 = &rect;
    Polygon * ppoly2 = &trgl;
    ppoly1->set_values(4.5,6);
    ppoly2->set_values(6,4.5);
    //cout<<ppoly1->area()<<'\t'<<ppoly1->maxCircle_area()<<'\n';
    //cout<<ppoly2->area()<<'\t'<<ppoly2->maxCircle_area()<<'\n';
    cout<<"A Rectangle: "<<endl; 
    ppoly1->print_self();
    cout<<"A Triangle: "<<endl; 
    ppoly2->print_self();

    return 0;
}
