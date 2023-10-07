#include<iostream>
#include<algorithm>
using namespace std;
long long x[4],y[4],z[6];

long long dist(int a,int b)
{
	return (x[b]-x[a])*(x[b]-x[a])+(y[b]-y[a])*(y[b]-y[a]);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	while (n-->0)
	{
		for (int i=0;i<4;i++) cin>>x[i]>>y[i];
		z[0]=dist(0,1);
		z[1]=dist(0,2);
		z[2]=dist(0,3);
		z[3]=dist(1,2);
		z[4]=dist(1,3);
		z[5]=dist(2,3);
		sort(z,z+6);
		if (z[0]==z[3] && z[4]==z[5]) cout<<"YES\n";else cout<<"NO\n";
	}
}