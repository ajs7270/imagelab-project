#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

#include "CImg.h"


#define T( U, r, c, d, nRow, nCol ) U[ (r) + (c) * nRow + (d) * nRow * nCol ]

#ifndef MAX 
    #define MAX( a, b ) ( ( (a) > (b) ) ? (a) : (b) )
#endif

#ifndef MIN
    #define MIN( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
#endif

using namespace std;
using namespace cimg_library;

#define show_message 0 // 1: Yes, 0: No  

// ****************************************************************************
// 
// definition of the data types
//
// ****************************************************************************

enum segment {

    none        = 0,    // no contour
    tl          = 1,    // top - left
    tr          = 2,    // top - right
    tl_tr       = 3,    // right - left
    br          = 4,    // right - bottom
    tl_br       = 5,    // saddle
    tr_br       = 6,    // top - bottom
    tl_tr_br    = 7,    // bottom - left
    bl          = 8,    // bottom - left
    tl_bl       = 9,    // top - bottom
    tr_bl       = 10,   // saddle
    tl_tr_bl    = 11,   // right - bottom
    br_bl       = 12,   // right - left
    tl_br_bl    = 13,   // top - right
    tr_br_bl    = 14,   // top - left
    all         = 15   // no contour
};

enum dir {

    north       = 1,
    east        = 2,
    south       = 4,
    west        = 8,
    north_west  = 9,
    north_east  = 3,
    south_east  = 6,
    south_west  = 12,
    null = 0
};


struct cell {

    double     top;
    double     right;
    double     bottom;
    double     left;
};

// ****************************************************************************
// 
// declaration of the functions
//
// ****************************************************************************
void    moveCell( cell& cl, int nX, int nY ); 
cell    getCellMove( const cell& cl, int nX, int nY ); 
cell    getCell( const point& p ); 
segment getSegment( const CImg< double >& im, const double& val, const cell& cl ); 
bool    moveNextPointInitial( const CImg< double >& im, const double& val, const cell& cl, point& p );
bool    moveNextCellPoint( const CImg< double >& im, const double& val, cell& cl, point& p );
point   getNextPoint( const CImg< double >& im, const double& val, const cell& cl, const point& p ); 
dir     getSide( const cell& cl, const point& p );
point   getSidePoint( const CImg< double >& im, const double& val, const cell& cl, const dir& d );
bool    isValidPoint( const CImg< double >& im, const point& p );
void    setPoint( point& p, const double& x, const double& y );
bool    isValidCell( const CImg< double >& im, const cell& cl );
bool    isValidSegment( const segment& seg );
bool    isSaddleSegment( const segment& seg );
bool    hasLoop( vector< point >& contour );
void    printPoint( const point& p );
void    printCell( const cell& cl );
void    printSegment( const segment& seg );
void    printDirection( const dir& d );

// ****************************************************************************
// 
// definition of the functions
//
// ****************************************************************************
void    moveCell( cell& cl, int nX, int nY ) 
{
    cl.top      = cl.top + nX;
    cl.bottom   = cl.bottom + nX;
    cl.left     = cl.left + nY;
    cl.right    = cl.right + nY;
}

cell    getCellMove( const cell& cl, int nX, int nY ) 
{

    cell cl_move;

    cl_move.top      = cl.top + nX;
    cl_move.bottom   = cl.bottom + nX;
    cl_move.left     = cl.left + nY;
    cl_move.right    = cl.right + nY;

    return( cl_move );
}

cell    getCell( const point& p ) 
{

    cell    cl;
    double     x_f = floor( p.x ) - 0.5;
    double     y_f = floor( p.y ) - 0.5;

    cl.top      = x_f;
    cl.bottom   = x_f + 1;
    cl.left     = y_f;
    cl.right    = y_f + 1;

    if( show_message ) printf("debug:  -------getCell(): Given p = %f %f -> cl = top %.2f bottom %.2f left %.2f right %.2f\n", p.x, p.y, cl.top, cl.bottom, cl.left, cl.right);

    return( cl );
}

cell    getNextCell( const cell& cl, const dir& d )
{
    cell    cl_next = cl;

    if( (d & north) == north ) {

        moveCell( cl_next, -1, 0 );
    }
    else if( (d & south) == south ) {

        moveCell( cl_next, 1, 0 );
    }
    if( (d & east) == east ) {

        moveCell( cl_next, 0, 1 );
    }
    else if( (d & west) == west ) {

        moveCell( cl_next, 0, -1 );
    }

    if( show_message ) printf("debug:  -----------------getNextCell: Given cl [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl.top, cl.bottom, cl.left, cl.right);
    if( show_message ) printf("debug:  -----------------getNextCell: with d = %d\n", d);
    if( show_message ) printf("debug:  -----------------getNextCell: -> a new cell [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl_next.top, cl_next.bottom, cl_next.left, cl_next.right);

    return( cl_next );
}

dir     getDirectionSaddleSegment (const segment& segSaddle, const CImg< double >& im, const double& val, const cell& cl, const dir& dFrom)
{
    dir         dTo;
    double      xc = (cl.top + cl.bottom) / 2.;
    double      yc = (cl.left + cl.right) / 2.;
    double      dCenter = im.linear_atXY( xc - 0.5, yc - 0.5, 0, 0, 0 ); // -0.5: (x, y) to (i, j)

    if( show_message ) printf("debug-----------------------------------------getDirectionSaddleSegment: xc = %f, yc = %f\n", xc, yc);
    if( show_message ) printf("debug-----------------------------------------getDirectionSaddleSegment: dCenter %f\n", dCenter);   

    if (segSaddle == tl_br) {
        
        if (dCenter > val) {

            if (dFrom == north) {
                
                dTo = east;
            }
            else if (dFrom == east) {
                
                dTo = north;
            }
            else if (dFrom == south) {
                
                dTo = west;
            }
            else if (dFrom == west) {
                
                dTo = south;
            }
        }
        else {
            
            if (dFrom == north) {
                
                dTo = west;
            }
            else if (dFrom == east) {
                
                dTo = south;
            }
            else if (dFrom == south) {
                
                dTo = east;
            }
            else if (dFrom == west) {
                
                dTo = north;
            }
        }
    }
    else if (segSaddle == tr_bl) {

        if (dCenter > val) {
 
            if (dFrom == north) {
                
                dTo = west;
            }
            else if (dFrom == east) {
                
                dTo = south;
            }
            else if (dFrom == south) {
                
                dTo = east;
            }
            else if (dFrom == west) {
                
                dTo = north;
            }            
        }
        else {

            if (dFrom == north) {
                
                dTo = east;
            }
            else if (dFrom == east) {
                
                dTo = north;
            }
            else if (dFrom == south) {
                
                dTo = west;
            }
            else if (dFrom == west) {
                
                dTo = south;
            }
        }
    }
    else {
        if(show_message)
        {
            fprintf( stdout, "[Warning] input segment (%d) is not saddle\n", segSaddle );
            fflush( stdout );
        }
    }
    
    return (dTo);
}

bool    isSaddleSegment( const segment& seg )
{
    if (seg == tl_br || seg == tr_bl) {
        
        return (true);
    }
    else {
        
        return (false);
    }
}


segment getSegment( const CImg< double >& im, const double& val, const cell& cl )
{
    segment seg;
    int     nSegment = 0;
    double  tl, tr, br, bl;
    int     nRow = im.width();
    int     nCol = im.height();
    
    int t = (int)(cl.top - 0.5); // -0.5: xy to index
    int b = (int)(cl.bottom - 0.5);
    int l = (int)(cl.left - 0.5);
    int r = (int)(cl.right - 0.5);

    // consider the pixels at the border.
    tl = im.atXY (t, l,  0,0); 
    tr = im.atXY (t, r, 0,0);
    br = im.atXY (b, r, 0,0);
    bl = im.atXY (b, l,  0,0);

    if( show_message ) printf("debug:  ---------------------getSegment(): Given cl [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl.top, cl.bottom, cl.left, cl.right);
   
    if (cl.top < 0.5) {

        tl = 0;
        tr = 0;
    }
    if (cl.bottom > nRow-0.5) {
        
        br = 0;
        bl = 0;
    }
    if (cl.left < 0.5 ) {
        
        tl = 0;
        bl = 0;
    }
    if (cl.right > nCol-0.5) {
        
        tr = 0;
        br = 0;
    }
    
    if( tl > val ) { nSegment += (int) pow(2.0, 0); };
    if( tr > val ) { nSegment += (int) pow(2.0, 1); };
    if( br > val ) { nSegment += (int) pow(2.0, 2); };
    if( bl > val ) { nSegment += (int) pow(2.0, 3); };

    seg = (segment) nSegment;

    if( show_message ) printf("debug:  ---------------------getSegment(): Compare val = %f with tl = %f, tr = %f, br = %f, bl = %f\n", val, tl, tr, br, bl);
    if( show_message ) printf("debug:  ---------------------getSegment():\n");	    
    if( show_message ) printf("debug:  ---------------------getSegment(): -> seg = %d\n", seg);  

    return( seg );
}



// 17/4/9 modified
point   getNextPoint( const CImg< double >& im, const double& val, const cell& cl, const point& p )
{
    point pFrom, pTo;
    dir dFrom, dTo;
    segment seg;

    pFrom = p;
    dFrom = getSide( cl, p );
    seg = getSegment( im, val, cl );

    if( show_message ) printf("debug:  --------------------------getNextPoint: Given p = %f %f\n", pFrom.x, pFrom.y);
    if( show_message ) printf("debug:  --------------------------getNextPoint: Given cl [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl.top, cl.bottom, cl.left, cl.right);
    if( show_message ) printf("debug:  --------------------------getNextPoint: p, cl -> dFrom = %d\n", dFrom);
    if( show_message ) printf("debug:  --------------------------getNextPoint: val = %f \n", val);
    if( show_message ) printf("debug:  --------------------------getNextPoint: val, cl -> seg = %d\n", seg);

    dTo = null; // added

    if( isValidCell(im, cl) && isValidSegment(seg) && isValidPoint(im, pFrom) )
    {
        if( (seg & tl_tr) == tl || (seg & tl_tr) == tr )  // if seg includes EITHER tl or tr
        {    
            if( (dFrom & north) != north )
            {
                if(isSaddleSegment (seg))
                {
                     dTo = getDirectionSaddleSegment(seg,im,val,cl,dFrom);
                }
                // non-saddle
                else
                {
                    dTo = north;
                }
            }
        }

        if( (seg & tr_br) == tr || (seg & tr_br) == br )
        {
            if( (dFrom & east) != east )
            {
                // saddle
                if(isSaddleSegment (seg))
                {
                    dTo = getDirectionSaddleSegment(seg,im,val,cl,dFrom);
                }
                // non-saddle
                else
                {
                    dTo = east;
                }
            }
        }

        if( (seg & br_bl) == br || (seg & br_bl) == bl )
        {    
            if( (dFrom & south) != south )
            {
                // saddle
                if (isSaddleSegment (seg))
                {
                    dTo = getDirectionSaddleSegment(seg,im,val,cl,dFrom);
                }
                // non-saddle
                else
                {
                    dTo = south;
                }
            }
        }

        if( (seg & tl_bl) == tl || (seg & tl_bl) == bl )
        {
            if( (dFrom & west) != west )
            {
                // saddle
                if (isSaddleSegment (seg))
                {
                    dTo = getDirectionSaddleSegment(seg,im,val,cl,dFrom);
                 }
                // non-saddle
                else
                {
                    dTo = west;
                }
            }
        }

    }
    else
    { 
        if( show_message )
        {
            fprintf( stdout, "[Warning] seg = %d\n", (int) seg );
            fflush( stdout );
        }

        dTo = null;
    }

    // added
    if(dTo == null)
    {
        if( show_message )
        {
            fprintf( stdout, "[Warning] dTo = %d\n", (int) dTo );
            fflush( stdout );
        }

        setPoint(pTo,-1,-1);
    }
    else
    {
        pTo = getSidePoint( im, val, cl, dTo );
    }

    if( show_message ) printf("debug:  ------------------getNextPoint: -> dTo = %d\n", dTo);
    if( show_message ) printf("debug:  ------------------getNextPoint: -> pTo = %f %f\n", pTo.x, pTo.y);

    return( pTo );
}

bool    moveNextPointInitial( const CImg< double >& im, const double& val, const cell& cl, point& p ) 
{
    dir         d;
    segment     seg     = getSegment( im, val, cl );

    if( show_message ) printf("debug:  --moveNextPointInitial(): starts\n");   

    if( isValidSegment(seg) && isValidPoint(im, p) ) {

        if ( ( (seg & tl_tr) == tl ) || ( (seg & tl_tr) == tr ) ) {

            d       = north;
            p       = getSidePoint( im, val, cl, d );
        }
        else if( ( (seg & tr_br) == tr ) || ( (seg & tr_br) == br ) ) {

            d       = east;
            p       = getSidePoint( im, val, cl, d );
        }
        else if( ( (seg & br_bl) == br ) || ( (seg & br_bl) == bl ) ) {

            d       = south;
            p       = getSidePoint( im, val, cl, d );
        }
        else if( ( (seg & tl_bl) == tl ) || ( (seg & tl_bl) == bl ) ) {

            d       = west;
            p       = getSidePoint( im, val, cl, d );
        }
        else {
                
            setPoint( p, -1, -1 );
        }
    }
    else {

        setPoint( p, -1, -1 );
    }

    if( show_message ) printf("debug:  --moveNextPointInitial(): Given seg = %d\n", seg);
    if( show_message ) printf("debug:  --moveNextPointInitial(): -> d = %d\n", d);
    if( show_message ) printf("debug:  --moveNextPointInitial(): -> p = %f %f \n", p.x, p.y);
    
    return( isValidPoint(im, p) );
}

// modified 17/4/28
bool    moveNextCellPoint( const CImg< double >& im, const double& val, cell& cl, point& p )
{
    bool        bRtn;
    point       pFrom, pTo;
    dir         dFrom, dTo;
    cell        cl_next;
    segment     seg;

    if( show_message ) printf("debug:  --moveNextCellPoint: Given p = %f %f, var = %f\n", p.x, p.y, val);
    if( show_message ) printf("debug:  --moveNextCellPoint: Given cl [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl.top, cl.bottom, cl.left, cl.right);
 
    cell cl_tmp;
    point p_tmp;

    pFrom   = p;
    dFrom   = getSide( cl, pFrom );

    if( show_message ) printf("debug:  --moveNextCellPoint: p -> pFrom = %f %f\n", pFrom.x, pFrom.y);
    if( show_message ) printf("debug:  --moveNextCellPoint: cl, pFrom -> dFrom = %d\n", dFrom);
    setPoint( pTo, -1, -1 );

    // We seek a next point in North or Sourth direction first
    // and store the new point if valid

    if( (dFrom & north) == north ) {

        cl_next = getNextCell( cl, north );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }
    else if( (dFrom & south) == south ) {

        cl_next = getNextCell( cl, south );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }

    if( isValidPoint(im, pTo) )
    {
        cl_tmp = cl_next;
        p_tmp = pTo;
    }

    // in East or West directions

    if( (dFrom & east) == east ) {

        cl_next = getNextCell( cl, east );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }
    else if( (dFrom & west) == west ) {

        cl_next = getNextCell( cl, west );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }

    if( isValidPoint(im, pTo) )
    {
        cl_tmp = cl_next;
        p_tmp = pTo;
    }

    if( show_message ) printf("debug:  --moveNextCellPoint: ---- 4 directions -> pTo = %f %f\n", pTo.x, pTo.y);

    // in the other four directions

    if( (dFrom & north_west) == north_west ) {

        cl_next = getNextCell( cl, north_west );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }
    else if( (dFrom & north_east) == north_east ) {

        cl_next = getNextCell( cl, north_east );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }
    else if( (dFrom & south_east) == south_east ) {

        cl_next = getNextCell( cl, south_east );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }
    else if( (dFrom & south_west) == south_west ) {

        cl_next = getNextCell( cl, south_west );
        pTo     = getNextPoint( im, val, cl_next, pFrom );
    }

    if( show_message ) printf("debug:  --moveNextCellPoint: ---- 8 directions -> pTo = %f %f\n", pTo.x, pTo.y);

    if( isValidPoint(im, pTo) )
    {
        cl_tmp = cl_next;
        p_tmp = pTo;
    }

    // We use the latest on of the valid points

    cl = cl_tmp;
    p = p_tmp;

    if( show_message ) printf("debug:  --moveNextCellPoint: finally -> pTo = %f %f\n", pTo.x, pTo.y);
    
    if( isValidPoint(im, p) ) { bRtn = true; }
    else                        { bRtn = false; }

    return( bRtn );
}

dir     getSide( const cell& cl, const point& p )
{
    int d = 0;
    dir side;

    if( show_message ) printf("debug:  ------------------getSide(): Given p = %f %f\n", p.x, p.y);
    if( show_message ) printf("debug:  ------------------getSide(): Given cl [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl.top, cl.bottom, cl.left, cl.right);

    if( cl.top          == p.x ) { d += (int) pow(2.0,0); } // north
    else if( cl.bottom  == p.x ) { d += (int) pow(2.0,2); } // south
    if( cl.right        == p.y ) { d += (int) pow(2.0,1); } // east
    else if( cl.left    == p.y ) { d += (int) pow(2.0,3); } // west

    side = (dir) d;

    if( show_message ) printf("debug:  ------------------getSide(): -> side = %d\n", d);

    return( side );
}

point   getSidePoint( const CImg< double >& im, const double& val, const cell& cl, const dir& d ) 
{
    point   p;
    double  ratio;
    double  tl, tr, br, bl;
    int     nRow = im.width();
    int     nCol = im.height();

    int t = (int)(cl.top - 0.5); // -0.5: xy to index
    int b = (int)(cl.bottom - 0.5);
    int l = (int)(cl.left - 0.5);
    int r = (int)(cl.right - 0.5);

    // consider the pixels at the border.
    tl = im.atXY (t, l,  0,0); 
    tr = im.atXY (t, r, 0,0);
    br = im.atXY (b, r, 0,0);
    bl = im.atXY (b, l,  0,0);

    if( show_message ) printf("debug:  ------------getSidePoint(): Given d = %d, val = %f\n", d, val);
    if( show_message ) printf("debug:  ------------getSidePoint(): Given cl [top, bottom, left, right] = [%.2f, %.2f, %.2f, %.2f]\n", cl.top, cl.bottom, cl.left, cl.right);	
    if( show_message ) printf("debug:  ------------getSidePoint(): cl intensities, tl, tr, br, bl = %f %f %f %f\n", tl, tr, br, bl);
    
    if (cl.top < 0.5) {
        
        tl = 0;
        tr = 0;
    }
    if (cl.bottom > nRow-0.5) {
        
        br = 0;
        bl = 0;
    }
    if (cl.left < 0.5 ) {
        
        tl = 0;
        bl = 0;
    }
    if (cl.right > nCol-0.5) {
        
        tr = 0;
        br = 0;
    }

    if( (d & north) == north ) {

        ratio   = (val - tl) / (tr - tl);
        p.x = cl.top;
        p.y = cl.left + ratio; 
    }
    else if( (d & east) == east ) {

        ratio   = (val - tr) / (br - tr);
        p.x = cl.top + ratio; 
        p.y = cl.right;
    }
    else if( (d & south) == south ) {

        ratio   = (val - bl) / (br - bl);
        p.x = cl.bottom;
        p.y = cl.left + ratio; 
    }
    else if( (d & west) == west ) {

        ratio   = (val - tl) / (bl - tl);
        p.x = cl.top + ratio; 
        p.y = cl.left;
    }
    else {
        if(show_message)
        {
            fprintf( stdout, "[Warning] dir = %d\n", d );
            fflush( stdout );
        }
    }

    if( show_message ) printf("debug:  ------------getSidePoint(): \n");
    if( show_message ) printf("debug:  ------------getSidePoint(): -> a new p = %f %f\n", p.x, p.y);

    return( p );
}

bool    isValidPoint( const CImg< double >& im, const point& p )
{
    bool    bRtn = true;
    int     nRow = im.width();
    int     nCol = im.height(); 

    // consider the pixels at the border. image is transposed.
    if( p.x < 0.5 || p.x > nRow - 0.5 || p.y < 0.5 || p.y > nCol - 0.5 ) {
    //if( p.x < 0 || p.x > nRow  || p.y < 0 || p.y > nCol ) {
    
        bRtn = false;
    }

    return( bRtn );
}

bool    isValidCell( const CImg< double >& im, const cell& cl )
{
    bool    bRtn = true;
    int     nRow = im.width();
    int     nCol = im.height();

    // consider the pixels at the border.
    if( cl.top < 0.5 || cl.bottom > nRow - 0.5 || cl.left < 0.5 || cl.right > nCol - 0.5 ) {
    
        bRtn = false;
    }

    return( bRtn );
}

bool    isValidSegment( const segment& seg )
{
    bool    bRtn;

    if( seg > none && seg < all ) { bRtn = true; }
    else { bRtn = false; }

    return( bRtn );
}

bool    isSamePoint( const point& p1, const point& p2 )
{
    bool    bRtn;

    if( p1.x == p2.x && p1.y == p2.y ) { bRtn = true; }
    else { bRtn = false; }

    return( bRtn );
}

void    setPoint( point& p, const double& x, const double& y )
{
    p.x = x;
    p.y = y;
}

void    printPoint( const point& p )
{
    fprintf( stdout, "(point) row: %.2f, col: %.2f\n", p.x, p.y );
    fflush( stdout );
}

void    printCell( const cell& cl )
{
    fprintf( stdout, "(cell) top: %.2f, bottom: %.2f, left: %.2f, right: %.2f\n", cl.top, cl.bottom, cl.left, cl.right );
    fflush( stdout );
}

void    printSegment( const segment& seg )
{
    fprintf( stdout, "(segment) %d\n", seg );
    fflush( stdout );
}

void    printDirection( const dir& d )
{
    if( (d & north) == north ) {

        fprintf( stdout, "(dir) north" );
        fflush( stdout );
    }
    else if( (d & south) == south ) {

        fprintf( stdout, "(dir) south" );
        fflush( stdout );
    }
    if( (d & east) == east ) {

        fprintf( stdout, "(dir) east" );
        fflush( stdout );
    }
    else if( (d & west) == west ) {

        fprintf( stdout, "(dir) west" );
        fflush( stdout );
    }

    fprintf( stdout, "\n" );
    fflush( stdout );
}

bool    hasLoop( vector< point >& contour )
{
    bool    bRtn    = false;

    point   pLast   = contour.back();
    int     nSize   = contour.size();

    for( int i = 0; i < nSize-1; i++ ) {
            
        if( isSamePoint( pLast, contour[i] ) ) {
            bRtn = true;

            if( show_message )
            {
                printf("[Warning] %f %f is already in a contour point [%d] %f %f\n", pLast.x, pLast.y, i, contour[i].x, contour[i].y);
            }

            break;
        }
    }

    return( bRtn );
}


// *****************************************************************************
// This function obtains an iso-contour from the input image at given position.
//
// [INPUT]
//  im       : input image in CImg format
//  x0       : x-position in double type
//  y0       : y-position in double type
//
// [OUTPUT]
//  countour : contour points in CImg format
//
// [USAGE]
//  (see main.cpp)
//  CImg<double> im('Gaus4.png');
//  vector< point > contour;
//  cal_isocontour(im, 50.50, 30.50, contour);
//
//  
// *****************************************************************************
int cal_isocontour(const CImg< double >& im, double x0, double y0, vector< point >& contour)
{
    double x, y, val;
    point   p_in, p_init, p_next;
    cell    cl_init, cl_next;

   
    val = im.linear_atXY( x0 - 0.5, y0 - 0.5, 0, 0, 0 ); // -0.5: (x, y) to index (i, j)

    if(show_message)
    {
        fprintf( stdout, "cal_isocontour: Given p(x, y) = %.2f, %.2f\n", x0, y0);
        fprintf( stdout, "cal_isocontour: p -> val (intensity) = %.2f\n", val );
        fflush( stdout ); 
    }

    contour.clear(); // clear all points in contour list

    p_in.x = x0;
    p_in.y = y0;

    cl_init = getCell( p_in );
    p_init  = p_in;
   
    if( moveNextPointInitial( im, val, cl_init, p_init ) )
    {
        contour.push_back( p_init ); 
    }
   
    p_next  = p_init;
    cl_next = cl_init;

    if( moveNextCellPoint( im, val, cl_next, p_next ) )
    {
        contour.push_back( p_next ); 
    }
    
    while( isValidPoint(im, p_next) && !hasLoop(contour) ) // 17/4/28 modified
    {
        if( moveNextCellPoint( im, val, cl_next, p_next ) )
        {
            contour.push_back( p_next );
        }
    }
    
    return contour.size();
}


