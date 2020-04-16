#include<iostream.h>
#include<process.h>
#include<bios.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14
#define POINT_DATA float
//..........class prototypes
template <class T> class vector;
typedef vector<POINT_DATA> point;
template <class T> class stack;
class vmouse;
class polygon;
typedef polygon set_of_points;
//..................GLOBAL VARIABLES
enum {	FALSE=0,TRUE=1,
		LEFT,RIGHT,BEYOND,BEHIND,BETWEEN,ORIGIN,DESTINATION,
		CLOCKWISE,ANTICLOCKWISE,
		UP,DOWN,
		DRAW,DRAWNOT,
		INSIDE,OUTSIDE,BOUNDARY,
		TOUCHING,CROSSING,INESSENTIAL,
		COLLINEAR,MAX=50};
#include<vector.h>
#include<edge.h>
#include<stack.h>
#include<function.h>
#include<vmouse.h>
#include<polygon.h>
