#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>g;
bool u[502];
int p[502],x[501],y[501],z[501],w[501],xx[501],yy[501],ans1=0,n;

bool kuhn(int v) 
{
	if (u[v]) return false;
	u[v]=true;
	for(int i=0;i<(int)g[v].size();i++)
	{
		int t=g[v][i];
		if (p[t]==-1 || kuhn(p[t])) 
		{
			p[t]=v;
			return true;
		}
	}
	return false;
}

bool can(int i,int j)
{
	return (xx[i]>=x[j] && xx[i]<=z[j] && yy[i]>=y[j] && yy[i]<=w[j]);
}

int main()
{
	scanf("%d",&n);
	g.resize(n);
	for (int i=0;i<n;i++) scanf("%d%d%d%d",&x[i],&y[i],&z[i],&w[i]);
	for (int i=0;i<n;i++) scanf("%d%d",&xx[i],&yy[i]);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (can(i,j)) g[j].push_back(i);
	memset(p,-1,sizeof p);
	for (int i=0;i<n;i++) 
	{
		memset(u,false,sizeof u);
		ans1+=(int)(kuhn(i));
	}
	vector<pair<int,int>> res;
	for(int j=0;j<n;j++)
		if (p[j]!=-1) res.push_back(make_pair(p[j],j));
	if (ans1!=n)
	{
		printf("No solution");
		return 0;
	}
	vector<int>ans(n);
	for (int i=0;i<n;i++) ans[res[i].first]=i;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (i!=j && can(ans[j],i) && can(ans[i],j))
			{
				printf("Not unique");
				return 0;
			}
	for (int i=0;i<n;i++) printf("%d ",ans[i]+1);
}