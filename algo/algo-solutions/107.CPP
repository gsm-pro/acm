#include<cstdio>
#include<vector>
using namespace std;
vector<char> used;
vector<vector<int>> g(20001),h(20001);
vector<int> comp;
vector<int> order;

void dfs(int v)
{
	used[v]=true;
	for (size_t i=0;i<g[v].size();++i)
	{
		int c=g[v][i];
		if (!used[c]) dfs(c);
	}
	order.push_back(v);
}

void dfs2(int v,int cmp)
{
	used[v]=true;
	comp[v]=cmp;
	for (size_t i=0;i<h[v].size();++i)
	{
		int c=h[v][i];
		if (!used[c]) dfs2(c,cmp);
	}
}

int main()
{
	int n,m;
	scanf_s("%d%d",&n,&m);
	for(int i=0;i<m;i++) 
	{
		int v1,v2;
        scanf_s("%d%d",&v1,&v2);
		v1--,v2--;
		g[v1].push_back(v2); 
   		h[v2].push_back(v1);
	}
	used.assign(n,false);
	for (int i=0;i<n;++i)
		if (!used[i]) dfs(i);
	int comps=0;
	used.assign(n,false);
	comp.resize(n);
	for (int i=n-1;i>=0;--i)
	{
		int j=order[i];
		if (!used[j]) dfs2(j,++comps);
	}
	printf("%d\n",comps);
	for (int i=0;i<n;i++) printf("%d ",comp[i]);
}