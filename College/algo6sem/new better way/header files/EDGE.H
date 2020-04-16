class edge{
public:
	point org,dest;
	edge():
		org(point(0,0)),dest(point(0,0))	{}
	edge(point _org,point _dest):
		org(_org),dest(_dest)			{}
	point point_on_edge(double t){
		return point(org.x+t*(dest.x-org.x),org.y+t*(dest.y-org.y));
	}




};