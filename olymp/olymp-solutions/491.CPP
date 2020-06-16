#include<cmath>
#include<iostream>
#define sq(a,b,c,d,e,f) .5*fabs((c-a)*(f-b)-(e-a)*(d-b))
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,k=0;
	double x,y,x1,y1,x2,y2,x3,y3,s;
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>n;
	s=sq(x1,y1,x2,y2,x3,y3);
	while (cin>>x>>y) 
		k+=(fabs(s-sq(x1,y1,x2,y2,x,y)-sq(x2,y2,x3,y3,x,y)-sq(x1,y1,x3,y3,x,y))<.01);
	printf("%.1lf\n%d",s,k);
}