//.........A PROGRAM DEVELOPED BY==============> VIPUL MISTRY
//.........IN THIS PROGRAM CONVENTIONS FOR 3 AXES ARE AS FOLLOWS
//.........                      Z
//.........                      ³
//.........                      ³
//.........                     /ÀÄÄÄÄÄÄÄX
//.........                   Y (outward)
//.........
//.........there is a slight problem with the conventions of x y z taken above in figure
//.........
#include<iostream.h>
#include <graphics.h>
#include <conio.h>
#include<bios.h>
#include<math.h>
#include<process.h>
#define Yes 1
#define No 0
void al_error(){
  cout<<"\n\nMemory Allocation error............";getch();
  exit(0);
}
class point{
 public:
   double x,y,z;   //......cordinates of point
   void transform(char axis,char dir,double angle){
    if(dir=='c')angle=-angle;   //....if clockwise 'c'
    //.......'x' axis means we see from positive side of x axis
    //.......'dir' shows how to rotate the object clkwise('c') or anticlkwise('a')
    double a,b;
    if(axis=='x'){  a = z*cos(angle)-y*sin(angle);
		    b = z*sin(angle)+y*cos(angle);
		    z=a;y=b;
		 }
    if(axis=='y'){  a = x*cos(angle)-z*sin(angle);
		    b = x*sin(angle)+z*cos(angle);
		    x=a;z=b;
		 }
    if(axis=='z'){  a = y*cos(angle)-x*sin(angle);
		    b = y*sin(angle)+x*cos(angle);
		    y=a;x=b;
		 }
   }
   void put(double xx,double yy,double zz)  { x=xx;y=yy;z=zz; }
};
class box{
//protected
 public:
	int n_pts,n_join;
	point *pts; //.....all points are stored in it
	int **join; //....all pts are marked as numbers
		    //....and join stores a (n_join,2) array of points
		    //....where each row denotes a line
	int **plane;//....a plane is specified by linked list of numbers
		    //....where numbers denote points
		    //....**plane is array of planes
	int xcur,ycur,zcur;  //....denotes the cordinates of center point of figure
	int show_dash;  //....flag which tells whether to show
			//....hidden lines or not
	int draw_color; //.....set drwaing color
	int view;       //...view=0 means four views and view=1 means one view
//public:
	void box_initialise(int,int,int,int);   //.....to initialise points etc.
	~box();               //....destructor
	void draw(int,int,int,char,int);
	void erase();
	void rotate();
	int find_ymin();
	int check_hidden(int);
	void transform_pts(char,char,double);
};
void box::box_initialise(int num_of_points,int num_of_lines,int color,int vview){
	   n_pts=num_of_points;
	   n_join=num_of_lines;
	   draw_color=color;
	   view=vview;
	   xcur=0;ycur=0;zcur=0;//..xcur,ycur,zcur gives cordinates of
				  //..centre of object being drawn which may change
				  //..with the translation of object
	   show_dash=Yes;    //..show hidden lines
	   if(!(pts=new point[n_pts]))al_error(); //  |
	   if(!(join=new int*[n_join]))al_error();//  |====>memory allocation
	   for(int i=0;i<n_join;i++)              //  |
		 if(!(join[i]=new int[2]))al_error();//  |
	}
box::~box(){
	  delete(pts);
	  for(int i=0;i<n_join;i++)delete join[i];
	  delete join;
	}
int box::find_ymin()
{ double small=pts[0].y;int pos=0;
  for(int i=1;i<n_pts;i++){
	if(pts[i].y<small)
	{ pos=i;small=pts[i].y;}
  }
  return(pos);
}
void box::rotate()
{ double angle,degree;
  int t=1;//.....as a increment for xcur or ycur
	  //increasing its value make translation possible
  angle=degree=3.14/180;     //.......1 radian
begin:
  gotoxy(1,1);
  cout<<"Rotation in degrees = "<<(angle*180/3.14)<<"  ";//..'angle' is angle by which it rotates in one stroke of key
			//..less 'angle' means less speed of rotation
  cout<<"\nTranslation Step size = "<<t<<"  ";

  if(view==0)
  {	draw(107,120,draw_color,'x',1);
	draw(107+215,120,draw_color,'y',1);
	draw(107+215+215,120,draw_color,'x',2);
	draw(107+215,120+240,draw_color,'z',1);
	setcolor(LIGHTGRAY);
	line(0,240,639,240);
	line(215,0,215,480);
	line(215+215,0,215+215,480);
	outtextxy(215+215+20,450,"Orthographic Parallel");
	outtextxy(215+215+20,460,"     Projections");
	outtextxy(215+215+20,470,"(Third Angle View)");
	outtextxy(70,230,"Right Side View");
	outtextxy(70+215,230,"Front View");
	outtextxy(70+215+215,230,"Left Side View");
	outtextxy(70+215,230+240,"Top View");
  }
  else{
	draw(320,240,draw_color,'y',1);
	setcolor(LIGHTGRAY);
	outtextxy(70+200,450,"Isometric Viewing");
	outtextxy(70+215,430,"Front View");
  }

  switch(bioskey(0))
  { case 19712://....to go to right
		  erase();transform_pts('z','a',angle);break;
    case 19200://....to go to left
		  erase();transform_pts('z','c',angle);break;
    case 18432://....to go to up
		  erase();transform_pts('x','c',angle);break;
    case 20480://....to go to down
		  erase();transform_pts('x','a',angle);break;
    case 11386://......z pressed
		  erase();transform_pts('y','a',angle);break;
    case 11640://......x pressed
		  erase();transform_pts('y','c',angle);break;
		  //....ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    case 20530://......to translate in -ve z ³
		  //......numpad 2                 ³
			erase();zcur-=t;break; //	³
    case 18488://......to translate in +ve z	³
		  //......numpad 8                 ³
		  erase();zcur+=t;break; //		³
    case 19252://......to translate in -ve x	³
		  //......numpad 4                 ³
		  erase();xcur-=t;break; //		³
    case 19766://......to translate in +ve x	ÃÄÄÄÄÄÄ>translation of figure
		  //......numpad 6                 ³
		  erase();xcur+=t;break; //		³
    case 18231://......to translate in -ve y ³
		  //......numpad 7                 ³
		  erase();ycur-=t;break; //        ³
    case 18745://......to translate in +ve y ³
		  //......numpad 9                 ³
		  erase();ycur+=t;break; //        ³
		  //.......ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    case 18176://......home pressed to get back to original position
		  erase();xcur=ycur=zcur=0;break;
    case 12386://......b pressed i.e. to enlarge the object
		  erase();
		  for(int i=0;i<n_pts;i++)
		  { pts[i].x=pts[i].x*6/5;
		 pts[i].y=pts[i].y*6/5;
		 pts[i].z=pts[i].z*6/5;
		  }
		  break;
    case 8051 ://........s pressed i.e. to shrink the object
		  erase();
		  for(i=0;i<n_pts;i++)
		  { pts[i].x=pts[i].x*5/6;
		 pts[i].y=pts[i].y*5/6;
		 pts[i].z=pts[i].z*5/6;
		  }
		  break;
    case 5993 ://........i pressed, increase speed of rotation
		  angle+=degree;break;
    case 8292 ://........d pressed, decrease speed of rotation
		  if(angle>=degree*2)angle-=degree;break;
    case 6255 ://........o pressed
		  erase();show_dash=(show_dash==Yes)?No:Yes;break;
    case 283  ://........escape pressed
		  return;
    case 5236:	//......t pressed
			t++;break;
    case 5497:	//.......y pressed
			if(t>=2)t--;break;
/*    case 12150://....v pressed
			view=1-view;
			break;*/
    default   :goto begin;
  }
  goto begin;
}
void box::transform_pts(char axis,char dir,double angle)
{  for(int p=0;p<n_pts;p++)
	pts[p].transform(axis,dir,angle);
}
void box::draw(int x_screen_center,int y_screen_center,int color,
		  char axis,int dir)  //....'axis' is axis about which you are seeing
				  //....and 'dir' is +ve(=1) or -ve(=2) side of the axis
{ int xcenter=x_screen_center; //....draw with specified cordinates on screen
  int ycenter=y_screen_center;
  int i;

  //.........draw hidden lines
  setlinestyle(3,1,1);setcolor(color);  //...set style to dash line and color gray
  for(i=0;i<n_join;i++){
    if(check_hidden(i)==0){//.....if ith line is hidden
	 if(show_dash==Yes)
	 line(xcenter+pts[join[i][0]].x,ycenter-pts[join[i][0]].z,
	  xcenter+pts[join[i][1]].x,ycenter-pts[join[i][1]].z);
    }
  }
  //.....draw solid lines
  setlinestyle(0,1,1);setcolor(color);  //...set style to solid line and color white
  for(i=0;i<n_join;i++){
    if(check_hidden(i)==1){ //....if the ith line is not hidden line
	//.....now draw according to axis and dir
	if(axis=='y')
	{ if(dir==1)line(xcenter+xcur+pts[join[i][0]].x,ycenter-zcur-pts[join[i][0]].z,
			 xcenter+xcur+pts[join[i][1]].x,ycenter-zcur-pts[join[i][1]].z);
	  else      line(xcenter-xcur-pts[join[i][0]].x,ycenter-zcur-pts[join[i][0]].z,
			 xcenter-xcur-pts[join[i][1]].x,ycenter-zcur-pts[join[i][1]].z);
	}
	if(axis=='x')
	{ if(dir==1)line(xcenter-ycur-pts[join[i][0]].y,ycenter-zcur-pts[join[i][0]].z,
			 xcenter-ycur-pts[join[i][1]].y,ycenter-zcur-pts[join[i][1]].z);
	  else        line(xcenter+ycur+pts[join[i][0]].y,ycenter-zcur-pts[join[i][0]].z,
			 xcenter+ycur+pts[join[i][1]].y,ycenter-zcur-pts[join[i][1]].z);
	}
	if(axis=='z')
	{ if(dir==1)line(xcenter+xcur+pts[join[i][0]].x,ycenter+ycur+pts[join[i][0]].y,
			 xcenter+xcur+pts[join[i][1]].x,ycenter+ycur+pts[join[i][1]].y);
	  else        line(xcenter+xcur+pts[join[i][0]].x,ycenter-ycur-pts[join[i][0]].y,
			 xcenter+xcur+pts[join[i][1]].x,ycenter-ycur-pts[join[i][1]].y);
	}
    }
  }
}
int box::check_hidden(int f)
{  /* int pos_ymin=find_ymin();
    if(join[f][0]!=pos_ymin&&join[f][1]!=pos_ymin)
	 return(1);//....false means not hidden
    else return(0); //....true means hidden*/
    return(1);
}
void box::erase()
{ if(view==0)
  {  	draw(107,120,BLACK,'x',1);
	draw(107+215,120,BLACK,'y',1);
	draw(107+215+215,120,BLACK,'x',2);
	draw(107+215,120+240,BLACK,'z',1);
  }
  else draw(320,240,BLACK,'y',1);
}
class cuboid: public box{
 public:cuboid(int x,int y,int z,int color,int view){
		 box_initialise(8,12,color,view);
		 pts[0].put(x/2,y/2,-z/2);pts[1].put(x/2,y/2,z/2);
		 pts[2].put(-x/2,y/2,z/2);pts[3].put(-x/2,y/2,-z/2);
		 pts[4].put(x/2,-y/2,-z/2);pts[5].put(x/2,-y/2,z/2);
		 pts[6].put(-x/2,-y/2,z/2);pts[7].put(-x/2,-y/2,-z/2);
		 int arr[12][2]={ {0,1},{1,2},{2,3},{3,0},
			    {4,5},{5,6},{6,7},{7,4},
			    {0,4},{3,7},{2,6},{1,5}
			  };
		 for(int i=0;i<12;i++)
		  { join[i][0]=arr[i][0];join[i][1]=arr[i][1];}
	  }
};
class tetrahedron:public box{
  public:tetrahedron(int x,int color,int view){
	   box_initialise(4,6,color,view);
	   double s3=sqrt(3.0);
	   pts[0].put(x/s3,0,0);
	   pts[1].put(-x/(2*s3),x/2,0);
	   pts[2].put(-x/(2*s3),-x/2,0);
	   pts[3].put(0,0,(sqrt(2.0)/s3)*x);
	   int arr[6][2]={ {0,1},{0,2},{0,3},{1,2},{1,3},{2,3} };
	   for(int i=0;i<6;i++){join[i][0]=arr[i][0];join[i][1]=arr[i][1];}
	 }
};
class hexagon:public box{
  public:hexagon(int color,int view){
	   box_initialise(12,18,color,view);
	   double s3=sqrt(3.0);
	   float hi=5.;
	   pts[0].put(1,0,hi/2);
	   pts[1].put(.5,s3/2,hi/2);
	   pts[2].put(-.5,s3/2,hi/2);
	   pts[3].put(-1,0,hi/2);
	   pts[4].put(-.5,-s3/2,hi/2);
	   pts[5].put(.5,-s3/2,hi/2);
	   pts[6].put(1,0,-hi/2);
	   pts[7].put(.5,s3/2,-hi/2);
	   pts[8].put(-.5,s3/2,-hi/2);
	   pts[9].put(-1,0,-hi/2);
	   pts[10].put(-.5,-s3/2,-hi/2);
	   pts[11].put(.5,-s3/2,-hi/2);
	   int arr[18][3]={ 	{0,1},{1,2},{2,3},
				{3,4},{4,5},{5,0},

				{6,7},{7,8},{8,9},
				{9,10},{10,11},{11,6},

				{0,6},{1,7},{2,8},
				{3,9},{4,10},{5,11}
			};
	   for(int i=0;i<18;i++){join[i][0]=arr[i][0];join[i][1]=arr[i][1];}
	 }
};
void main()
{
   clrscr();
   cout<<"\n\n\n\n\n\t\tA Program of Orthographic Parallel Projections";
   cout<<"\n\n\t\tand Isometric Viewing of 3D Solid Models.";
   cout<<"\n\n\n\t\t\t\t\t\tBy :- VIPUL MISTRY";
   cout<<"\n\t\t\t\t\t\t      B.Tech(3rd Year)(CSE)";
   cout<<"\n\n\nPress any key to continue.........";
   getch();
while(1){
   clrscr();
   cout<<"\n\n\n\n\t\t\t1.) Draw a Tetrahedron";
   cout<<"\n\n\n\n\t\t\t2.) Draw a Hexagon";
   cout<<"\n\n\n\n\t\t\t3.) Draw a Cuboid";
   cout<<"\n\n\n\n\t\t\t4.) Exit";
   cout<<"\n\n\n\n\n\t\tEnter your choice.....";
   int ch;cin>>ch;
   if(ch==4)break;

   clrscr();
   cout<<"\n\n\n\n\n\n\t\t\t1.) Orthographic Parallel Projections";
   cout<<"\n\n\n\n\t\t\t2.) Isometric View";
   cout<<"\n\n\n\n\t\tEnter the view that you want to see.....";
   int view;cin>>view;
   if(view==1)view=0;
   else view=1;
   int x,y,z;x=100;y=50;z=100;
   int color=WHITE;

   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "\\tc\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
	 cout<<"Graphics error: "<<grapherrormsg(errorcode)<<"\n";
	 cout<<"Press any key to halt:";
	 getch();
	 return; /* terminate with an error code */
   }

   tetrahedron    t(x,color,view);
   cuboid c(x,y,z,color,view);
   hexagon h(color,view);
   switch(ch){
	case 1:t.rotate();closegraph();break;
	case 2:h.rotate();closegraph();break;
	case 3:c.rotate();closegraph();break;
   }
}//.......end while
}