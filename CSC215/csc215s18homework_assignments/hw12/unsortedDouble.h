    #include <iostream>
#include <string>
#include <functional>
using std::nothrow;
using std::ostream;
using std::string;
using std::function;


#ifndef UNSORTEDDOUBLE__H
#define UNSORTEDDOUBLE__H

#ifdef UNSORTEDDOUBLE_EXPORTS
    #define UNSORTEDDOUBLE_API __declspec(dllexport)
#else
    #define UNSORTEDDOUBLE_API __declspec(dllimport)
#endif



class unsortedDouble
{
    public:
        UNSORTEDDOUBLE_API unsortedDouble();
        UNSORTEDDOUBLE_API ~unsortedDouble();
        UNSORTEDDOUBLE_API void clear();
        UNSORTEDDOUBLE_API void print ( ostream &out, bool forward = true,
                                        string seperator = ", ");
        UNSORTEDDOUBLE_API bool insert ( string val, int pos=1 );
        
        UNSORTEDDOUBLE_API bool remove ( int pos=1 );
        UNSORTEDDOUBLE_API bool remove ( string val );
        UNSORTEDDOUBLE_API bool rfind ( string val );
        UNSORTEDDOUBLE_API bool find ( string val );

        bool isEmpty( );
        int size();
        bool push_back(string val);
        bool push_front(string val);
        bool pop_back( string &val );
        bool pop_front( string &val );
        void swap( unsortedDouble &l );

        UNSORTEDDOUBLE_API unsortedDouble(unsortedDouble &l); // copy constructor
        UNSORTEDDOUBLE_API int countIf( function<bool(string)> cond );
        UNSORTEDDOUBLE_API int retrieve ( string val );
        UNSORTEDDOUBLE_API int rretrieve ( string val );
        UNSORTEDDOUBLE_API bool retrieve( string &item, int position );


        
    private:

        /** *******************************************************************
         * @struct  node unsortedDouble.h unsortedDouble.h
         *
         * @brief   A node structure used for the doubly linked list.
         *
         * @author  Schrader, Roger
         * @date    3/13/2018
         *********************************************************************/
        struct node
        {
            string item;               /*!< The item being stored*/
            node *next;                /*!< A Pointer to the next node. */
            node *last;                /*!< A Pointer to the previous node. */
        };
        node *headptr;                 /*!< A pointer to the first item 
                                            in the list */
        node *tailptr;                 /*!< A Pointer to the last item 
                                            in the list */
};
#endif
