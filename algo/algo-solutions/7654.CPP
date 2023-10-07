#include<iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<(n);i++)
#define M 1000000000
int d1[20][65536],d2[20][65536];

void add(int &a,int b)
{
	a=(b+a)%M;
}

int has(int mask,int v)
{
	return mask&(1<<v);
}

int main()
{
	int n,m;
	cin>>n>>m;
	if (n>m) swap(n,m);
	forn(i,(1<<(n+1))) d1[0][i]=1;
	for (int i=1;i<m;i++)
	{
		forn(j,n)
		{
			forn(k,(1<<(n+1)))
			{
				if (j==n-1)
				{
					int mask=k;
					if (mask&(1<<n)) mask-=(1<<n);
					mask<<=1;
					add(d2[0][mask],d1[j][k]);
					add(d2[0][mask+1],d1[j][k]);
					continue;
				}
				int mask=k;
				mask^=(1<<(j+1));
				add(d1[j+1][mask],d1[j][k]);
				mask^=(1<<(j+1));
				if (((has(mask,j)==0)+(has(mask,j+1)==0)+(has(mask,j+2)==0))%3!=0)
					add(d1[j+1][mask],d1[j][k]);
			}
		}
		memset(d1,0,sizeof(d1));
		forn(k,(1<<(n+1)))
		{
			d1[0][k]=d2[0][k];
			d2[0][k]=0;
		}
	}
	int ans=0;
	forn(i,(1<<n)) add(ans,d1[0][i<<1]);
	cout<<ans;
}