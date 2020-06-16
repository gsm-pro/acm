#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define forn(i,n) for (int i=0;i<(int)n;i++)
#define NMAX 7501
bool used[NMAX],us[NMAX];
int n,x[NMAX],y[NMAX],dist[NMAX],tree[NMAX],color[NMAX];
vector<int> mst[NMAX],g[NMAX];

void update(int v,bool flag)
{
	if (flag)
	{
		mst[tree[v]].push_back(v);
		mst[v].push_back(tree[v]);
	}
	used[v]=true;
	forn(i,g[v].size())
		if (!used[g[v][i]]) update(g[v][i],false);
	forn(i,n)
		if (dist[i]>(x[i]-x[v])*(x[i]-x[v])+(y[i]-y[v])*(y[i]-y[v]))
		{
			dist[i]=(x[i]-x[v])*(x[i]-x[v])+(y[i]-y[v])*(y[i]-y[v]);
			tree[i]=v;
		}
}

void dfs(int v,int cl)
{
	us[v]=true;
	color[v]=cl;
	for (int i=0;i<(int)mst[v].size();i++)
		if (!us[mst[v][i]]) dfs(mst[v][i],3-cl);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	forn(i,n)
		scanf("%d%d",&x[i],&y[i]);
	forn(i,n)
	{
		dist[i]=int(2e9);
		used[i]=false;
		tree[i]=-1;
	}
	update(0,false);
	while (true)
	{
		int best=int(2e9),v=-1;
		forn(i,n)
			if ((!used[i]) && (dist[i]<best))
			{
				v=i;
				best=dist[i];
			}
		if (v==-1) break;
		update(v,true);
	}
	dfs(0,1);
	int ans=int(2e9);
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (color[i]+color[j]!=3)
				ans=min(ans,(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
	printf("%.9lf\n",0.5*sqrt(ans+.0));
	for (int i=0;i<n;i++) cout<<color[i]<<" ";
}