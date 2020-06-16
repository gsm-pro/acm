#include <iostream>
using namespace std;
typedef long long LL;

LL gcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	LL x1,y1;
	LL d=gcd(b,a%b,x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
	return d;	
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	LL a,b,m,x,y;
	cin>>a>>b>>m;
	LL d=gcd(a,m,x,y);
	if(b%d==0)	
		cout<<((x*(b/d))%m+m)%m;
	else cout<<-1;
}