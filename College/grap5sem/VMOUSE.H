#include<process.h>
#include<bios.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
union REGS i,o;
class vmouse
{
public:
	void showmouseptr();
	void hidemouseptr();
	void restrictmouseptr(int,int,int,int);
	void getmousepos(int*,int*,int*);
	int initmouse();
	void getpt(int&,int&);
	void waitforrightclick();
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
