#ifndef POLYGON_H
#define POLYGON_H

#include<iostream>
using namespace std;

class Polygon{
    protected:
        double width,height;
    public:
        void set_values(double a,double b){
            width = a;
            height = b;
        }
//        virtual double area(){
//            return 0;
//        }
        virtual double area() =0;
        virtual double maxCircle_area() =0;
        virtual void print_self(){
            cout<<"----------------------------------------"<<endl;
            cout<<"Date:"<<endl;
            cout<<"width = "<<width<<endl;
            cout<<"height = "<<height<<endl;
            cout<<"----------------------------------------"<<endl;
        }
};

#endif
