/*
    Nathaniel Fagrey. CSC372. HW3
*/
#include"Polygon.h"

Polygon::Polygon( vector< Point > points )
{
    this->points = points;
}

void Polygon::operation( int counter )
{
    int numInter = 0;
    for ( int i = 0; i < points.size(); ++i )
    {
        for( int j = i + 1; j < points.size(); ++j )
        {         
            //cout << " " << points[i].x << "," << points[i].y << " " << points[j].x << "," << points[j].y << " " << points[ ( j+1 ) % points.size()].x << "," << points[ ( j+1 ) % points.size()].y << endl;
            if( segmentsIntersect( points[ i ], points[ ( i + 1) ], 
                points[ ( j ) % points.size() ], points[ ( j + 1 ) % points.size() ] ) )
            {
                numInter++;
            }
        }
    }

    if( numInter > points.size() )
       isSimple = false;
    
    else
        isSimple = true;

    printTest( counter );
    
}



bool Polygon::segmentsIntersect( Point p1, Point p2, Point p3, Point p4 )
{
    float d1 = direction( p3, p4, p1 );
    //cout << d1 << endl;
    float d2 = direction( p3, p4, p2 );
    //cout << d2 << endl;
    float d3 = direction( p1, p2, p3 );
    //cout << d3 << endl;
    float d4 = direction( p1, p2, p4 );
    //cout << d4 << endl;

    if( ( ( d1 > 0 && d2 < 0 ) || ( d1 < 0 && d2 > 0 ) ) and 
        ( ( d3 > 0 && d4 < 0 ) || ( d3 < 0 && d4 > 0 ) ) )
    {
        return true;
    }

    else if ( d1 == 0 && onSegement( p3, p4, p1 ) )
        return true;
    
    else if ( d2 == 0 && onSegement( p3, p4, p2 ) )
        return true;

    else if ( d3 == 0 && onSegement( p1, p2, p3 ) )
        return true;

    else if ( d4 == 0 && onSegement( p1, p2, p4 ) )
        return true;
    
    else
        return false;
}

// Most of this method gotten from
// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/ 
float Polygon::direction(Point p, Point q, Point r)
{
    //cout << "Vector1: " << (q.x - p.x) << "," << q.y - p.y << " Vector2: " << r.x - q.x << "," << r.y - q.y << endl;
    sign = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
    checkSign( sign );

    return sign;
}

bool Polygon::onSegement( Point pi, Point pj, Point pk )
{
    if( ( pk.x >= min( pi.x, pj.x) && pk.x <= max( pi.x, pj.x) ) && 
        ( pk.y >= min( pi.y, pj.y) && pk.y <= max( pi.y, pj.y ) ) )
    {
        return true;
    }

    else
        return false;
}

void Polygon::checkSign( float signCopy )
{
    if ( signCopy > 0 )
        signCopy = 1;
    else if ( signCopy < 0 )
        signCopy = -1;

    if ( signCopy != previousSign && previousSign != 0 && signCopy != 0 )
        isConvex = false;
    else
        previousSign = signCopy;
}

void Polygon::printTest( int TestNum )
{
    cout << "Polygon: " << TestNum << endl;
    
    if( !isSimple )
        cout << "\tNot Simple" << endl;

    else
    {
        cout << "\tSimple" << endl;

        if( isConvex )
        {
            cout << ("\tConvex" ) << endl;

            if( sign < 0 )
                cout << "\tCounter-Clockwise" << endl;

            else
                cout << "\tClockwise" << endl;
        }

        else
            cout << "\tConcave" << endl;

    
    }

}




