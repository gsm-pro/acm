#include<cstdio>
#include<vector>
using namespace std;
int n,l;
vector<vector<int>>g;
vector<char>used;
vector<int>tin,tout;
int timer;
vector<vector<int>> up;

void dfs(int v,int p=0) 
{
	used[v]=true;
	tin[v]=++timer;
	up[v][0]=p;
	for(int i=1;i<=l;++i) up[v][i]=up[up[v][i-1]][i-1];
	for(size_t i=0;i<g[v].size();++i) 
	{
		int to=g[v][i];
		if (!used[to]) dfs(to,v);
	}
	tout[v]=++timer;
}

bool upper(int a,int b) 
{
	return tin[a]<=tin[b] && tout[a]>=tout[b];
}

int lca(int a,int b)
{
	if (upper(a,b)) return a;
	if (upper(b,a)) return b;
	for(int i=l;i>=0;--i)
		if (!upper(up[a][i],b))
			a=up[a][i];
	return up[a][0];
}

int main()
{
	scanf_s("%d",&n);
	g.resize(n);
	int v1,v2;
	for(int i=1;i<=n-1;i++)
	{
		scanf_s("%d%d",&v1,&v2);
		v1--;
		v2--;
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	used.resize(n);
	tin.resize(n);
	tout.resize(n);
	up.resize(n);
	l=1;
	while ((1<<l)<=n) ++l;
	for(int i=0;i<n;++i) up[i].resize(l+1);
	dfs(0);
	while (scanf_s("%d%d",&v1,&v2)==2) printf("%d ",lca(--v1,--v2)+1);
}