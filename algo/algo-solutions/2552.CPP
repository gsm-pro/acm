#include<iostream>
#include<cmath>
using namespace std;
#define sqr(x) (x)*(x)
const double eps = 1e-9;
double p1,q1,r1,p2,q2,r2,p3,q3,r3,p4,q4,r4;

double d(double &t,double &c)
{
	return sqr(p1+(p2-p1)*t-p3-(p4-p3)*c)+sqr(q1+(q2-q1)*t-q3-(q4-q3)*c)+sqr(r1+(r2-r1)*t-r3-(r4-r3)*c);
}

double f(double &c)
{
	double l=0,r=1,t1,t2;
	while (r-l>eps)
	{
		t2=(r-l)/3.0;
		t1=l+t2;
		t2=t1+t2;
		if (d(t1,c)<d(t2,c)) r=t2;else l=t1;
	}
	return sqrt(d(l,c));
}

int main()
{
	cin>>p1>>q1>>r1>>p2>>q2>>r2>>p3>>q3>>r3>>p4>>q4>>r4;
	double l=0,r=1,c1,c2;
	while (r-l>eps)
	{
		c2=(r-l)/3.0;
		c1=l+c2;
		c2=c1+c2;
		if (f(c1)<f(c2)) r=c2;else l=c1;
	}
	cout.precision(10);
	cout<<f(l);
}