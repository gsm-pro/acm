#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

__int64 integer(double a,double b)
{
	return ((int)b-(b<0 && b!=(int)b)-(int)a-(a>0 && a!=(int)a)+1)*(a<=b);
}

__int64 center(double a,double b,double c,double d)
{
	if ((b<c && a<c) || (c<a && d<a)) return 0;
	vector<double> v(4);
	v[0]=a,v[1]=b,v[2]=c,v[3]=d;
	sort(v.begin(),v.end());
	return integer(v[1],v[2]);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	double x1,y1,x2,y2,x0,y0,r;
	cin>>x1>>y1>>x2>>y2>>x0>>y0>>r;
	__int64 ans=0;
	for (int i=(int)x1;i<=(int)x2;i++)
	{
		if (r*r-(i-x0)*(i-x0)<0) continue;
		double z1=y0-sqrt(r*r-(i-x0)*(i-x0)),z2=y0+sqrt(r*r-(i-x0)*(i-x0));
		ans+=center(z1,z2,y1,y2);
	}
	cout<<ans;
}