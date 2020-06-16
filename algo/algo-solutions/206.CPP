#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
using namespace std;
#define N 100001
int n,l,timer,v1,v2,k;
vector<vector<int>>g(N),up(N),grps(N);
vector<char>used(N),us(N),us1(N);
vector<int>tin(N),tout(N),dst(N),cur_group(N),predok(N); 

void dfs(int v,int p=0) 
{
	used[v]=true,up[v][0]=p;
	tin[v]=++timer;
	for (int i=1;i<=l;++i) up[v][i]=up[up[v][i-1]][i-1];
	for (size_t i=0;i<g[v].size();++i) 
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

int LCA(int a,int b)
{
	if (upper(a,b)) return a;
	if (upper(b,a)) return b;
	for (int i=l;i>=0;--i)
		if (!upper(up[a][i],b)) a=up[a][i];
	return up[a][0];
}

void calc_dst(int v,int r,int pred)
{
	us[v]=true;
	if (v!=0) predok[v]=pred;
	dst[v]=r;
	int cnt=(int)g[v].size();
	if ((pred==0) || (pred!=0 && (int)g[pred].size()>2)) cur_group[v]=v;
		else cur_group[v]=cur_group[pred];
	for (int i=0;i<cnt;i++)
		if (!us[g[v][i]]) calc_dst(g[v][i],r+1,v);
}

void make_groups(int v)
{
	us1[v]=true;
	if (v!=0) grps[cur_group[v]].push_back(v);
	int cnt=(int)g[v].size();
	for (int i=0;i<cnt;i++)
		if (!us1[g[v][i]]) make_groups(g[v][i]);
}

int calc(int lca,int v,int k)
{
	if (dst[v]-dst[lca]<k) return -1;
	int nuzhen=dst[lca]+k,cur_dist=dst[v];
	while (true)
	{
		int gr=cur_group[v],first=grps[gr][0],cur_dist=dst[first];
		if (cur_dist<=nuzhen)
		{
			k=k-(dst[first]-dst[lca]);
			return grps[gr][k];
		}
		v=predok[first];
	}
}

int main()
{
	scanf("%d",&n);
	predok[0]=-1,cur_group[0]=0;
	for (int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&v1,&v2);
		v1--,v2--;
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	l=1;
	while ((1<<l)<=n) ++l;
	for (int i=0;i<n;++i) up[i].resize(l+1);
	dfs(0);
	calc_dst(0,0,0);
	grps[0].push_back(0);
	for (int i=0;i<(int)g[0].size();i++) make_groups(g[0][i]);
	while (scanf("%d%d%d",&v1,&v2,&k)==3)
	{
		--v1,--v2;
		int lca=LCA(v1,v2);
		printf("%d %d\n",calc(lca,v1,k)+1,calc(lca,v2,k)+1);
	}
}