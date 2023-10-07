#include<iostream>
#include<vector>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
int n,m,k,p[102],cnt=0;
vector<vector<int>> g;
bool used[102];

bool kuhn(int v)
{
	if (used[v]) return false;
	used[v]=true;
	forn(j,g[v].size())
	{
		int to=g[v][j];
		if (p[to]==-1 || kuhn(p[to]))
		{
			p[to]=v;
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d%d%d",&n,&k,&m);
	g.resize(n);
	forn(i,m)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[--a].push_back(--b);
	}
	memset(p,-1,sizeof(p));
	forn(i,n)
	{
		memset(used,0,sizeof(used));
		kuhn(i);
	}
	forn(i,k)
		if(p[i]!=-1) cnt++;
	printf("%d\n",cnt);
	forn(i,k)
		if(p[i]!=-1)
			printf("%d %d\n",p[i]+1,i+1);
}