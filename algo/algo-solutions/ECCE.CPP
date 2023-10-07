#include<iostream>
#include<cmath>
using namespace std;
#define pw(a,b) (int)(exp(b*(log(a+.0))+.0)+.5)
int d[200000];

int main() 
{
	int n,k;
	cin>>n>>k;
	if (k==1) cout<<1;else
	{
		memset(d,100,sizeof(d));
		d[0]=0;
		for (int j=1;pw(j,k)<=n;++j)
		{
			int c=pw(j,k);
			for (int i=0;c+i<=n;++i) d[i+c]=min(d[i+c],d[i]+1);
		}
		cout<<d[n];
	}
}