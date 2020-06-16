#include<iostream>
using namespace std;
double x1,y1,x2,y2,x3,y3,x4,y4,k;

int main()
{
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
	if ((y2-y1)*(x3-x4)-(y4-y3)*(x1-x2)==0)
	{
		if ((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)==0)
			cout<<2;
		else
			cout<<0;
	}
	else
	{
		cout<<1<<"\n";
		k=((x4-x3)*(y1-y3)-(y4-y3)*(x1-x3))/((x2-x1)*(y4-y3)-(y2-y1)*(x4-x3));
		cout.precision(5);
		cout<<fixed<<x1+k*(x2-x1)<<" "<<y1+k*(y2-y1);
	}
}