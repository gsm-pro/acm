#include <iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);i++)
#define INF 1000000010

void main()
{
	int g[20][20],d[20][200000],n;
	cin>>n;
	forn(i,n) forn(j,n)
	{
		cin>>g[i][j];
		if (g[i][j]==0) g[i][j]=INF;
	}
	forn(i,n) forn(j,(1<<n)) d[i][j]=INF;
	d[0][0]=0;
	forn(mask,(1<<n)){
		forn(i,n){
			if (d[i][mask]==INF) continue;
			forn(j,n){
				if (mask&(1<<j)) continue;
				if (g[i][j]==INF) continue;
				d[j][mask^(1<<j)]=min(d[j][mask^(1<<j)],d[i][mask]+g[i][j]);
			}
		}
	}
	long long ans=d[0][(1<<n)-1];
	if (ans==INF) ans=-1;
	cout<<ans;
}