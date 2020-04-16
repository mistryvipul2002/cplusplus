class polygon{
public:
	point pt[MAX];
	int np;
	polygon(){np=0;}
	void add_point(point p){
		pt[np++]=p;
	}
	point centre_of_gravity();
	void input_points(int);
	void remove_point(int);
	void print_polygon();
	int check_convex();
	int check_monotone_wrt_x_axis();
	void orient(int);
	int edgetype(point,edge);
	int point_inside_wedge_method_for_convex_polygons(point);
	int point_inside_ray_shoot_method_for_any_polygon(point p);
	void convex_hull_gift_wrapping_algorithm(point[],int);
	void convex_hull_graham_scan_algorithm(point[],int);
	polygon* triangulate();
	void triangulate(int);
};
void polygon::remove_point(int pos){
	if(pos==np-1){np--;return;}
	for(int i=pos;i<np-1;i++){
		pt[i]=pt[i+1];
	}
	np--;
}
void polygon::print_polygon(){
	for(int i=0;i<np;i++){
		vline(pt[i],pt[(i+1)%np]);
	}
}
point polygon::centre_of_gravity(){
	//.......find c.g. of polygon
	point q;q.x=q.y=0;
	for(int i=0;i<np;i++)q=q+pt[i];
	q.x=q.x/np;q.y=q.y/np;
	return(q);
}
void polygon::input_points(int drawline_or_not){
	//.....enter the lines
	vmouse v;
	point p,prev;int k=0;
	while(v.waitforaclick(p)==LEFT){
		add_point(p);
		if(k==0)prev=p;
		if(drawline_or_not==DRAW)vline(p,prev);
		else vputpixel(p,15);
		prev=p;k=1;
	}
	if(drawline_or_not==DRAW)vline(prev,pt[0]);
}
int polygon::check_convex(){
	//.....check polygon is convex or not
	int parity;
	if(pt[0].classify_point_position_wrt_line_segment(pt[1],pt[2])==RIGHT)parity=RIGHT;
	else parity =LEFT;
	for(int i=0;i<=np;i++){
		if(pt[i%np].classify_point_position_wrt_line_segment(pt[(i+1)%np],pt[(i+2)%np])!=parity)
			return(FALSE);
	}
	return(TRUE);
}
void polygon::orient(int direction){
	//...put points of a "convex polygon" in fashion specified by "direction"
	if( (pt[0].classify_point_position_wrt_line_segment(pt[1],pt[2])==RIGHT&& //...means points are clockwise
		direction==ANTICLOCKWISE)		||
	    (pt[0].classify_point_position_wrt_line_segment(pt[1],pt[2])==LEFT&& //...means points are anticlockwise
		direction==CLOCKWISE)
	  ){
		for(int i=0;i<np/2;i++)
			swap(pt[i],pt[(np-1)-i]);
	}
}
int polygon::point_inside_wedge_method_for_convex_polygons(point p){
	//......check if point p lies in polygon
	point q=centre_of_gravity();	//.....q is cg of polygon
	for(int i=0;i<np;i++){
		if(p.classify_point_position_wrt_line_segment(q,pt[i])==LEFT &&  p.classify_point_position_wrt_line_segment(q,pt[(i+1)%np])==RIGHT){
			//.........pt z lies in wedge p(i)-q-p(i+1)
			//........now check whether p(i)-p(i+1)-z is a left turn
			if(pt[i].classify_point_position_wrt_line_segment(pt[(i+1)%np],p)==LEFT)return(TRUE);
		}
	}
	return(FALSE);
}
int polygon::edgetype(point a,edge e){
	//............function to be used in ray shoot method of point inclusion
	point v = e.org;
	point w = e.dest;
	switch(a.classify_point_position_wrt_line_segment(v,w)){
		case LEFT:
			return ((v.y<a.y) && (a.y<=w.y)) ? CROSSING:INESSENTIAL;
		case RIGHT:
			return ((w.y<a.y) && (a.y<=v.y)) ? CROSSING:INESSENTIAL;
		case BETWEEN:
		case ORIGIN:
		case DESTINATION:
			return TOUCHING;
		default:
			return INESSENTIAL;
	}
}
int polygon::point_inside_ray_shoot_method_for_any_polygon(point pt_to_check){
	//......check if point p lies in polygon
	int parity=0;
	for(int i=0;i<np;i++){
		edge edge_of_polygon=edge(pt[i],pt[(i+1)%np]);
		switch(edgetype(pt_to_check,edge_of_polygon)){
			case TOUCHING: return BOUNDARY;
			case CROSSING: parity = 1- parity;
			case INESSENTIAL:;
		}
	}
	return(parity?INSIDE:OUTSIDE);
}
int polygon::check_monotone_wrt_x_axis(){
	point left=pt[0],right=pt[0];
	int posleft=0,posright=0;
	for(int i=0;i<np;i++){
		if(pt[i].x<left.x){left=pt[i];posleft=i;}
		if(pt[i].x>right.x){right=pt[i];posright=i;}
	}
	int cou1=posleft,cou2=posleft;
	for(i=0;i<np;i++){
		if(cou1!=before(posright,np)){
			if(pt[cou1].x>pt[next(cou1,np)].x)return(FALSE);
			cou1=next(cou1,np);
		}
		if(cou2!=next(posright,np)){
			if(pt[cou2].x>pt[before(cou2,np)].x)return(FALSE);
			cou2=before(cou2,np);
		}
	}
	return(TRUE);
}
void polygon::convex_hull_gift_wrapping_algorithm(point pt[],int np){
	//.......find leftmost point of set
	point leftmost=pt[0];
	int a=0;
	for(int i=0;i<np;i++){
		if(pt[i].x<leftmost.x){
			leftmost=pt[i];
			a=i;
		}
	}
	pt[np]=pt[a];

	//....apply gift wrapping algorithm
	for(int m=0;m<np;m++){
		swap(pt[a],pt[m]);
		add_point(pt[m]);
		a=m+1;
		for(int i=m+2;i<=np;i++){
			int c=pt[i].classify_point_position_wrt_line_segment(pt[m],pt[a]);
			if(c==LEFT||c==BEYOND)
				a=i;
		}
		if(a==np)break;
	}
}
void polygon::convex_hull_graham_scan_algorithm(point pt[],int np){
	//.......find lowest point of set
	point lowest=pt[0];
	for(int i=0;i<np;i++){
		if(pt[i].y<lowest.y){
			lowest=pt[i];
		}
	}

	//....sort the points by polar angle subtended on lowest point
	point less;int pos;
	for(i=0;i<np;i++){
		pos=i;less=pt[i];
		for(int j=i+1;j<np;j++){
			if(pt[j].polar_angle_in_radian_subtended_on(lowest)<
			   less.polar_angle_in_radian_subtended_on(lowest)){
				less=pt[j];pos=j;
			}
		}
		swap(pt[pos],pt[i]);
	}

	//.....apply graham scan
	stack <point>list;
	point p1=pt[0],p2=pt[1];
	list.push(pt[0]);
	list.push(pt[1]);
	for(i=2;i<np;i++){
		if(p1.classify_point_position_wrt_line_segment(p2,pt[i])==RIGHT){
			while(p1.classify_point_position_wrt_line_segment(p2,pt[i])!=LEFT){
				list.pop();
				p2=list.pop();
				p1=list.pop();
				list.push(p1);
				list.push(p2);
			}
			list.push(pt[i]);
			p1=p2;
			p2=pt[i];
		}
		else{
			p1=p2;
			p2=pt[i];
			list.push(pt[i]);
		}
	}

	//.......we get hull in 'list' stack
	while(!list.empty())
		add_point(list.pop());
}
polygon* polygon::triangulate(){
	//............find leftmost and rightmost point in pt
	point left=pt[0],right=pt[0];
	int posleft=0,posright=0;
	for(int i=0;i<np;i++){
		if(pt[i].x<left.x){left=pt[i];posleft=i;}
		if(pt[i].x>right.x){right=pt[i];posright=i;}
	}

	//....check if points are in clockwise fashion
	if(pt[before(posleft,np)].classify_point_position_wrt_line_segment(pt[posleft],pt[next(posleft,np)])==LEFT){
		//......orient the polygn in reverse direction
		for(int i=0;i<np/2;i++)
			swap(pt[i],pt[(np-1)-i]);
		//......again calculate left,right,posleft,posright
		left=pt[0],right=pt[0];
		posleft=0,posright=0;
		for(i=0;i<np;i++){
			if(pt[i].x<left.x){left=pt[i];posleft=i;}
			if(pt[i].x>right.x){right=pt[i];posright=i;}
		}
	}

	//....make new "ptnew" which use z cordinate of each point to store
	//.... whether it lies in Upper polygonal chain or in the lower one
	point ptnew[MAX];
	int cou1=posleft,cou2=posleft;
	while(cou1!=posright){
		ptnew[cou1]=pt[cou1];
		ptnew[cou1].z=UP;
		cou1=next(cou1,np);
	};
	while(cou2!=posright){
		ptnew[cou2]=pt[cou2];
		ptnew[cou2].z=DOWN;
		cou2=before(cou2,np);
	};
	ptnew[posright]=pt[posright];
	ptnew[posright].z=UP;

	//..........now we have got the ptnew with position of each point
	//........so sort it wrt x cordinate
	int pos;point less;
	for(i=0;i<np;i++){
		pos=i;less=ptnew[i];
		for(int j=i+1;j<np;j++){
			if(ptnew[j].x<less.x){
				less=ptnew[j];pos=j;
			}
		}
		swap(ptnew[pos],ptnew[i]);
	}

	//.........apply algorithm
	setcolor(10);
	polygon *triangles = new polygon[np-2];int count=0;
	stack <point> stk;
	stk.push(ptnew[0]);
	stk.push(ptnew[1]);
	point stop,stopnext,copyofstk_top;
	for(i=2;i<np;i++){
		if(i==np-1){  	//......vi adjacent to stk_top and stk_bottom
					//......which is possible for rightmost point
			stop=stk.pop();
			while(!stk.empty()){
				stopnext=stk.pop();
				triangles[count].add_point(ptnew[i]);
				triangles[count].add_point(stop);
				triangles[count].add_point(stopnext);
				count++;
				stop=stopnext;
			}
		}
		else{
			if(ptnew[i].z==(stk.stacktop()).z){
				//......vi adjacent to stk_top and not to stk_bottom
				stop=stk.pop();
				while(!stk.empty()){
					stopnext=stk.pop();
					if(ptnew[i].z==DOWN){
						if(ptnew[i].classify_point_position_wrt_line_segment(stop,stopnext)==RIGHT){
							triangles[count].add_point(ptnew[i]);
							triangles[count].add_point(stop);
							triangles[count].add_point(stopnext);
							count++;
						}
						else{
							stk.push(stopnext);
							break;
						}
					}
					if(ptnew[i].z==UP){
						if(ptnew[i].classify_point_position_wrt_line_segment(stop,stopnext)==LEFT){
							triangles[count].add_point(ptnew[i]);
							triangles[count].add_point(stop);
							triangles[count].add_point(stopnext);
							count++;
						}
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
				stop=stk.pop();
				copyofstk_top=stop;
				while(!stk.empty()){
					stopnext=stk.pop();
					triangles[count].add_point(ptnew[i]);
					triangles[count].add_point(stop);
					triangles[count].add_point(stopnext);
					count++;
					stop=stopnext;
				}
				stk.push(copyofstk_top);
				stk.push(ptnew[i]);
			}
		}
	}
	return(triangles);
}