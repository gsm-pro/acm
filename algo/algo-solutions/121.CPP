#include<cstdio>
#include<iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);i++)
#define NMAX 402
#define INF 9999999
int d[NMAX],p[NMAX][NMAX],c[NMAX][NMAX],f[NMAX][NMAX],prev[NMAX],n,s,t,kol;
bool used[NMAX];

void P()
{
	forn(i,kol) d[i]=INF;
	d[s]=0;
	memset(used,0,sizeof(used));
	used[s]=true;
	forn(i,kol)
	{
		bool flag=false;
		forn(j,kol)
		{
			if(used[j])
			{
				flag=true;
				forn(k,kol)
					if(c[j][k]>f[j][k] && d[k]>d[j]+p[j][k])
					{
						d[k]=d[j]+p[j][k];
						prev[k]=j;
						used[k]=true;
					}
				used[j]=false;
			}
		}
		if(!flag) break;
	}
}

int main()
{
	scanf("%d",&n);
	forn(i,n)
		forn(j,n)
		{
			scanf("%d",&p[i][j+n]);
			c[i][j+n]=1;
			p[j+n][i]=-p[i][j+n];
		}
	s=2*n;
	t=2*n+1;
	kol=2*n+2;
	forn(i,n)
	{
		c[s][i]=1;
		c[i+n][t]=1;
	}
	int cost=0;
	while(true)
	{
		P();
		if(d[t]>INF/2) break;
		cost+=d[t];
		int k=t;
		while(k!=s)
		{
			f[prev[k]][k]++;
			f[k][prev[k]]--;
			k=prev[k];
		}
	}
	printf("%d\n",cost);
	forn(i,n)
		forn(j,n)
			if(f[i][j+n]==c[i][j+n]) printf("%d ",j+1);
}