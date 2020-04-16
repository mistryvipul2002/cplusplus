#include<math.h>
#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
const int np=5;
void toscreen(float **arr){
	for(int i=0;i<np;i++){
		arr[i][0]+=320;
		arr[i][1]=240-arr[i][1];
	}
}
void screento(float **arr){
	for(int i=0;i<np;i++){
		arr[i][0]-=320;
		arr[i][1]=240-arr[i][1];
	}
}
void draw(float **arr){
	clearviewport();
	setcolor(4);
	line(0,240,640,240);
	line(320,0,320,480);
	setcolor(10);
	toscreen(arr);
	for(int i=0;i<np-1;i++){
		line(arr[i][0],arr[i][1],arr[i+1][0],arr[i+1][1]);
	}
	line(arr[0][0],arr[0][1],arr[np-1][0],arr[np-1][1]);
	getch();
	screento(arr);
}
void main()
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
   float **arr=new float*[np];
   for(int i=0;i<np;i++)arr[i]=new float[2];
   arr[0][0]=0;arr[0][1]=0;
   arr[1][0]=0;arr[1][1]=100;
   arr[2][0]=50;arr[2][1]=150;
   arr[3][0]=100;arr[3][1]=100;
   arr[4][0]=100;arr[4][1]=0;
   draw(arr);

a: clearviewport();
   gotoxy(1,1);
   cout<<"\n\n\n\n\t\t\t1) Translation";
   cout<<"\n\n\t\t\t2) Rotation";
   cout<<"\n\n\t\t\t3) Scaling";
   cout<<"\n\n\t\t\t4) Shear";
   cout<<"\n\n\t\t\t5) Exit";
   cout<<"\n\n\t\tEnter your choice......";
   int cho,xref,yref;cin>>cho;
   switch(cho){
	case 1:int xtr,ytr;
		  cout<<"\n\n\t\tEnter x translation....";cin>>xtr;
		  cout<<"\t\tEnter y translation....";cin>>ytr;
		  cout<<"\t\tEnter reference point x = ";cin>>xref;
		  cout<<"\t\tEnter reference point y = ";cin>>yref;
		  for(int i=0;i<np;i++){
			arr[i][0]+=xtr;
			arr[i][1]+=ytr;
		  }
		  draw(arr);
		  goto a;
	case 2:float Q;
		  cout<<"\n\n\t\tEnter angle (in degrees) for anticlockwise rotation....";cin>>Q;
		  cout<<"\t\tEnter reference point x = ";cin>>xref;
		  cout<<"\t\tEnter reference point y = ";cin>>yref;
		  Q=Q*3.14/180.;
		  for(i=0;i<np;i++){
			float x=arr[i][0],y=arr[i][1];
			arr[i][0]-=xref;
			arr[i][1]-=yref;
			arr[i][0]=x*cos(Q)-y*sin(Q);
			arr[i][1]=x*sin(Q)+y*cos(Q);
			arr[i][0]+=xref;
			arr[i][1]+=yref;
		  }
		  draw(arr);
		  goto a;
	case 3:float sx,sy;
		  cout<<"\n\n\t\tEnter scaling in x....";cin>>sx;
		  cout<<"\t\tEnter scaling in y....";cin>>sy;
		  cout<<"\t\tEnter reference point x = ";cin>>xref;
		  cout<<"\t\tEnter reference point y = ";cin>>yref;
		  for(i=0;i<np;i++){
			arr[i][0]-=xref;
			arr[i][1]-=yref;
			arr[i][0]*=sx;
			arr[i][1]*=sy;
			arr[i][0]+=xref;
			arr[i][1]+=yref;
		  }
		  draw(arr);
		  goto a;
	case 4:float s;int x;
		  cout<<"\n\n\t\tFor shear in x enter 1, for shear in y enter 2....";cin>>x;
		  cout<<"\t\tEnter amount of shear....";cin>>s;
		  cout<<"\t\tEnter reference point x = ";cin>>xref;
		  cout<<"\t\tEnter reference point y = ";cin>>yref;
		  for(i=0;i<np;i++){
			arr[i][0]-=xref;
			arr[i][1]-=yref;
			if(x==1)arr[i][0]=arr[i][0]+s*arr[i][1];
			else arr[i][1]=arr[i][1]+s*arr[i][0];
			arr[i][0]+=xref;
			arr[i][1]+=yref;
		  }
		  draw(arr);
		  goto a;
	case 5:break;
	default:goto a;
   }
   for(i=0;i<np;i++)delete arr[i];
   delete arr;
   closegraph();
}