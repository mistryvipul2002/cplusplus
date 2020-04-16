#include<iostream.h>
#include<fstream.h>
void main()
{
	ofstream outfile;
	ifstream infile;
	infile.open("delip.txt");
	outfile.open("delop.txt");
	float i,num,total;
	while(1){
		total=0.0;
		i=2.0;
		infile>>num;
		if(num==0.0)break;
		while(1){
			if(total>=num){
				outfile<<(i-2)<<" cards(s)\n";
				break;
			}
			total+=1/i;
			i+=1.0;
		}
	}
	infile.close();
	outfile.close();
}