#include<vector>
#include<cstdio>
#define forn(i,n) for(int i=0;i<(n);i++)
using namespace std;
vector<int> uk,d,p,op;

void sw(int a,int b) 
{
	swap(p[a],p[b]);
	op[p[a]]=a;
	op[p[b]]=b;
}

int main() 
{
	int n;
	scanf("%d",&n);
	uk=vector<int>(n,0),
	d=vector<int>(n,1);
	p=op=vector<int>(n);
	forn(i,n) op[i]=p[i]=i;
	int fac=1;
	for(int i=2;i<=n;i++) fac*=i;
	forn(z,fac) 
	{
		forn(i,n) printf("%d ",p[i]+1);
		printf("\n");
		for(int i=n-1;i>=0;--i) 
		{
			if (uk[i]+d[i]<=i && uk[i]+d[i]>=0) 
			{
				uk[i]+=d[i];
				if (d[i]>0) sw(op[i],op[i]-1);else sw(op[i],op[i]+1);
				break;
			}
			else d[i]*=-1;
		}
	}
}