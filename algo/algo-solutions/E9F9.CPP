#include<iostream>
#include<cmath>
typedef long double LD;
using namespace std;

void biss(LD x1,LD y1,LD x2,LD y2,LD x3,LD y3,LD &ar,LD &br,LD &cr)
{
	LD u=(atan2(y2-y1,x2-x1)+atan2(y3-y1,x3-x1))/2;
	ar=sin(u);
	br=-cos(u);
	cr=-sin(u)*x1+cos(u)*y1;
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		LD x1,y1,x2,y2,x3,y3;
		cin>>x1>>y1>>x2>>y2>>x3>>y3;
		LD a1,a2,b1,b2,c1,c2;
		biss(x1,y1,x2,y2,x3,y3,a1,b1,c1);
		biss(x2,y2,x1,y1,x3,y3,a2,b2,c2);
		cout.precision(15);
		cout<<(c2*b1-c1*b2)/(a1*b2-a2*b1)<<" "<<(c2*a1-c1*a2)/(b1*a2-a1*b2)<<endl;
	}
}