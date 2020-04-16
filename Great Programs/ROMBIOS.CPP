#include<conio.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include<iostream.h>
union REGS i,o;
int a;
void videomodes()
{
	i.h.ah=0x00;
	i.h.al=0x0;
	int86(0x10,&i,&o);
	cout<<"Different Video Modes\n";
	cout<<"\n\n\t40x25 text 16 grey";
	bioskey(0);
	i.h.al=0x2;
	int86(0x10,&i,&o);
	cout<<"Different Video Modes\n";
	cout<<"\n\n\t80x25 text 16 grey";
	bioskey(0);
	i.h.al=0x4;
	int86(0x10,&i,&o);
	cout<<"Different Video Modes\n";
	cout<<"\n\n\t320x200 graphics 4 colors";
	bioskey(0);
	i.h.al=0x6;
	int86(0x10,&i,&o);
	cout<<"Different Video Modes\n";
	cout<<"\n\n\t640x200 graphics mono";
	bioskey(0);
	i.h.al=0x11;
	int86(0x10,&i,&o);
	cout<<"Different Video Modes\n";
	cout<<"\n\n\t640x480 graphics 2 color";
	bioskey(0);

	i.h.al=0x3;
	int86(0x10,&i,&o);
	cout<<"Text Mode restored to 80x25 text 16/8 color\n";
	cout<<"Press any key to continue...";
	bioskey(0);
}
void cursorsize()
{
	clrscr();
	i.h.ah=0x01;
	i.h.ch=15;     //.....start line
	i.h.cl=15;     //.....end line
	int86(0x10,&i,&o);
	cout<<"Type single digit numbers to check cursor size......\n";
	cout<<"Cursor size small 15 to 15\n";
	cin>>a;

	i.h.ch=11;     //.....start line
	i.h.cl=15;     //.....end line
	int86(0x10,&i,&o);
	cout<<"Cursor Size big from 11 to 15\n";
	cin>>a;

	i.h.ch=0;     //.....start line
	i.h.cl=15;     //.....end line
	int86(0x10,&i,&o);
	cout<<"Cursor Size big from 0 to 15\n";
	cin>>a;

	i.h.ch=14;     //.....start line
	i.h.cl=15;     //.....end line
	int86(0x10,&i,&o);
	cout<<"Cursor Size restored from 14 to 15\n";
	cin>>a;
}
void cursorpos()
{
	clrscr();
	cout<<"Cursor position set to row 10 column 25. Enter anything...\n";
	i.h.ah=0x02;
	i.h.dh=10;	//row
	i.h.dl=25;	//column
	int86(0x10,&i,&o);
	cin>>a;
}
void getvideomode()
{
	clrscr();

	int gd=DETECT,gm;

	initgraph(&gd,&gm,"");

	cout<<"Current video mode :-\n";
	i.h.ah=0x0F;
	int86(0x10,&i,&o);
	cout<<"\nNo. of chracters columns on screen : -"<<(int)o.h.al;
	cout<<"\nVideo mode : -"<<(int)o.h.al;
	cout<<"\nPage number : - "<<(int)o.h.bh;
	getch();
	closegraph();
}
void main()
{
	videomodes();
	cursorsize();
	cursorpos();
	getvideomode();
}