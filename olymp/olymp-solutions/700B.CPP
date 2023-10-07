#include<algorithm>
#include<iostream>
using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int xx1,yy1,xx2,yy2,x1,y1,x2,y2,x3,y3,x4,y4,p=1;
	cin>>xx1>>yy1>>xx2>>yy2;
	x1=min(xx1,xx2);
	y1=min(yy1,yy2);
	x2=max(xx1,xx2);
	y2=max(yy1,yy2);
	cin>>xx1>>yy1>>xx2>>yy2;
	x3=min(xx1,xx2);
	y3=min(yy1,yy2);
	x4=max(xx1,xx2);
	y4=max(yy1,yy2);
	if (x2<x3 || x4<x1 || y2<y3 || y4<y1) p=0;
	int c[4]={x1,x2,x3,x4};
	sort(c,c+4);
	int d[4]={y1,y2,y3,y4};
	sort(d,d+4);
	cout<<(c[2]-c[1])*(d[2]-d[1])*p;
}