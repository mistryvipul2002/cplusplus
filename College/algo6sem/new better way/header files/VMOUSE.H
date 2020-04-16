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
	*x=(*x)/PIXELHEIGHT;
	*y=(*y)/PIXELHEIGHT;
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
	int x,y;
	while(1){
		getmousepos(button,&x,&y);
		while((*button&1)!=1&&(*button&2)!=2)getmousepos(button,&x,&y);
		if((*button&1)==1){
			while((*button&1)==1)getmousepos(button,&x,&y);
			p.x=x;p.y=y;
			hidemouseptr();
			return(LEFT);
		}
		else if((*button&2)==2){
				while((*button&2)==2)getmousepos(button,&x,&y);
				p.x=x;p.y=y;
				hidemouseptr();
				return(RIGHT);
			}
	}
}
