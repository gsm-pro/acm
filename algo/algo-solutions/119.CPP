#include<iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);i++)
#define NMAX 205
int n,c[NMAX][NMAX],f[NMAX][NMAX],h[NMAX],e[NMAX];

void main()
{
	cin>>n;
	forn(i,n) forn(j,n) cin>>c[i][j];
	forn(i,n)
	{
		f[i][0]=e[0]-=c[0][i];
		f[0][i]=e[i]+=c[0][i];
	}
	h[0]=n;
	while (true)
	{
		int p=-1;
		forn(i,n)
			if (i!=n-1 && e[i]>0)
			{
				p=i;
				break;
			}
		if (p==-1) break;
		forn(i,n)
		{
			if (c[p][i]>f[p][i] && h[p]>h[i])
			{
				int add=min(c[p][i]-f[p][i],e[p]);
				f[p][i]+=add;
				f[i][p]-=add;
				e[p]-=add;
				e[i]+=add;
			}
		}
		if (e[p]>0) ++h[p];
	}
	cout<<e[n-1];
}