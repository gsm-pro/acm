#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> g(20001);
vector<char> used,pts;
int timer=0,n,m,k=0;
vector<int> t,f;

void dfs(int v,int p=-1)
{
	used[v]=true;
	t[v]=f[v]=timer++;
	int ch=0;
	for (size_t i=0;i<g[v].size();++i) 
	{
		int to=g[v][i];
		if (used[to]) f[v]=min(f[v],t[to]);else 
		{
			++ch;
			dfs(to,v);
			f[v]=min(f[v],f[to]);
			if (f[to]>=t[v]) pts[v]=true;
		}
	}
	if (p==-1) pts[v]=ch>1;
}

int main() 
{
	scanf_s("%d%d",&n,&m);
	for(int i=0;i<m;i++) 
	{
		int v1,v2;
		scanf_s("%d%d",&v1,&v2);
		v1--,v2--;
		g[v1].push_back(v2); 
		g[v2].push_back(v1);
	}
	timer=0;
	used.assign(n,false);
	t.resize(n);
	f.resize(n);
	pts.assign(n,false);
	dfs(0);
	for (int i=0;i<n;i++) if (pts[i]) k++;
	printf("%d\n",k);
	for (int i=0;i<n;i++) if (pts[i]) printf("%d ",i+1);
}