#include<iostream>
using namespace std;
#define LL long long

LL gcd_ext(LL a,LL b,LL &x,LL &y)
{
	if (b==0)
	{
		x=1,y=0;
		return a;
	}
	LL x0,y0;
	LL d=gcd_ext(b,a%b,x0,y0);
	x=y0,y=x0-(a/b)*y0;
	return d;
}

int main()
{
	LL a,b,x,y;
	cin>>a>>b;
	gcd_ext(a,b,x,y);
	cout<<x<<" "<<y;
}