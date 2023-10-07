#include<iostream>
using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	double n,m,x,y,a,b;
	cin>>n>>m>>x>>y;
	if (2*x==n && 2*y==m)
	{
		cout<<"NO";
		return 0;
	}
	bool vert=(m>n);
	if (vert)
	{
		double t=x;
		x=y;
		y=n-t;
		swap(n,m);
	}
	if (x<=n/2 && y<=m/2)
	{
		x=n-x;
		a=0;
		b=y+(n-x)*(3*m-y)/(3*n-x);
	} else
	if (x>=n/2 && y<=m/2)
	{
		a=n;
		b=y+(n-x)*(3*m-y)/(3*n-x);
	} else
	if (x>=n/2 && y>=m/2)
	{
		y=m-y;
		a=n;
		b=m-(y+(n-x)*(3*m-y)/(3*n-x));
	} else
	if (x<=n/2 && y>=m/2)
	{
		x=n-x;
		y=m-y;
		a=0;
		b=m-(y+(n-x)*(3*m-y)/(3*n-x));
	}
	if (vert)
	{
		double t=a;
		a=m-b;
		b=t;
	}
	cout<<"YES"<<endl;
	cout.precision(9);
	cout<<fixed<<a<<" "<<b;
}