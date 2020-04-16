#include<process.h>
#include<bios.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
class vector{
	public:	int x,y;
			vector(){}
			vector(vector &v){
				x=v.x;y=v.y;
			}
			void put(int x1,int y1){
				x=x1;y=y1;
			}
			void put(vector pt){
				x=pt.x;y=pt.y;
			}
			void get(int &x1,int &y1){
				x1=x;y1=y;
			}
			void get(vector &pt){
				pt.x=x;pt.y=y;
			}
			friend int operator==(vector,vector);
};
typedef vector point;
int operator==(vector v1, vector v2){
	if((v1.x==v2.x)&&(v1.y==v2.y))return 1;
	return 0;
}
void vline(point pt1,point pt2){
	int x1,y1,x2,y2;
	pt1.get(x1,y1);
	pt2.get(x2,y2);
	line(x1,y1,x2,y2);
}
void vmoveto(point p){
	int x,y;
	p.get(x,y);
	moveto(x,y);
}
//--------------------------------------------------
union REGS i,o;
class vmouse
{
public:
	void showmouseptr();
	void hidemouseptr();
	void restrictmouseptr(int,int,int,int);
	void getmousepos(int*,int*,int*);
	int initmouse();
	void waitforrightclick();
	void getpt(point&);
	void getpt(int&,int&);
};
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
	*y=o.x.dx;
}
void vmouse::waitforrightclick(){
	int x,y,button;
	showmouseptr();
	while(1){
		getmousepos(&button,&x,&y);
		if((button & 2)==2){
			while((button & 2)==2)	getmousepos(&button,&x,&y);
			break;
		}
		else continue;
	}
	hidemouseptr();
}
void vmouse::getpt(point &pt){
	int x,y,button;
	showmouseptr();
	while(1){
		getmousepos(&button,&x,&y);
		if((button & 1)==1)
		{
			while((button & 1)==1)getmousepos(&button,&x,&y);
			pt.put(x,y);
			hidemouseptr();
			putpixel(x,y,15);
			break;
		}
	}
}
void vmouse::getpt(int &x1,int &y1){
	int x,y,button;
	showmouseptr();
	while(1){
		getmousepos(&button,&x,&y);
		if((button & 1)==1)
		{
			while((button & 1)==1)getmousepos(&button,&x,&y);
			x1=x;y1=y;
			hidemouseptr();
			putpixel(x,y,15);
			break;
		}
	}
}