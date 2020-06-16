#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> g(1001);
int id[1001][1001];
vector<char>used;
int timer=0,kol=0,n,m,v1,v2;
vector<int> t,f,c;

void dfs(int v,int p=-1)
{
	used[v]=true;
	t[v]=f[v]=timer++;
	for (size_t i=0;i<g[v].size();++i)
	{
		int to=g[v][i];
		if (to==p) continue;
		if (used[to]) f[v]=min(f[v],t[to]);else 
		{
			dfs(to,v);
			f[v]=min(f[v],f[to]);
			if (f[to]>t[v]) c.push_back(id[v][to]);
		}
	}
}

int main() 
{
	scanf_s("%d%d",&n,&m);
	for(int i=0;i<m;i++) 
	{
		scanf_s("%d%d",&v1,&v2);
		v1--,v2--;
		g[v1].push_back(v2); 
		g[v2].push_back(v1);
		id[v1][v2]=id[v2][v1]=i;
	}
	used.assign(n,false);
	t.resize(n);
	f.resize(n);
	dfs(0);
	sort(c.begin(),c.end());
	printf("%d\n",(int)c.size());
	for (size_t i=0;i<c.size();i++) printf("%d\n",c[i]+1);
}