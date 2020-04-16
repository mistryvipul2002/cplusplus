#include<vmousenw.h>
void main(){
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  // an error occurred
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); // terminate with an error code
	}

	//.......initialise mouse
	int maxx=getmaxx(),maxy=getmaxy();
	if(v.initmouse()==0)
	{
		closegraph();
		restorecrtmode();
		printf("\nMouse driver not loaded");
		exit(1);
	}
	v.restrictmouseptr(0,0,maxx,maxy);

	moveto(200,10);
	setcolor(10);
	outtext("Convex Polygon Inclusion Algorithm");
	moveto(600,460);
	outtext("Exit");

	//.....store the points using mouse
	polygon poly;
	//.....enter the lines
	poly.input();
	//......check if it is monotone polygon
	if(!poly.monotone_wrt_x_axis()){
		cout<<"Not a monotone polygon......";
		v.waitforrightclick();
		exit(0);
	}

	//............find leftmost and rightmost point in pt
	point left=poly.pt[0],right=poly.pt[0];
	int posleft=0,posright=0;
	for(int i=0;i<poly.np;i++){
		if(poly.pt[i].x<left.x){left=poly.pt[i];posleft=i;}
		if(poly.pt[i].x>right.x){right=poly.pt[i];posright=i;}
	}

	//............print poly
	v.waitforrightclick();
	clearviewport();
	cout<<"polygon you entered....";
	setcolor(10);char str[]="a";
	for(i=0;i<poly.np-1;i++){
		vline(poly.pt[i],poly.pt[i+1]);
		vmoveto(poly.pt[i]);
		outtext(str);
		++str[0];
	}
	vmoveto(poly.pt[i]);
	outtext(str);
	vline(poly.pt[poly.np-1],poly.pt[0]);
	vmoveto(left);outtext("  Left");
	vmoveto(right);outtext("  Right");

	//....check if points are in clockwise fashion
	if(turn(poly.pt[cycle(posleft,poly.np,'-')],poly.pt[posleft],poly.pt[cycle(posleft,poly.np,'+')])==LEFT){
		//......orient the polygn in reverse direction
		for(int i=0;i<poly.np/2;i++)
			swap(poly.pt[i],poly.pt[(poly.np-1)-i]);
		//......again calculate left,right,posleft,posright
		left=poly.pt[0],right=poly.pt[0];
		posleft=0,posright=0;
		for(i=0;i<poly.np;i++){
			if(poly.pt[i].x<left.x){left=poly.pt[i];posleft=i;}
			if(poly.pt[i].x>right.x){right=poly.pt[i];posright=i;}
		}
	}

	//............print poly
	v.waitforrightclick();
	clearviewport();
	cout<<"after making clockwise...";
	setcolor(10);str[0]='a';str[1]='\0';
	for(i=0;i<poly.np-1;i++){
		vline(poly.pt[i],poly.pt[i+1]);
		vmoveto(poly.pt[i]);
		outtext(str);
		++str[0];
	}
	vmoveto(poly.pt[i]);
	outtext(str);
	vline(poly.pt[poly.np-1],poly.pt[0]);
	vmoveto(left);outtext("  Left");
	vmoveto(right);outtext("  Right");

	//.........make new "ptnew" which store for each point whether
	//.......it lies in Upper polygonal chain or in the lower one
	struct point_with_position{
		point p;
		int pos;
	}ptnew[MAX];
	int cou1=posleft,cou2=posleft;
	while(cou1!=posright){
		ptnew[cou1].p=poly.pt[cou1];
		ptnew[cou1].pos=UP;
		cou1=cycle(cou1,poly.np,'+');
	};
	while(cou2!=posright){
		ptnew[cou2].p=poly.pt[cou2];
		ptnew[cou2].pos=DOWN;
		cou2=cycle(cou2,poly.np,'-');
	};
	ptnew[posright].p=poly.pt[posright];
	ptnew[posright].pos=UP;

	//...................print ptnew
	v.waitforrightclick();
	clearviewport();
	cout<<"ptnew constructed with pos of each point......";
	setcolor(10);str[0]='a';str[1]='\0';
	for(i=0;i<poly.np-1;i++){
		vline(ptnew[i].p,ptnew[i+1].p);
		vmoveto(ptnew[i].p);
		outtext(str);
		if(ptnew[i].pos==UP)outtext(" (UP)");
		else outtext(" (DOWN)");
		++str[0];
	}
	vmoveto(ptnew[i].p);
	outtext(str);
	if(ptnew[i].pos==UP)outtext(" (UP)");
	else outtext(" (DOWN)");
	vline(ptnew[poly.np-1].p,ptnew[0].p);
	vmoveto(left);outtext("        Left");
	vmoveto(right);outtext("       Right");

	//..........now we have got the ptnew with position of each point
	//........so sort it wrt x cordinate
	int pos;point_with_position less;
	for(i=0;i<poly.np;i++){
		pos=i;less=ptnew[i];
		for(int j=i+1;j<poly.np;j++){
			if(ptnew[j].p.x<less.p.x){
				less=ptnew[j];pos=j;
			}
		}
		swap(ptnew[pos],ptnew[i]);
	}

	//........print ptnew
	v.waitforrightclick();
	clearviewport();
	cout<<"ptnew now sorted...";
	setcolor(10);str[0]='a';str[1]='\0';
	for(i=0;i<poly.np-1;i++){
		vline(ptnew[i].p,ptnew[i+1].p);
		vmoveto(ptnew[i].p);
		outtext(str);
		if(ptnew[i].pos==UP)outtext(" (UP)");
		else outtext(" (DOWN)");
		++str[0];
	}
	vmoveto(ptnew[i].p);
	outtext(str);
	if(ptnew[i].pos==UP)outtext(" (UP)");
	else outtext(" (DOWN)");
	vline(ptnew[poly.np-1].p,ptnew[0].p);
	vmoveto(left);outtext("        Left");
	vmoveto(right);outtext("       Right");
	v.waitforrightclick();


	//........print polygon in which triangulation will be shown
	clearviewport();
	cout<<"polygon triangulated...";
	setcolor(15);str[0]='a';str[1]='\0';
	for(i=0;i<poly.np-1;i++){
		vline(poly.pt[i],poly.pt[i+1]);
		vmoveto(poly.pt[i]);
		outtext(str);
		++str[0];
	}
	vmoveto(poly.pt[i]);
	outtext(str);
	vline(poly.pt[poly.np-1],poly.pt[0]);

	//.........apply algorithm
	setcolor(10);
	stack <point_with_position> stk;
	stk.push(ptnew[0]);
	stk.push(ptnew[1]);
	for(i=2;i<poly.np;i++){
		if(i==poly.np-1){  	//......vi adjacent to stk_top and stk_bottom
						//......which is possible for rightmost point
			point_with_position stop=stk.pop(),stopnext;
			while(!stk.empty()){
				stopnext=stk.pop();
				triangle(ptnew[i].p,stop.p,stopnext.p);
				stop=stopnext;
			}
		}
		else{
			if(ptnew[i].pos==(stk.stacktop()).pos){
				//......vi adjacent to stk_top and not to stk_bottom
				point_with_position stop=stk.pop(),stopnext;
				while(!stk.empty()){
					stopnext=stk.pop();
					if(ptnew[i].pos==DOWN){
						if(turn(ptnew[i].p,stop.p,stopnext.p)==RIGHT)
							triangle(ptnew[i].p,stop.p,stopnext.p);
						else{
							stk.push(stopnext);
							break;
						}
					}
					if(ptnew[i].pos==UP){
						if(turn(ptnew[i].p,stop.p,stopnext.p)==LEFT)
							triangle(ptnew[i].p,stop.p,stopnext.p);
						else{
							stk.push(stopnext);
							break;
						}
					}
					stop=stopnext;
				}
				stk.push(stop);
				stk.push(ptnew[i]);
			}
			else {
				//......vi adjacent to stk_bottom and not to stk_top
				point_with_position stop=stk.pop(),stopnext,copyofstk_top;
				copyofstk_top=stop;
				while(!stk.empty()){
					stopnext=stk.pop();
					triangle(ptnew[i].p,stop.p,stopnext.p);
					stop=stopnext;
				}
				stk.push(copyofstk_top);
				stk.push(ptnew[i]);
			}
		}
		getch();
	}

	//........print polygon in which triangulation has been shown
	setcolor(15);str[0]='a';str[1]='\0';
	for(i=0;i<poly.np-1;i++){
		vline(poly.pt[i],poly.pt[i+1]);
		vmoveto(poly.pt[i]);
		outtext(str);
		++str[0];
	}
	vmoveto(poly.pt[i]);
	outtext(str);
	vline(poly.pt[poly.np-1],poly.pt[0]);
	v.waitforrightclick();
	closegraph();
}