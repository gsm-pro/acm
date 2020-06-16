#include<iostream>
#include<vector>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
#define ford(i,n) for(int i=1;i<int(n);++i)
const int NMAX=4001;
vector<int> g[NMAX];
short p1[NMAX];
short p2[NMAX];
bool u1[NMAX];
bool u2[NMAX];

void ext_dfs(int v)
{
	if(u1[v]) return;
	u1[v]=true;
	forn(j,g[v].size())
	{
		int to=g[v][j];
		u2[to]=true;
		ext_dfs(p2[to]);
	}
}

void main()
{
	int n,m;
	scanf("%d%d",&m,&n);
	ford(i,m+1)
	{
		int s;
		scanf("%d",&s);
		g[i].resize(s);
		forn(j,s) scanf("%d",&g[i][j]);
	}
	ford(i,m+1)
	{
		int t;
		scanf("%d",&t);
		p1[i]=t;
		p2[t]=i;
	}
	memset(u1,0,sizeof(u1));
	memset(u2,0,sizeof(u2));
	ford(i,m+1)
		if(p1[i]==0) ext_dfs(i);
	vector<int> res1;
	vector<int> res2;
	ford(i,m+1)
		if(!u1[i])
			res1.push_back(i);
	ford(i,n+1)
		if(u2[i])
			res2.push_back(i);
	printf("%d\n%d ",res1.size()+res2.size(),res1.size());
	forn(i,res1.size())
		printf("%d ",res1[i]);
	printf("\n%d ",res2.size());
	forn(i,res2.size())
		printf("%d ",res2[i]);
}