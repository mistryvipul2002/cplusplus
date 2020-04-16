#include<iostream.h>
#include<conio.h>
class b;
class a{
			int data;
	public:   a(){data=0;}
			a(a& a1){
			  cout<<"\nCopy Constructor of A called.....";
			  data=a1.data;
			}
			void get(int &d){data=d;}
			void show(){cout<<data;}
			void put(int a){
				data=a;
			}
			void operator=(b b1);

			//............ambiguity in this operator
			/*operator b(){
				cout<<"\nOperator B() in class A...";
				b b1;
				b1.put(data);
				return b1;
			} */
};

class b{
			int data;
	public:   b(){data=0;}
			b(b& b1){
			  cout<<"\nCopy Constructor of B called.....";
			  data=b1.data;
			}
			b(a &a1){
				cout<<"\nCopy constructor of B taking A as argument....";
				a1.get(data);
			}
			void show(){cout<<data;}
			void put(int b){
				data=b;
			}
			void get(int &d){
				d=data;
			}
			operator a(){
				cout<<"\nOperator A() in class B...";
				a a1;
				a1.put(data);
				return a1;
			}

};
//......*******************AMBIGUITY RESOLVED*************
void a::operator=(b b1)
{
	cout<<"\nOperator = used in class B....";
	b1.get(data);
}

void main(){
	clrscr();
	a a1,a2;
	a1.put(1);
	a2.put(2);
	b b1,b2;
	b1.put(3);
	b2.put(4);

	//a1=a2;
	a1.show();a2.show();b1.show();b2.show();

	b1=a1;
	a2=b2;
	cout<<endl;

	a1.show();a2.show();b1.show();b2.show();
	getch();
}