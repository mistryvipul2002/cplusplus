template <class T> class vector{
public:
	T x,y,z;
	vector(){x=y=z=0;}
	vector(vector &v){
		x=v.x;y=v.y;z=v.z;
	}
	vector(T x1,T y1){x=x1;y=y1;}
	int operator==(vector v)	{	return v.x==x&&v.y==y&&v.z==z;	}
	int operator!=(vector v)	{	return v.x!=x||v.y!=y||v.z!=z;	}
	int operator>(vector v)	{	return x>v.x&&y>v.y&&z>v.z;	}
	int operator<(vector v)	{	return x<v.x&&y<v.y&&z<v.z;	}
	int operator>=(vector v)	{	return x>=v.x&&y>=v.y&&z>=v.z;	}
	int operator<=(vector v)	{	return x<=v.x&&y<=v.y&&z<=v.z;	}
	istream& operator>>(istream& istr){	return istr>>x>>y>>z;	}
	ostream& operator<<(ostream& ostr){	return ostr<<x<<y<<z;	}
	vector operator+(vector);
	vector operator-(vector);
	double length(){return sqrt(x*x+y*y);}
	int classify_point_position_wrt_line_segment(point,point);
	float polar_angle_in_radian_subtended_on(point);
};
template <class T> float vector<T>::polar_angle_in_radian_subtended_on(point p2){
	if(x>p2.x){
		if(y>p2.y)	return(atan(float(y-p2.y)/(x-p2.x)));
		else         	return(PI*2-atan(float(p2.y-y)/(x-p2.x)));
	}
	if(x<p2.x){
		if(y>p2.y)	return(PI-atan(float(y-p2.y)/(p2.x-x)));
		else         	return(PI+atan(float(p2.y-y)/(p2.x-x)));
	}
	if(x==p2.x){
		if(y>p2.y)return(PI);
		else if(y<p2.y)return(3*PI/2);
		else return(0);
	}
	return 0;
}
template <class T> vector<T> vector<T>::operator+(vector<T> v){
	vector v2;
	v2.x=v.x+x;
	v2.y=v.y+y;
	v2.z=v.z+z;
	return (v2);
}
template <class T> vector<T> vector<T>::operator-(vector<T> v){
	vector v2;
	v2.x=v.x-x;
	v2.y=v.y-y;
	v2.z=v.z-z;
	return (v2);
}
template <class T> int vector<T>::classify_point_position_wrt_line_segment(point p0,point p1){
	//..........to classify this point wrt directed line segment p0->p1
	point a=p1-p0;
	point b=*this-p0;
	POINT_DATA sa=a.x*b.y-b.x*a.y;
	if(sa>0.0)return LEFT;
	if(sa<0.0)return RIGHT;
	if((a.x*b.x<0.0) || (a.y*b.y<0.0))
		return BEHIND;
	if(a.length()<b.length())
		return BEYOND;
	if(p0==*this)return ORIGIN;
	if(p1==*this)return DESTINATION;
	return BETWEEN;
}