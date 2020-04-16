template <class T> void swap(T &p1,T &p2){
	T temp;
	temp=p1;
	p1=p2;
	p2=temp;
}
int round_special(float);
//------------primitive functions
int PIXELHEIGHT=1;
void setpixelheight(int x){
	if(x<=0)PIXELHEIGHT=1;
	PIXELHEIGHT=x;
}
void vputpixel(int x1,int y1,int color){
	setcolor(color);
	for(int i=x1*PIXELHEIGHT;i<(x1+1)*PIXELHEIGHT;i++){
		line(i,479-y1*PIXELHEIGHT,i,479-((y1+1)*PIXELHEIGHT-1));
	}
}
void vmoveto(int x1,int y1){
	moveto(x1*PIXELHEIGHT,479-y1*PIXELHEIGHT);
}
int vgetmaxx(){
	return(639/PIXELHEIGHT);
}
int vgetmaxy(){
	return(479/PIXELHEIGHT);
}
//---------------derived functions
void vline(POINT_DATA x1,POINT_DATA y1,POINT_DATA x2,POINT_DATA y2){
	//.............this uses scan line algorithm DDA
	vputpixel(x1,y1,getcolor());
	vputpixel(x2,y2,getcolor());

	if(x2==x1){
		for(POINT_DATA i=(y1>y2?y2:y1);i<=(y2>y1?y2:y1);i++)
			vputpixel(x1,i,getcolor());
		return;
	}
	float m=double(y2-y1)/(x2-x1);
	if(m<=1&&m>=-1){
		if(x1>x2)	{swap(x1,x2);swap(y1,y2);}
		float prevy=y1;
		for(POINT_DATA i=x1+1;i<=x2;i++){
			vputpixel(i,round_special(prevy+m),getcolor());
			prevy=prevy+m;
		}
	}
	else{
		if(y1>y2) {swap(x1,x2);swap(y1,y2);}
		m=1/m;
		float prevx=x1;
		for(POINT_DATA i=y1+1;i<=y2;i++){
			vputpixel(round_special(prevx+m),i,getcolor());
			prevx=prevx+m;
		}
	}
}
void vline(point p1,point p2){
	vline(p1.x,p1.y,p2.x,p2.y);
}
void vmoveto(point p){
	vmoveto(p.x,p.y);
}
void vputpixel(point p1,int color){
	vputpixel(p1.x,p1.y,color);
}
void vrectangle(point p1,point p2){
	vline(p1.x,p1.y,p2.x,p1.y);
	vline(p1.x,p1.y,p1.x,p2.y);
	vline(p2.x,p2.y,p2.x,p1.y);
	vline(p2.x,p2.y,p1.x,p2.y);
}
void triangle(point p1,point p2,point p3){
	vline(p1,p2);vline(p2,p3);vline(p3,p1);
}
void vcircle(point p,int radius){
	circle(p.x,480-p.y,radius);
}
//---------------------other derived functions
void check_if_exit_is_clicked(point p){
	if(p.x>600.0/PIXELHEIGHT&&p.y<20.0/PIXELHEIGHT){closegraph();exit(0);}
}
int next(int no,int np){
	//.......finds next no. in the cycle of numbers from 0 to (np-1)
	//.......in positive side
	return((no+1)%np);
}
int before(int no,int np){
	//.......finds next no. in the cycle of numbers from 0 to (np-1)
	//.......in negative side
	if(no==0)return(np-1);
	else return(no-1);
}
void grid(int interval){
	setcolor(8);
	for(int i=0;i<640;i+=interval)
		line(i,479,i,0);
	for(int j=0;j<480;j+=interval)
		line(0,479-j,639,479-j);
}
int round_special(float i){
	int j=(int)i;
	if(i>(float)(j+.5))return(j+1);
	return(j);
}