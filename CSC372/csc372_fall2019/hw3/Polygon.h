/*
    Nathaniel Fagrey. CSC372. HW3
*/
#ifndef POLYGON_H
#define POLYGON_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;

struct Point
{
    float x;
    float y;
};

class Polygon
{
    public:
        Polygon( vector< Point > points );
        void operation( int counter );
    private:
        vector< Point > points;
        bool segmentsIntersect( Point p1, Point p2, Point p3, Point p4 );
        float direction(  Point pi, Point pj, Point pk );
        float sign = 0;
        float previousSign = 0;
        bool onSegement( Point pi, Point pj, Point pk );
        void printTest( int TestNum );
        void checkSign( float signCopy );
        bool isConvex = true;
        bool isSimple;

};

#endif
