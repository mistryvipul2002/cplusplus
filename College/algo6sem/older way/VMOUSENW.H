#include<iostream.h>
#include<process.h>
#include<bios.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14
//..........class prototypes
template <class T> class vector;
typedef vector<int> point;
template <class T> class stack;
class vmouse;
class polygon;

//............function prototypes
void check(point);
float anglesubtendedby(point,point);
template <class T> void swap(T &p1,T &p2){
	T temp;
	temp=p1;
	p1=p2;
	p2=temp;
}
int turn(point,point,point);
void vline(point,point);
void vputpixel(point,int);
void vmoveto(point);
void vrectangle(point,point);
void triangle(point,point,point);
int cycle(int,int,char);
void grid(int);
enum {	FALSE=0,TRUE=1,LEFT,RIGHT,CLOCKWISE,ANTICLOCKWISE,UP,DOWN,MAX=100};

//------------------------------------------------
template <class T> class vector{
public:
	int x,y;
	vector(){}
	vector(vector &v){
		x=v.x;y=v.y;
	}
	void put(T x1,T y1){
		x=x1;y=y1;
	}
	void get(T &x1,T &y1){
		x1=x;y1=y;
	}
	int operator==(vector v)	{	return v.x==x&&v.y==y;	}
	int operator!=(vector v)	{	return v.x!=x||v.y!=y;	}
	int operator>(vector v)	{	return x>v.x&&y>v.y;	}
	int operator<(vector v)	{	return x<v.x&&y<v.y;	}
	int operator>=(vector v)	{	return x>=v.x&&y>=v.y;	}
	int operator<=(vector v)	{	return x<=v.x&&y<=v.y;	}
	istream& operator>>(istream& istr){	return istr>>x>>y;	}
	ostream& operator<<(ostream& ostr){	return ostr<<x<<y;	}
	vector operator+(vector);
//	vector operator=(vector);
	vector operator-(vector);
};
template <class T> vector<T> vector<T>::operator+(vector<T> v){
	vector v2;
	v2.put(v.x+x,v.y+y);
	return (v2);
}
template <class T> vector<T> vector<T>::operator-(vector<T> v){
	vector v2;
	v2.put(v.x-x,v.y-y);
	return (v2);
}
/*template <class T> vector<T> vector<T>::operator=(vector<T> v){
	vector v2;
	x=v.x;y=v.y;
	return (v2);
} */
//-----------------------------------------------
template <class stacktype>class stack{
	stacktype p[MAX];
	int top;
public:
	stack(){top=-1;}
	void push(stacktype t){
		if(top+1==MAX){cout<<"Can't push....overflow";exit(0);}
		p[++top]=t;
	}
	stacktype pop(){
		if(top==-1){cout<<"Can't pop....";exit(0);}
		return(p[top--]);
	}
	int empty(){
		if(top==-1)return(TRUE);
		return(FALSE);
	}
	stacktype stacktop(){
		return p[top];
	}
};
//----------------------------------------------
class vmouse
{
public:
	union REGS i,o;
	void showmouseptr();
	void hidemouseptr();
	void restrictmouseptr(int,int,int,int);
	void getmousepos(int*,int*,int*);
	int initmouse();
	void waitforrightclick();
	int waitforaclick(point&);
	void getpt(point&);
}v;
void vmouse::showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}
void vmouse::hidemouseptr()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}
int vmouse::initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
}
void vmouse::restrictmouseptr(int x1,int y1,int x2,int y2)
{
	i.x.ax=7;
	i.x.cx=x1;
	i.x.dx=x2;
	int86(0x33,&i,&o);
	i.x.ax=8;
	i.x.cx=y1;
	i.x.dx=y2;
	int86(0x33,&i,&o);
}
void vmouse::getmousepos(int *button,int *x,int *y)
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button = o.x.bx;
	*x=o.x.cx;
	*y=480-o.x.dx;
}
void vmouse::waitforrightclick(){
	point p;
	while(waitforaclick(p)!=RIGHT){}
}
void vmouse::getpt(point &p1){
	while(waitforaclick(p1)!=LEFT){}
}
int vmouse::waitforaclick(point &p){
	int *button=NULL;
	showmouseptr();
	while(1){
		getmousepos(button,&p.x,&p.y);
		while((*button&1)!=1&&(*button&2)!=2)getmousepos(button,&p.x,&p.y);
		if((*button&1)==1){
			while((*button&1)==1)getmousepos(button,&p.x,&p.y);
			hidemouseptr();
			return(LEFT);
		}
		else if((*button&2)==2){
				while((*button&2)==2)getmousepos(button,&p.x,&p.y);
				hidemouseptr();
				return(RIGHT);
			}
	}
}
//------------------------------------------------
class polygon{
public:
	point pt[MAX];
	int np;
	polygon(){np=0;}
	void add(point p){
		pt[np++]=p;
	}
	point cg();
	void input();
	int convex();
	int monotone_wrt_x_axis();
	void orient(int);
	int pointinside(point);
};
point polygon::cg(){
	//.......find c.g. of polygon
	point q;q.put(0,0);
	for(int i=0;i<np;i++)q=q+pt[i];
	q.x=q.x/np;q.y=q.y/np;
	return(q);
}
void polygon::input(){
	//.....enter the lines
	vmouse v;
	point p,prev;int k=0;
	setcolor(15);
	while(v.waitforaclick(p)==LEFT){
		check(p);
		add(p);
		if(k==0)prev=p;
		vline(p,prev);
		prev=p;k=1;
	}
	vline(prev,pt[0]);
}
int polygon::convex(){
	//.....check polygon is convex or not
	int parity=LEFT;
	if(turn(pt[0],pt[1],pt[2])==RIGHT)parity=RIGHT;
	for(int i=0;i<=np;i++){
		if(turn(pt[i%np],pt[(i+1)%np],pt[(i+2)%np])!=parity)
			return(FALSE);
	}
	return(TRUE);
}
void polygon::orient(int direction){
	//...put points of a "convex polygon" in fashion specified by "direction"
	if( (turn(pt[0],pt[1],pt[2])==RIGHT&& //...means points are clockwise
		direction==ANTICLOCKWISE)		||
	    (turn(pt[0],pt[1],pt[2])==LEFT&& //...means points are anticlockwise
		direction==CLOCKWISE)
	  ){
		for(int i=0;i<np/2;i++)
			swap(pt[i],pt[(np-1)-i]);
	}
}
int polygon::pointinside(point p){
	//......check if point p lies in polygon
	point q=cg();	//.....q is cg of polygon
	for(int i=0;i<np;i++){
		if(turn(p,q,pt[i])==LEFT &&  turn(p,q,pt[(i+1)%np])==RIGHT){
			//.........pt z lies in wedge p(i)-q-p(i+1)
			//........now check whether p(i)-p(i+1)-z is a left turn
			if(turn(pt[i],pt[(i+1)%np],p)==LEFT)return(TRUE);
		}
	}
	return(FALSE);
}
int polygon::monotone_wrt_x_axis(){
	point left=pt[0],right=pt[0];
	int posleft=0,posright=0;
	for(int i=0;i<np;i++){
		if(pt[i].x<left.x){left=pt[i];posleft=i;}
		if(pt[i].x>right.x){right=pt[i];posright=i;}
	}
	int cou1=posleft,cou2=posleft;
	for(i=0;i<np;i++){
		if(cou1!=cycle(posright,np,'-')){
			if(pt[cou1].x>pt[cycle(cou1,np,'+')].x)return(FALSE);
			cou1=cycle(cou1,np,'+');
		}
		if(cou2!=cycle(posright,np,'+')){
			if(pt[cou2].x>pt[cycle(cou2,np,'-')].x)return(FALSE);
			cou2=cycle(cou2,np,'-');
		}
	}
	return(TRUE);
}
//--------------------------------------
void vline(point p1,point p2){
	line(p1.x,480-p1.y,p2.x,480-p2.y);
}
void vputpixel(point p1,int color){
	putpixel(p1.x,480-p1.y,color);
}
void vmoveto(point p){
	moveto(p.x,480-p.y);
}
void vrectangle(point p1,point p2){
	rectangle(p1.x,480-p1.y,p2.x,480-p2.y);
}
void triangle(point p1,point p2,point p3){
	vline(p1,p2);vline(p2,p3);vline(p3,p1);
}
void vcircle(point p,int radius){
	circle(p.x,480-p.y,radius);
}
int turn(point p1,point p2,point p3){
	//....check if 1-2-3 is a left or a right turn
	long c= p2.x-p1.x;
	long d= p3.x-p2.x;
	long e= p3.y-p2.y;
	long f= p2.y-p1.y;
	if(c*e>=d*f)return(LEFT);
	else return(RIGHT);
}
float anglesubtendedby(point p1,point p2){
	if(p1.x>p2.x){
		if(p1.y>p2.y)	return(atan(float(p1.y-p2.y)/(p1.x-p2.x)));
		else         	return(PI*2-atan(float(p2.y-p1.y)/(p1.x-p2.x)));
	}
	if(p1.x<p2.x){
		if(p1.y>p2.y)	return(PI-atan(float(p1.y-p2.y)/(p2.x-p1.x)));
		else         	return(PI+atan(float(p2.y-p1.y)/(p2.x-p1.x)));
	}
	if(p1.x==p2.x){
		if(p1.y>p2.y)return(PI);
		else if(p1.y<p2.y)return(3*PI/2);
		else return(0);
	}
	return 0;
}
void check(point p){
	if(p.x>600&&p.y<20){closegraph();exit(0);}
}
int cycle(int no,int np,char ch){
	//.......finds next no. in the cycle of numbers from 0 to (np-1)
	//.......in positive or negative side
	if(ch=='+')return((no+1)%np);
	if(no==0)return(np-1);
	else return(no-1);
}
void grid(int interval){
	setcolor(8);
	for(int i=0;i<640;i+=interval)
		line(i,480,i,0);
	for(int j=1;j<480;j+=interval)
		line(0,480-j,640,480-j);
}