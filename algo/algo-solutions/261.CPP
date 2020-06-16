#include <iostream>
using namespace std;

__int64 gcd_ext(__int64 a,__int64 b,__int64 &x,__int64 &y)
{
	if (b==0)
	{
		x=1;
		y=0;
		return a;
	}
	else
	{
		__int64 x0,y0;
		__int64 d=gcd_ext(b,a%b,x0,y0);
		x=y0;
		y=x0-(a/b)*y0;
		return d;
	}
}

int main()
{
	__int64 a,b,x,y,mina,maxa,minb,maxb,dx,dy,d;
	cin>>mina>>maxa>>minb>>maxb>>a>>b;
	d=gcd_ext(a,b,x,y);
    	dx=b/d;
	dy=-a/d;
	__int64 k1 = max((mina-x)/dx,(maxb-y)/dy);
	__int64 k2 = min((maxa-x)/dx,(minb-y)/dy);
	cout<<k2-k1+1;
}